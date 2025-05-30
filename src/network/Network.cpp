/*
 *
 *               _____  _                 _
 *              /  ___|| |               | |
 *              \ `--. | |_  _ __   __ _ | |_   ___   ___
 *               `--. \| __|| '__| / _` || __| / _ \ / __|
 *              /\__/ /| |_ | |   | (_| || |_ | (_) |\__ \
 *              \____/  \__||_|    \__,_| \__| \___/ |___/
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Copyright (C) 2025 Armen Deroian
 *
 */

#include "Network.h"

#include "NetworkClient.h"
#include "spdlog/logger.h"

#include <ranges>
#ifdef __linux__
#include <sys/epoll.h>
#endif

bool stratos::NetworkManager::start() {
    if (running) throw std::runtime_error("Attempted to start NetworkManager while it is already running");
    running = true;

    try {
        if (socketServer.isValid()) socketServer.listen(100);
    } catch (const std::exception& e) {
        logger->error("Socket Error: {}", e.what());
        return false;
    }

    logger->info("Listening on {}:{}", socketServer.getAddress(), socketServer.getPort());

    bossThread = std::make_unique<BossThread>(this, 10);
    bossThread->start();
    return true;
}
void stratos::NetworkManager::stop() {
    if (!running) throw std::runtime_error("Attempted to stop NetworkManager while it is not running");
    running = false;

    // Wait for the socket thread to finish
    bossThread->stop();

    try {
        socketServer.close();
    } catch (const std::exception& e) {
        logger->error("Socket Error: {}", e.what());
    }
}
void stratos::NetworkManager::tick() {
    processIncomingConnections();

    // Tick all sessions
    std::vector<SessionId> staleSessions;
    for (const auto& [sessionId, session] : sessions) {
        session->tick();
        if (session->isStale()) {
            staleSessions.push_back(sessionId);
        }
    }

    // Remove stale sessions
    for (const auto& sessionId : staleSessions) {
        sessions.erase(sessionId);
    }
}
std::shared_ptr<stratos::NetworkSession> stratos::NetworkManager::getSession(const SessionId& sessionId) {
    if (const auto it = sessions.find(sessionId); it != sessions.end()) return it->second;
    return nullptr;
}
std::vector<std::shared_ptr<stratos::NetworkSession>> stratos::NetworkManager::getSessions() {
    std::vector<std::shared_ptr<NetworkSession>> sessionList;
    sessionList.reserve(sessions.size());
    for (const auto& session : sessions | std::views::values) {
        sessionList.push_back(session);
    }
    return sessionList;
}

