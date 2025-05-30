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

#include "NetworkClient.h"

#include "Network.h"
#include "protocol/PacketSerialization.h"
#include "spdlog/logger.h"

namespace stratos {
void NetworkSession::tick() {
    if (!connected) return;

    if (connection->isClosed()) connected = false; // TODO: Handle connection close

    // Empty received queue
    // TODO: Should we always empty or consume a fix amount per tick?
    processReceived();

    // Attempt to empty the recvBuffer
    handleRawReceived();
}
void NetworkSession::send(const ByteVec& data) const {
    if (!isStale()) connection->send(data);
}
void NetworkSession::send(ClientboundPacket& packet) const {
    send(std::move(packet));
}
void NetworkSession::send(ClientboundPacket&& packet) const {
    if (!isStale()) {
        PacketBuffer buffer;
        buffer.writeVarInt(packet.getId());
        packet.encrypt(buffer);
        connection->send(buffer.getBuffer());
    }
}
void NetworkSession::sendLegacyPong() const {
    send(LegacyServerListPong(47, "1.21.5", "A Minecraft Server", 0, 20));
    connection->close();
}
void NetworkSession::handleClientHandshake(const ClientHandshake& packet) {
    if (packet.intent == ClientHandshake::Intent::Status)
        protocolState = Status;
}
void NetworkSession::handleStatusRequest() const {
    if (protocolState == Status) {
        send(StatusResponse(
            R"({"version":{"name":"1.21.5","protocol":770},"players":{"max":20,"online":0,"sample":[]},"description":{"text":"A Minecraft Server"}})"));
    }
}
void NetworkSession::handlePingRequest(const int64_t timestamp) const {
    if (protocolState == Status)
        send(PongResponse(timestamp));
}
void NetworkSession::processReceived() {
    ByteVec segment;
    while (connection->receive(segment) > 0) {
        recvBuffer.insert(recvBuffer.end(), std::make_move_iterator(segment.begin()), std::make_move_iterator(segment.end()));
        segment.clear();
    }
}
void NetworkSession::handleRawReceived() {
    size_t offset = 0;
    while (recvBuffer.size() > 0) {
        if (protocolState == Handshaking) {
            // Attempt to read the LegacyServerListPing
            try {
                size_t legacyPingOffset = 0;
                if (const uint8_t id = readUnsignedByte(recvBuffer, legacyPingOffset); id == LegacyServerListPing::ID) {
                    PacketBuffer buffer(recvBuffer, legacyPingOffset);
                    LegacyServerListPing packet;
                    packet.decrypt(buffer);
                    packet.handle(*this);

                    const size_t newOffset = buffer.getOffset();
                    recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + newOffset);
                    continue;
                }
            } catch (PacketSerializationException & ignored) {}
        }

        try {
            const int packetLength = readVarInt(recvBuffer, offset);
            if (packetLength <= 0 || packetLength > recvBuffer.size() - offset) {
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
void NetworkSession::dispose() const {
    networkManager->getLogger()->info("Disposing network session for client {}:{}", sessionId.ip, sessionId.port);
    ByteVec buffer;
    while (connection->receive(buffer) > 0) {
        buffer.clear();
    } // Empty the received queue
}
int  NetworkConnection::receive(ByteVec& data) {
    if (ByteVec buffer; receiveQueue.try_dequeue(buffer)) {
        data = std::move(buffer);
        return static_cast<int>(data.size());
    }
    return 0;
}
int NetworkConnection::send(const ByteVec& data) {
    ByteVec sendBuffer;
    writeVarInt(sendBuffer, static_cast<int>(data.size()));
    sendBuffer.insert(sendBuffer.end(), data.begin(), data.end());
    sendQueue.enqueue(sendBuffer);

#ifdef __linux__
    if (bool expected = false; dirty.compare_exchange_strong(expected, true))
        eventLoop->notifySend(socketFd);
#endif
    return static_cast<int>(sendBuffer.size());
}
int NetworkConnection::handleReceive() {
    ByteVec buffer;
    ByteVec segment;
    segment.resize(mtu);
    int totalReceived = 0;

    while (true) {
        int received              = 0;
        totalReceived += received = receive(mtu, segment);
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
int NetworkConnection::flushSendQueue() {
    ByteVec buffer;
    buffer.reserve(mtu);

    int totalBytesSent = 0;
    while (sendQueue.try_dequeue(buffer)) {
        const int bytesSent = send(buffer, static_cast<int>(buffer.size()), 0);
        if (bytesSent == SOCKET_ERROR)
            return -1;
        totalBytesSent += bytesSent;
    }

    return totalBytesSent;
}
} // stratos