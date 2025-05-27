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

#include "spdlog/logger.h"

#include <ranges>
#ifdef __linux__
#include <sys/epoll.h>
#endif

void stratos::NetworkSession::tick() {
    if (!connected) return;

    if (connection->isClosed()) connected = false; // TODO: Handle connection close

    // Empty received queue
    // TODO: Should we always empty or consume a fix amount per tick?
    processReceived();

    // Attempt to empty the recvBuffer
    handleRawReceived();
}
void stratos::NetworkSession::processReceived() {
    ByteVec segment;
    while (connection->receive(segment) > 0) {
        recvBuffer.insert(recvBuffer.end(), std::make_move_iterator(segment.begin()), std::make_move_iterator(segment.end()));
        segment.clear();
    }
}
void stratos::NetworkSession::handleRawReceived() {
    size_t offset = 0;
    while (recvBuffer.size() > 0) {
        if (protocolState == Handshaking) {
            // Attempt to read the LegacyServerListPing
            try {
                if (const uint8_t id = readUnsignedByte(recvBuffer, offset); id == LegacyServerListPing::ID) {
                    PacketBuffer buffer(recvBuffer);
                    LegacyServerListPing packet;
                    packet.decrypt(buffer);
                    packet.handle(*this);

                    const size_t newOffset = buffer.getOffset();
                    recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + newOffset);
                    continue;
                }
            } catch (PacketSerializationException & ignored) {}
        }

        if (recvBuffer.size() < 6) {
            // Not enough data to read a packet, wait for more data
            return;
        }

        try {
            const int packetLength = readVarInt(recvBuffer, offset);
            if (packetLength < 0 || packetLength > recvBuffer.size() - offset) {
                // Not enough data to read a full packet, wait for more data
                return;
            }

            PacketBuffer packetBuffer(recvBuffer, offset);
            try {
                const int packetId = packetBuffer.readVarInt();
                auto       packetKey = PacketKey{protocolState, Serverbound, packetId};
                const auto packet = PacketRegistry::instance().create(packetKey);
                if (!packet) {
                    networkManager->getLogger()->error("Received unknown packet with ID {} from client {}:{}", packetId, sessionId.ip, sessionId.port);
                    recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + offset + packetLength);
                    return;
                }

                networkManager->getLogger()->info("Received packet with ID {} from client {}:{}", packetId, sessionId.ip, sessionId.port);
                packet->decrypt(packetBuffer);
                packet->handle(*this);
            } catch (const PacketSerializationException &e) {
                networkManager->getLogger()->error("Failed to read packet from client {}:{}: {}", sessionId.ip, sessionId.port, e.what());
            } catch (const std::exception &e) {
                networkManager->getLogger()->error("Encountered an exception when handing a packet for client {}:{}: {}", sessionId.ip, sessionId.port, e.what());
            }

            recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + offset + packetLength);
        } catch (const PacketSerializationException& ignored) {
            // Not enough data to read a packet, wait for more data
            break;
        } catch (const std::exception& e) {
            networkManager->getLogger()->error("Failed to read packet from client {}:{}: {}", sessionId.ip, sessionId.port, e.what());
        }
    }
}
void stratos::NetworkSession::dispose() const {
    networkManager->getLogger()->info("Disposing network session for client {}:{}", sessionId.ip, sessionId.port);
    ByteVec buffer;
    while (connection->receive(buffer) > 0) {
        buffer.clear();
    } // Empty the received queue
}
int  stratos::NetworkConnection::receive(ByteVec& data) {
    if (ByteVec buffer; receiveQueue.try_dequeue(buffer)) {
        data = std::move(buffer);
        return static_cast<int>(data.size());
    }
    return 0;
}
int stratos::NetworkConnection::send(const ByteVec& data) {
    if (data.size() > mtu) {
        ByteVec buffer;
        buffer.reserve(mtu);
        buffer.insert(buffer.end(), std::make_move_iterator(data.begin()), std::make_move_iterator(data.begin() + mtu));
        sendQueue.enqueue(buffer);
        return mtu;
    }

    sendQueue.enqueue(data);
    return static_cast<int>(data.size());
}
int stratos::NetworkConnection::handleReceive() {
    ByteVec buffer;
    ByteVec segment;
    segment.reserve(4096);
    int totalReceived = 0;

    while (true) {
        int received              = 0;
        totalReceived += received = receive(4096, segment);
        if (received == 0) {
            return 0;
        }
        if (received < 0) {
            if (totalReceived < 0) {
                return -1;
            }
            receiveQueue.enqueue(std::move(buffer));
            return totalReceived;
        }

        buffer.insert(buffer.end(), std::make_move_iterator(segment.begin()), std::make_move_iterator(segment.begin() + received));
        segment.clear();
    }
}
int stratos::NetworkConnection::flushSendQueue() {
    ByteVec buffer;
    buffer.reserve(mtu);

    size_t bytesSent = 0;
    while (sendQueue.try_dequeue(buffer)) {
        if (send(buffer, static_cast<int>(buffer.size()), 0) == SOCKET_ERROR) {
            return -1;
        }

        bytesSent += buffer.size();
    }

    return static_cast<int>(bytesSent);
}
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
            session->dispose();
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

    workers = std::vector<std::unique_ptr<WorkerThread>>();
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
                        const auto connection = std::make_shared<NetworkConnection>(socket, ip, port);
                        if (workers.size() < workerThreads) {
                            auto worker = std::make_unique<WorkerThread>(network, workers.size());
                            worker->start();
                            worker->addConnection(connection);
                            workers.push_back(std::move(worker));
                        } else {
                            workers[connectionCount % workerThreads]->addConnection(connection);
                        }

                        // Create a new network session
                        network->createSession(connection);
                        connectionCount++;
                        network->logger->info("Client '{}:{} - {}' connected (MTU: {})", ip, port, socket, connection->getMtu());
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
                    if (!conn->getSendQueue().size_approx()) FD_SET(conn->getFd(), &writeSet);
                    if (conn->getFd() > maxFd) maxFd = conn->getFd();
                }

                timeval timeout{};
                timeout.tv_sec  = 0;
                timeout.tv_usec = 2000;
                select(maxFd + 1, &readSet, &writeSet, nullptr, &timeout);

                for (const auto& conn : connections) {
                    if (FD_ISSET(conn->getFd(), &readSet)) {
                        if (conn->handleReceive() == 0) { // non-blocking
                            // TODO: handle connection close
                            network->getLogger()->info("Connection closed for client {}:{}", conn->getAddress(), conn->getPort());
                            conn->close();
                            removeConnection(conn);
                        }
                    }
                    if (FD_ISSET(conn->getFd(), &writeSet)) {
                        conn->flushSendQueue(); // try sending pending buffers
                    }
                }
#elifdef __linux__
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
                        }
                    }

                    if (!conn->isClosed() && events[i].events & EPOLLOUT) {
                        conn->flushSendQueue();

                        // If queue is empty, remove EPOLLOUT to prevent epoll wakeups
                        epoll_event ev{};
                        ev.events = EPOLLIN | EPOLLET; // Edge-triggered, no out until we have data to send
                        if (conn->getSendQueue().size_approx() > 0) ev.events |= EPOLLOUT;
                        ev.data.fd = fd;
                        epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
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