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
    if (!isConnected()) return;

    // Empty received queue
    // TODO: Should we always empty or consume a fix amount per tick?
    processReceived();
}
void NetworkSession::processReceived() {
    while (true) {
        std::optional<std::unique_ptr<ServerboundPacket>> optionalPacket = connection->receivePacket();
        if (!optionalPacket) break; // No more packets to process
        if (auto packet = std::move(*optionalPacket); !packetHandler->handle(*packet)) {
            networkManager->getLogger()->warn("Unhandled packet with ID {} from client {}:{}", packet->getId(), sessionId.ip, sessionId.port);
        }
    }
}
std::optional<std::unique_ptr<ServerboundPacket>> NetworkConnection::receivePacket() {
    if (isDisconnected()) return std::nullopt;
    if (std::unique_ptr<ServerboundPacket> packet; receiveQueue.try_dequeue(packet)) {
        return std::move(packet);
    }
    return std::nullopt;
}
void NetworkConnection::sendPacket(std::unique_ptr<ClientboundPacket>&& packet) {
    if (isDisconnected()) return;
    sendQueue.enqueue(std::move(packet));
    if (bool expected = false; dirty.compare_exchange_strong(expected, true)) eventLoop->notifySend(socketFd);
}
int NetworkConnection::handleReceive() {
    const int received = flushReceive();
    if (received <= 0) return received; // Connection closed or error

    size_t offset = 0;
    while (!receiveBuf.empty()) {
        if (handleLegacyPing()) {
            // Legacy ping handled, continue to next iteration
            continue;
        }

        try {
            const int packetLength = readVarInt(receiveBuf, offset);
            if (packetLength <= 0 || packetLength > receiveBuf.size() - offset) {
                // Not enough data to read a full packet, wait for more data
                return received;
            }

            PacketBuffer packetBuffer(receiveBuf, offset);
            try {
                const int  packetId  = packetBuffer.readVarInt();
                auto       packetKey = PacketKey{state, Serverbound, packetId};
                auto packet    = PacketRegistry::instance().create(packetKey);
                if (!packet) {
                    logger->error("Received unknown packet with ID {} from client {}:{}", packetId, address, port);
                    receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + offset + packetLength);
                    return received;
                }

                packet->decrypt(packetBuffer);
                if (!packet->accept(*packetHandler)) {
                    std::unique_ptr<ServerboundPacket> casted{
                        dynamic_cast<ServerboundPacket*>(packet.release())
                    };
                    receiveQueue.enqueue(std::move(casted)); // Enqueue the packet for further processing
                }
            } catch (const PacketSerializationException& e) {
                logger->error("Failed to read packet from client {}:{}: {}", address, port, e.what());
            } catch (const std::exception& e) {
                logger->error("Encountered an exception when handing a packet for client {}:{}: {}", address, port, e.what());
            }

            receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + offset + packetLength);
            offset = 0; // Reset offset for the next packet
        } catch (const PacketSerializationException& ignored) { // Failed to read packet length
            // Not enough data to read a packet, wait for more data
            break;
        } catch (const std::exception& e) {
            logger->error("Failed to read packet from client {}:{}: {}", address, port, e.what());
        }
    }
    return received;
}
void NetworkConnection::changeState(const ProtocolState newState) {
    state = newState;
    switch (state) {
    case Handshaking:
        packetHandler = std::make_unique<HandshakePacketHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Status:
        packetHandler = std::make_unique<StatusPacketHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Login:
        packetHandler = std::make_unique<LoginPacketHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Configuration:
        packetHandler = std::make_unique<ConfigurationPacketHandler>(this);
        receiveBuf.reserve(1024);
        break;
    case Play:
        packetHandler = std::make_unique<PacketHandler>(); // Network connection does not handle play packets directly
        receiveBuf.reserve(4096);
    }
}
bool NetworkConnection::disconnect() {
    if (bool expected = false; !disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) return false;
    return true;
}
bool NetworkConnection::disconnect(const std::string& reason) {
    if (bool expected = false; !disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) return false;
    if (state == Login)
        sendPacket(std::make_unique<LoginDisconnect>(reason.data()));
    return true;
}
bool NetworkConnection::close() {
    if (TCPConnection::close()) {
        bool expected = false;
        disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel);

        // Clear queues and buffers
        receiveBuf.clear();
        std::unique_ptr<ServerboundPacket> receiveConsumer;
        while (receiveQueue.try_dequeue(receiveConsumer)) {
        }
        std::unique_ptr<ClientboundPacket> sendConsumer;
        while (sendQueue.try_dequeue(sendConsumer)) {
        }
        return true;
    }
    return false;
}
void NetworkConnection::updateSessionInfo(SessionInfo&& info) {
    if (sessionInfo) {
        sessionInfo->username = std::move(info.username);
        sessionInfo->uuid     = std::move(info.uuid);
    } else {
        sessionInfo = std::make_unique<SessionInfo>(std::move(info));
    }
}
int NetworkConnection::flushReceive () {
    int totalReceived = 0;
    ByteVec segment;
    segment.resize(1050);
    while (true) {
        const int received = receive(1050, segment);
        if (received == 0) return 0; // Connection closed
        if (received < 0) break;

        totalReceived += received;
        if (encryptionEnabled) {
            try {
                ByteVec decrypted = aesDecryptCFB8(clientSecret, clientSecret, segment);
                if (decrypted.empty()) {
                    logger->error("Failed to decrypt received data, disconnecting client {}:{}", address, port);
                    disconnect("Decryption failed");
                    return -1; // Decryption failed
                }
                receiveBuf.insert(receiveBuf.end(), decrypted.begin(), decrypted.begin() + received);
            } catch (std::runtime_error & e) {
                logger->error("Decryption error for client {}:{}: {}", address, port, e.what());
                disconnect("Decryption error");
                return -1; // Decryption error
            }
        } else {
            receiveBuf.insert(receiveBuf.end(), segment.begin(), segment.begin() + received);
        }
        segment.clear();
    }
    return totalReceived > 0 ? totalReceived : -1;
}
int NetworkConnection::flushSend() {
    ByteVec                            sendBuffer;
    std::unique_ptr<ClientboundPacket> packet;
    while (sendQueue.try_dequeue(packet)) {
        if (!packet) continue; // Skip empty packets
        PacketBuffer pkBuf;
        pkBuf.writeVarInt(packet->getId());
        packet->encrypt(pkBuf);

        PacketBuffer framedBuf;
        framedBuf.writeVarInt(static_cast<int>(pkBuf.getSize()));
        framedBuf.append(pkBuf.getBuffer());
        if (encryptionEnabled) {
            ByteVec encrypted = aesEncryptCFB8(clientSecret, clientSecret, framedBuf.getBuffer());
            sendBuffer.insert(sendBuffer.end(), std::make_move_iterator(encrypted.begin()), std::make_move_iterator(encrypted.end()));
        } else {
            sendBuffer.insert(sendBuffer.end(), framedBuf.begin(), framedBuf.end());
        }
    }

    if (sendBuffer.empty()) return 0;
    return send(sendBuffer, sendBuffer.size(), 0);
}
bool NetworkConnection::handleLegacyPing() {
    if (state != Handshaking) return false;
    try {
        size_t legacyPingOffset = 0;
        if (const uint8_t id = readUnsignedByte(receiveBuf, legacyPingOffset); id == LegacyServerListPing::ID) {
            PacketBuffer buffer(receiveBuf, legacyPingOffset);
            LegacyServerListPing packet;
            packet.decrypt(buffer);

            packetHandler->handle(packet); // Handle legacy ping packet
            const size_t newOffset = buffer.getOffset();
            receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + newOffset);
            return true; // Legacy ping handled
        }
    } catch (PacketSerializationException & ignored) {}
    return false; // No legacy ping found
}
} // stratos