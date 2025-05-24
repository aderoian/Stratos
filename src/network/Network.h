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

#ifndef NETWORK_H
#define NETWORK_H
#include "concurrentqueue.h"
#include "Socket.h"

#include <memory>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace spdlog {
class logger;
}
namespace stratos {
class WorkerThread;
class BossThread;
class Server;
class NetworkSession;

using byte      = unsigned char;
using ByteVec   = std::vector<byte>;
using SessionId = ClientInfo;

class NetworkManager final {
  public:
    NetworkManager(Server* server, std::shared_ptr<spdlog::logger> logger, const std::string& address, const int& port)
        : server(server), logger(std::move(logger)), socketServer(address, port) {}
    NetworkManager(const NetworkManager&) = delete;
    ~NetworkManager()                     = default;

    bool start();
    void stop();
    void tick();

    std::shared_ptr<spdlog::logger>              getLogger() const { return logger; }
    std::shared_ptr<NetworkSession>              getSession(const SessionId& sessionId);
    std::vector<std::shared_ptr<NetworkSession>> getSessions();

    NetworkManager& operator=(NetworkManager&) = delete;

  protected:
    std::shared_ptr<NetworkSession> createSession(const ClientInfo& client);
    bool                            removeSession(const SessionId& sessionId);

  private:
    Server*                         server;
    std::shared_ptr<spdlog::logger> logger;

    std::shared_mutex                                              sessionMutex;
    std::unordered_map<SessionId, std::shared_ptr<NetworkSession>> sessions;

    TCPServer socketServer;

    std::atomic<bool> running;

    std::unique_ptr<BossThread> bossThread;

    friend class BossThread;
};

class NetworkSession {
  public:
    explicit NetworkSession(NetworkManager* networkManager, const ClientInfo& client)
        : networkManager(networkManager), sessionId{client.socket, client.ip, client.port}, socket(client.socket, client.ip, client.port) {}
    ~NetworkSession();

    [[nodiscard]] std::string getIp() const { return sessionId.ip; }
    [[nodiscard]] int         getPort() const { return sessionId.port; }

    void tick();

  private:
    NetworkManager* networkManager;
    SessionId       sessionId;
    TCPConnection   socket;
};

class NetworkConnection final : public TCPConnection {
  public:
    using TCPConnection::receive;
    using TCPConnection::send;

    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port) : TCPConnection(socketFd, address, port) {
        sendQueue    = moodycamel::ConcurrentQueue<ByteVec>();
        receiveQueue = moodycamel::ConcurrentQueue<ByteVec>();
    }
    ~NetworkConnection() override = default;

    [[nodiscard]] const moodycamel::ConcurrentQueue<ByteVec>& getSendQueue() const { return sendQueue; }
    [[nodiscard]] const moodycamel::ConcurrentQueue<ByteVec>& getReceiveQueue() const { return receiveQueue; }

    int receive(ByteVec& data);
    int send(const ByteVec& data);

  private:
    moodycamel::ConcurrentQueue<ByteVec> sendQueue;
    moodycamel::ConcurrentQueue<ByteVec> receiveQueue;

    int handleReceive();
    int flushSendQueue();

    friend class WorkerThread;
};

class NetworkThread {
  public:
    explicit NetworkThread(NetworkManager* network) : network(network) {}
    virtual ~NetworkThread() = default;

    virtual void start() = 0;
    virtual void stop() {
        if (running.exchange(true)) {
            running = false;
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

  protected:
    NetworkManager*   network;
    std::thread       thread;
    std::atomic<bool> running = false;
};

class BossThread final : public NetworkThread {
  public:
    BossThread(NetworkManager* network, const int workerThreads) : NetworkThread(network), workerThreads(workerThreads) {};

    void start() override;
    void stop() override;

  private:
    int                                        workerThreads;
    int                                        connectionCount = 0;
    std::vector<std::unique_ptr<WorkerThread>> workers;
};

class WorkerThread final : public NetworkThread {
  public:
    WorkerThread(NetworkManager* network, const int id) : NetworkThread(network), id(id) {}
    void start() override;
    void stop() override;

    void addConnection(std::shared_ptr<NetworkConnection> connection);
    void removeConnection(const std::shared_ptr<NetworkConnection>& connection);

    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] int getConnectionCount() const { return connectionCount; }

  private:
    int id;
    int connectionCount = 0;

    std::mutex                                                      connectionMutex;
    std::vector<std::shared_ptr<NetworkConnection>>                 connections;
    moodycamel::ConcurrentQueue<std::shared_ptr<NetworkConnection>> inConnectionQueue;

    void processIncomingConnections();

#ifdef __linux__
    int epollFd = -1;
#endif
};
} // namespace stratos

#endif // NETWORK_H