void stratos::NetworkManager::createSession(std::shared_ptr<NetworkConnection> connection) {
    sessionsQueue.enqueue(std::move(connection));
}
bool stratos::NetworkManager::removeSession(const SessionId& sessionId) {
    if (const auto it = sessions.find(sessionId); it != sessions.end()) {
        sessions.erase(it);
        return true;
    }
    return false;
}
void stratos::NetworkManager::processIncomingConnections() {
    std::shared_ptr<NetworkConnection> connection;
    while (sessionsQueue.try_dequeue(connection)) {
        if (connection) {
            ClientInfo client{connection->getFd(), connection->getAddress(), connection->getPort()};
            if (const auto it = sessions.find(client); it != sessions.end()) {
                // TODO: This could be due to a client loosing a connection and reconnecting, reuse session?
                logger->warn("Session already exists for client {}:{}", client.ip, client.port);
                return; // Session already exists
            }
            // Create a new session
            logger->info("Creating new network session for client {}:{}", client.ip, client.port);
            const auto session = std::make_shared<NetworkSession>(this, client, std::move(connection));
            sessions[client] = session;
        }
    }
}
void stratos::BossThread::start() {
    if (running.exchange(true)) return;

    workers = std::vector<std::shared_ptr<WorkerThread>>();
    workers.reserve(workerThreads);

    thread = std::thread([this] {
        while (running) {
            try {
                // Accept new connections
                if (const auto client = network->socketServer.accept(); client.socket != INVALID_SOCKET_FD) {
                    std::string ip = client.ip;
                    int port = client.port;
                    SocketFd socket = client.socket;

                    network->getLogger()->info("New connection from {}:{}", ip, port);

                    // Create a new session for the client
                    try {
                        std::shared_ptr<NetworkConnection> connection;
                        if (workers.size() < workerThreads) {
                            auto worker = std::make_shared<WorkerThread>(network, workers.size());
                            worker->start();
#ifdef __linux__
                            connection = std::make_shared<NetworkConnection>(socket, ip, port, network->getLogger(), worker);
#else
                            connection = std::make_shared<NetworkConnection>(socket, ip, port, network->getLogger());
#endif
                            worker->addConnection(connection);
                            workers.push_back(std::move(worker));
                        } else {
#ifdef __linux__
                            connection = std::make_shared<NetworkConnection>(socket, ip, port, network->getLogger(), workers[connectionCount % workerThreads]);
#else
                            connection = std::make_shared<NetworkConnection>(socket, ip, port, network->getLogger());
#endif
                            workers[connectionCount % workerThreads]->addConnection(connection);
                        }

                        // Create a new network session
                        //network->createSession(connection);
                        connectionCount++;
                        network->logger->info("Client '{}:{} - {}' connected", ip, port, socket);
                    } catch (std::exception& e) {
                        network->logger->error("Failed to connect client '{}:{}': {}", ip, port, e.what());
#ifdef _WIN32
                        closesocket(socket);
#else
                        ::close(socket);
#endif
                    }
                }
            } catch (const std::exception& e) {
                network->getLogger()->error("Socket Error: {}", e.what());
            }
        }
    });
}
void stratos::BossThread::stop() {
    if (running.exchange(false)) {
        // Notify all worker threads to stop
        for (const auto& worker : workers) {
            worker->stop();
        }

        // Wait for the boss thread to finish
        if (thread.joinable()) {
            thread.join();
        }
    }
}
void stratos::WorkerThread::start() {
#ifdef __linux__
    epollFd = epoll_create1(0);
    if (epollFd == -1) throw std::runtime_error("epoll_create1 failed: " + std::string(strerror(errno)));
#endif

    if (!running.exchange(true)) {
        thread = std::thread([this] {
            while (running) {
                processIncomingConnections();
#ifdef _WIN32
                fd_set readSet, writeSet;
                FD_ZERO(&readSet);
                FD_ZERO(&writeSet);
                SocketFd maxFd = 0;

                for (const auto& conn : connections) {
                    FD_SET(conn->getFd(), &readSet);
                    if (conn->hasSendData()) FD_SET(conn->getFd(), &writeSet);
                    if (conn->getFd() > maxFd) maxFd = conn->getFd();
                }

                timeval timeout{};
                timeout.tv_sec  = 0;
                timeout.tv_usec = 2000;
                select(maxFd + 1, &readSet, &writeSet, nullptr, &timeout);

                for (const auto& conn : connections) {
                    if (!conn) continue;
                    if (FD_ISSET(conn->getFd(), &readSet)) {
                        std::cout << "\nHandling receive for client " << conn->getAddress() << ":" << conn->getPort() << std::endl;
                        if (conn->handleReceive() == 0) { // non-blocking
                            // TODO: handle connection close
                            network->getLogger()->info("Connection closed for client {}:{}", conn->getAddress(), conn->getPort());
                            conn->close();
                            removeConnection(conn);
                            continue; // Skip further processing for this connection
                        }
                    }
                    if (FD_ISSET(conn->getFd(), &writeSet)) {
                        conn->flushSend(); // try sending pending buffers
                    }

                    // Handle server -> client disconnects
                    if (conn->isDisconnected()) {
                        network->getLogger()->info("Client {}:{} disconnected", conn->getAddress(), conn->getPort());
                        conn->close();
                        removeConnection(conn);
                    }
                }
#elifdef __linux__
                processSendNotifications();

                constexpr int MAX_EVENTS = 64;
                epoll_event   events[MAX_EVENTS];

                const int ready = epoll_wait(epollFd, events, MAX_EVENTS, 100); // wait up to 100 ms
                if (ready == -1) {
                    if (errno == EINTR) continue;
                    throw std::runtime_error("epoll_wait failed: " + std::string(strerror(errno)));
                }

                for (int i = 0; i < ready; ++i) {
                    int  fd = events[i].data.fd;
                    auto it = std::ranges::find_if(connections, [fd](const auto& c) { return c->getFd() == fd; });

                    if (it == connections.end()) continue;
                    auto& conn   = *it;
                    if (events[i].events & EPOLLIN) {
                        if (conn->handleReceive() == 0) {
                            network->getLogger()->info("Connection closed for client {}:{}", conn->getAddress(), conn->getPort());
                            conn->close();
                            removeConnection(conn);
                            continue; // Skip further processing for this connection
                        }
                    }

                    if (!conn->isClosed() && events[i].events & EPOLLOUT) {
                        conn->flushSend();

                        // If queue is empty, remove EPOLLOUT to prevent epoll wakeups
                        epoll_event ev{};
                        ev.events = EPOLLIN | EPOLLET; // Edge-triggered, no out until we have data to send
                        if (conn->hasSendData()) {
                            ev.events |= EPOLLOUT;
                        } else {
                            bool expected = true;
                            conn->dirty.compare_exchange_strong(expected, false);
                        }
                        ev.data.fd = fd;
                        epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
                    }

                    // Handle server -> client disconnects
                    if (conn->isDisconnected()) {
                        network->getLogger()->info("Client {}:{} disconnected", conn->getAddress(), conn->getPort());
                        conn->close();
                        removeConnection(conn);
                    }
                }
#endif
            }
        });
    }
}
void stratos::WorkerThread::stop() {
    if (running.exchange(false)) {
        // Notify all connections to stop
        for (const auto& conn : connections) {
            conn->close();
        }

        // Wait for the worker thread to finish
        if (thread.joinable()) {
            thread.join();
        }
    }
}
void stratos::WorkerThread::addConnection(std::shared_ptr<NetworkConnection> connection) {
    inConnectionQueue.enqueue(std::move(connection));
}

