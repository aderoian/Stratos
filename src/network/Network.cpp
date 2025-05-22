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

stratos::NetworkSession::~NetworkSession() {
    networkManager->getLogger()->info("Destroying network session for client {}:{}", sessionId.ip, sessionId.port);
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

    // Create and start a thread to handle incoming connections
    socketThread = std::thread([this] {
        while (running) {
            try {
                tickSocket();
            } catch (const std::exception& e) {
                logger->error("Socket Error: {}", e.what());
            }
        }
    });
    socketThread.detach();

    return true;
}
void stratos::NetworkManager::stop() {
    if (!running) throw std::runtime_error("Attempted to stop NetworkManager while it is not running");
    running = false;

    // Wait for the socket thread to finish
    socketThread.join();

    try {
        socketServer.close();
    } catch (const std::exception& e) {
        logger->error("Socket Error: {}", e.what());
    }
}
std::shared_ptr<stratos::NetworkSession> stratos::NetworkManager::getSession(const SessionId& sessionId) {
    std::shared_lock lock(sessionMutex);
    if (const auto it = sessions.find(sessionId); it != sessions.end()) return it->second;
    return nullptr;
}
std::shared_ptr<stratos::NetworkSession> stratos::NetworkManager::createSession(const ClientInfo& client) {
    std::unique_lock lock(sessionMutex);
    if (const auto it = sessions.find(client); it != sessions.end()) {
        // TODO: This could be due to a client loosing a connection and reconnecting, reuse session?
        logger->warn("Session already exists for client {}:{}", client.ip, client.port);
        return it->second; // Session already exists
    }
    // Create a new session
    logger->info("Creating new network session for client {}:{}", client.ip, client.port);
    auto             session = std::make_shared<NetworkSession>(this, client);
    sessions[client]         = session;
    return session;
}
bool stratos::NetworkManager::removeSession(const SessionId& sessionId) {
    std::unique_lock lock(sessionMutex);
    if (const auto it = sessions.find(sessionId); it != sessions.end()) {
        sessions.erase(it);
        return true;
    }
    return false;
}

void stratos::NetworkManager::tickSocket() {
    ClientInfo client{};
    try {
        client = socketServer.accept();
    } catch (const std::exception& e) {
        logger->error("Socket Error: {}", e.what());
        return;
    }

    if (client.socket == INVALID_SOCKET_FD) {
        return; // No new connection
    }

    // TODO: Handle new connection
    logger->info("New connection from {}:{}", client.ip, client.port);
    createSession(client);
}