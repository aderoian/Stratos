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

#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include "concurrentqueue.h"
#include "protocol/Packet.h"
#include "protocol/PacketCodec.h"
#include "Socket.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <optional>

namespace stratos {
class WorkerThread;
using SessionId = ClientInfo;
class NetworkManager;

class NetworkConnection final : public TCPConnection {
  public:
    using TCPConnection::receive;
    using TCPConnection::send;

#ifdef __linux__
    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port, std::shared_ptr<spdlog::logger> logger, std::shared_ptr<WorkerThread> eventLoop) : TCPConnection(socketFd, address, port), logger(std::move(logger)), eventLoop(std::move(eventLoop)) { changeState(Handshaking); }
#else
    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port, std::shared_ptr<spdlog::logger> logger) : TCPConnection(socketFd, address, port), logger(std::move(logger)) { changeState(Handshaking); }
#endif
    ~NetworkConnection() override = default;

    std::optional<std::unique_ptr<ServerboundPacket>> receivePacket();
    void                                              sendPacket(std::unique_ptr<ClientboundPacket>&& packet);
    int                                               handleReceive();
    void changeState(ProtocolState newState);
    bool                                              disconnect();
    bool                                              close() override;

    [[nodiscard]] bool hasSendData() const { return sendQueue.size_approx() > 0; }
    [[nodiscard]] bool isDisconnected() const { return disconnected.load(std::memory_order_acquire); }
    [[nodiscard]] ProtocolState getState() const { return state; }
    [[nodiscard]] ClientHandshake::Intent getIntent() const { return intent; }

  private:
    ByteVec receiveBuf;
    moodycamel::ConcurrentQueue<std::unique_ptr<ClientboundPacket>> sendQueue = moodycamel::ConcurrentQueue<std::unique_ptr<ClientboundPacket>>();
    moodycamel::ConcurrentQueue<std::unique_ptr<ServerboundPacket>> receiveQueue = moodycamel::ConcurrentQueue<std::unique_ptr<ServerboundPacket>>();
    std::atomic<bool> disconnected = false;

    ProtocolState state;
    ClientHandshake::Intent intent = ClientHandshake::Intent::None;
    std::unique_ptr<PacketHandler> packetHandler;

    std::shared_ptr<spdlog::logger> logger;
#ifdef __linux__
    std::atomic<bool> dirty = false; // Indicates if the connection has data to send
    std::shared_ptr<WorkerThread> eventLoop;
#endif
    int flushReceive();
    int flushSend();

    bool handleLegacyPing();

    friend class WorkerThread;
};

class NetworkSession {
  public:
    explicit NetworkSession(NetworkManager* networkManager, SessionId id, std::shared_ptr<NetworkConnection> connection)
        : networkManager(networkManager), sessionId(std::move(id)), connection(std::move(connection)), packetHandler(std::make_unique<PlayPacketHandler>(this)) {}
    ~NetworkSession() = default;

    [[nodiscard]] std::string getIp() const { return sessionId.ip; }
    [[nodiscard]] int         getPort() const { return sessionId.port; }
    [[nodiscard]] bool        isConnected() const { return !connection->isDisconnected(); }
    [[nodiscard]] bool        isStale() const { return !isConnected() && connection->isClosed(); }

    void tick();

    template <typename T> void send(T& packet) const { send(std::move(packet)); }
    template <typename T> void send(T&& packet) const { connection->sendPacket(std::make_unique<T>(std::move(packet))); }

  private:
    NetworkManager* networkManager;
    SessionId       sessionId;
    std::shared_ptr<NetworkConnection>   connection;

    std::unique_ptr<PlayPacketHandler> packetHandler;

    // Processes received packets
    void processReceived();
    void dispose() const;

    friend class NetworkManager;
};

} // stratos

#endif //NETWORKCLIENT_H
