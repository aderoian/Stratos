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

#include <memory>

namespace stratos {
using SessionId = ClientInfo;
class NetworkManager;

class NetworkConnection final : public TCPConnection {
  public:
    using TCPConnection::receive;
    using TCPConnection::send;

#ifdef __linux__
    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port, std::shared_ptr<WorkerThread> eventLoop) : TCPConnection(socketFd, address, port), eventLoop(std::move(eventLoop)) {}
#else
    NetworkConnection(const SocketFd socketFd, const std::string& address, const int& port) : TCPConnection(socketFd, address, port) {}
#endif
    ~NetworkConnection() override = default;

    [[nodiscard]] const moodycamel::ConcurrentQueue<ByteVec>& getSendQueue() const { return sendQueue; }
    [[nodiscard]] const moodycamel::ConcurrentQueue<ByteVec>& getReceiveQueue() const { return receiveQueue; }

    int receive(ByteVec& data);
    int send(const ByteVec& data);

  private:
    moodycamel::ConcurrentQueue<ByteVec> sendQueue = moodycamel::ConcurrentQueue<ByteVec>();
    moodycamel::ConcurrentQueue<ByteVec> receiveQueue = moodycamel::ConcurrentQueue<ByteVec>();
#ifdef __linux__
    std::atomic<bool> dirty = false; // Indicates if the connection has data to send
    std::shared_ptr<WorkerThread> eventLoop;
#endif

    int handleReceive();
    int flushSendQueue();

    friend class WorkerThread;
};

class NetworkSession {
  public:
    explicit NetworkSession(NetworkManager* networkManager, SessionId id, std::shared_ptr<NetworkConnection> connection)
        : networkManager(networkManager), sessionId(std::move(id)), connection(std::move(connection)) {}
    ~NetworkSession() = default;

    [[nodiscard]] std::string getIp() const { return sessionId.ip; }
    [[nodiscard]] int         getPort() const { return sessionId.port; }
    [[nodiscard]] bool        isConnected() const { return connected; }
    [[nodiscard]] bool        isStale() const { return !connected && connection->isClosed(); }

    void tick();

    void send(const ByteVec& data) const;
    void send(ClientboundPacket& packet) const;
    void send(ClientboundPacket&& packet) const;

    void sendLegacyPong() const;
    void handleClientHandshake(const ClientHandshake& packet);
    void handleStatusRequest() const;
    void handlePingRequest(int64_t timestamp) const;


  private:
    NetworkManager* networkManager;
    SessionId       sessionId;
    std::shared_ptr<NetworkConnection>   connection;

    ByteVec recvBuffer;

    ProtocolState protocolState = Handshaking;
    ClientHandshake::Intent sessionIntent = ClientHandshake::Intent::None;
    bool connected = true;

    // Clears the received segments and moves the data to the recvBuffer
    void processReceived();
    // Handles the raw received data, frames data into received packet(s), then handles the packet(s) if any
    void handleRawReceived();
    void dispose() const;

    friend class NetworkManager;
};

} // stratos

#endif //NETWORKCLIENT_H
