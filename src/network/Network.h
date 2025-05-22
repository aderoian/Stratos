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
#include "Socket.h"

#include <memory>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>

namespace spdlog {
class logger;
}
namespace stratos {
class Server;
class NetworkSession;

using SessionId = ClientInfo;

class NetworkManager final {
public:
    NetworkManager(Server* server, std::shared_ptr<spdlog::logger> logger, const std::string& address, const int& port) :
        server(server), logger(std::move(logger)), socketServer(address, port) {}
    NetworkManager(const NetworkManager&) = delete;
    ~NetworkManager() = default;

    bool start();
    void stop();

    std::shared_ptr<spdlog::logger> getLogger() const { return logger; }
    std::shared_ptr<NetworkSession> getSession(const SessionId& sessionId);

    NetworkManager& operator=(NetworkManager&) = delete;

protected:
    std::shared_ptr<NetworkSession> createSession(const ClientInfo& client);
    bool removeSession(const SessionId& sessionId);

private:
    Server* server;
    std::shared_ptr<spdlog::logger> logger;

    std::shared_mutex sessionMutex;
    std::unordered_map<SessionId, std::shared_ptr<NetworkSession>> sessions;

    TCPServer socketServer;
    std::thread socketThread;

    std::atomic<bool> running;

    void tickSocket();
};

class NetworkSession {
public:
    explicit NetworkSession(NetworkManager* networkManager, const ClientInfo& client) : networkManager(networkManager), sessionId{client.socket, client.ip, client.port}, socket(client.socket, client.ip, client.port) {}
    ~NetworkSession();

    [[nodiscard]] std::string getIp() const { return sessionId.ip; }
    [[nodiscard]] int         getPort() const { return sessionId.port; }
private:
    NetworkManager* networkManager;
    SessionId sessionId;
    TCPConnection socket;
};

} // namespace stratos

#endif //NETWORK_H
