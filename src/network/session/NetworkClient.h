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
#include "network/io/Socket.h"
#include "network/protocol/handler/PacketConfigurationHandler.h"
#include "network/protocol/Packet.h"
#include "utils/crypto/CryptoUtils.h"
#include "utils/Types.h"

#include <memory>

namespace spdlog {
class logger;
}
namespace stratos::network {
class ClientboundPacket;
class ServerboundPacket;
class WorkerThread;
using SessionId = ClientInfo;
class NetworkManager;

struct SessionInfo {
    std::string username;
    UUID uuid;
};

class NetworkConnection final : public TCPConnection {
  public:
    using TCPConnection::receive;
    using TCPConnection::send;

    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port, NetworkManager* network, std::shared_ptr<spdlog::logger> logger, const std::shared_ptr<WorkerThread>& eventLoop) : TCPConnection(socketFd, address, port), network(network), logger(std::move(logger)), eventLoop(eventLoop) { changeState(Handshaking); }
    ~NetworkConnection() override = default;

    const ServerboundPacket* receivePacket();
    void                                              sendPacket(const ClientboundPacket* packet);
    int                                               handleReceive();
    void changeState(ProtocolState newState);
    bool                                              disconnect();
    bool                                              disconnect(const std::string& reason);
    bool                                              close() override;

    [[nodiscard]] const NetworkManager* getNetwork() const { return network; }
    [[nodiscard]] const std::shared_ptr<spdlog::logger>& getLogger() const { return logger; }
    [[nodiscard]] bool hasSendData() const { return sendQueue.size_approx() > 0; }
    [[nodiscard]] bool isDisconnected() const { return disconnected.load(std::memory_order_acquire); }
    [[nodiscard]] ProtocolState getState() const { return state; }
    [[nodiscard]] HandshakeIntent getIntent() const { return intent; }
    [[nodiscard]] std::optional<std::reference_wrapper<SessionInfo>> getSessionInfo() const { return sessionInfo ? std::make_optional(std::ref(*sessionInfo)) : std::nullopt; }
    void updateSessionInfo(SessionInfo&& info);
    void createNetworkSession();

  private:
    NetworkManager* network;

    ByteVec receiveBuf;
    moodycamel::ConcurrentQueue<const ClientboundPacket*> sendQueue = moodycamel::ConcurrentQueue<const ClientboundPacket*>();
    moodycamel::ConcurrentQueue<const ServerboundPacket*> receiveQueue = moodycamel::ConcurrentQueue<const ServerboundPacket*>();
    std::atomic<bool> disconnected = false;

    ProtocolState state;
    HandshakeIntent intent = HandshakeIntent::None;
    std::unique_ptr<PacketHandler> packetHandler;
    std::unique_ptr<SessionInfo> sessionInfo = nullptr;

    std::shared_ptr<spdlog::logger> logger;
    std::atomic<bool> dirty = false; // Indicates if the connection has data to send
    std::shared_ptr<WorkerThread> eventLoop;

    bool encryptionEnabled = false;
    const EVPKeyPtr* encryptionKey;
    std::vector<uint8_t> verifyToken; // Used for encryption handshake
    std::vector<uint8_t> clientSecret;

    int flushReceive();
    int flushSend();

    bool handleLegacyPing();

    friend class WorkerThread;
    friend class PacketLoginHandler;
};

class NetworkSession {
  public:
    explicit NetworkSession(NetworkManager* networkManager, SessionId id, std::shared_ptr<NetworkConnection> connection)
        : networkManager(networkManager), sessionId(std::move(id)), connection(std::move(connection)), packetHandler(std::make_unique<PacketConfigurationHandler>(this)) { beginConfiguration(); }
    ~NetworkSession() = default;

    [[nodiscard]] std::string getIp() const { return sessionId.ip; }
    [[nodiscard]] int         getPort() const { return sessionId.port; }
    [[nodiscard]] bool        isConnected() const { return !connection->isDisconnected(); }
    [[nodiscard]] bool        isStale() const { return !isConnected() && connection->isClosed(); }

    void tick();
    void beginConfiguration() const;
    void changeState(ProtocolState newState) const;
    void loginPlayer();
    void sendKeepAlive();
    void receiveKeepAlive(const ServerboundPacket* packet);

    template <typename T> void send(const T* packet) const { connection->sendPacket(packet); }

  private:
    NetworkManager* networkManager;
    SessionId       sessionId;
    std::shared_ptr<NetworkConnection>   connection;

    std::unique_ptr<PacketHandler> packetHandler;

    // Processes received packets
    void processReceived();
    void dispose() const;

    friend class NetworkManager;
    std::vector<int64_t> sentKeepAlives;
};

} // stratos::network

#endif //NETWORKCLIENT_H