void stratos::WorkerThread::removeConnection(const std::shared_ptr<NetworkConnection>& connection) {
    if (!connection) return;

#ifdef __linux__
    epoll_ctl(epollFd, EPOLL_CTL_DEL, connection->getFd(), nullptr);
#endif

    std::lock_guard lock(connectionMutex);
    std::erase(connections, connection);
    connectionCount--;
}
#ifdef __linux__
void stratos::WorkerThread::notifySend(const SocketFd& socketFd) {
    std::cout <<"Notify send for socket " << socketFd << std::endl;
    sendNotifyQueue.enqueue(socketFd);
}
#endif
void stratos::WorkerThread::processIncomingConnections() {

    std::lock_guard lock(connectionMutex);
    while (true) {
        if (std::shared_ptr<NetworkConnection> connection; inConnectionQueue.try_dequeue(connection)) {
#ifdef __linux__
            epoll_event ev{};
            ev.events  = EPOLLIN | EPOLLET; // Edge-triggered, no out until we have data to send
            ev.data.fd = connection->getFd();
            if (epoll_ctl(epollFd, EPOLL_CTL_ADD, connection->getFd(), &ev) == -1) {
                if (errno != EEXIST) throw std::runtime_error("epoll_ctl(ADD) failed: " + std::string(strerror(errno)));

                epoll_ctl(epollFd, EPOLL_CTL_MOD, connection->getFd(), &ev);
            }
#endif

            connections.push_back(connection);
            connectionCount++;
        } else {
            break;
        }
    }
}
#ifdef __linux__
void stratos::WorkerThread::processSendNotifications() {
    SocketFd socketFd;
    while (sendNotifyQueue.try_dequeue(socketFd)) {
        epoll_event ev{};
        ev.events = EPOLLIN | EPOLLOUT| EPOLLET; // Edge-triggered, no out until we have data to send
        ev.data.fd = socketFd;
        epoll_ctl(epollFd, EPOLL_CTL_MOD, socketFd, &ev);
    }
}
#endif
