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

#include "PacketCodec.h"

#include "network/Network.h"
#include "network/NetworkClient.h"
#include "PacketSerialization.h"
#include "utils/UUID.h"

void stratos::ClientHandshake::decrypt(PacketBuffer& buffer) {
    protocolVersion = buffer.readVarInt();
    serverAddress   = buffer.readString(255);
    serverPort      = buffer.readUnsignedShort();

    // Read the intent
    intent = buffer.readVarIntEnum<Intent>([](const int& value) -> Intent {
        switch (value) {
        case 0x01:
            return Intent::Status;
        case 0x02:
            return Intent::Login;
        case 0x03:
            return Intent::Transfer;
        default:
            throw PacketSerializationException("Unknown intent value: " + std::to_string(value));
        }
    });
}
void stratos::LegacyServerListPing::decrypt(PacketBuffer& buffer) {
    payload = buffer.readByte();

    // None of this matters, but we need to read the payload to avoid deserialization errors
    buffer.readByte(); // Packet identifier
    buffer.readStringUTF16BE(); // MC|Pinghost
    buffer.readShort(); // Remaining length
    buffer.readByte(); // Protocol version
    buffer.readStringUTF16BE(); // Server address
    buffer.readInt(); // Server port
}
void stratos::LegacyServerListPong::encrypt(PacketBuffer& buffer) {
    buffer.writeByte(0xFF); // Kick packet identifier
    const std::string payload =
        "§1\0" + std::to_string(protocolVersion) + "\0" + version + "\0" + motd + "\0" + "\0" + std::to_string(onlinePlayers) + "\0" + std::to_string(maxPlayers);
    buffer.writeStringUTF16BE(payload);
}
void stratos::StatusResponse::encrypt(PacketBuffer& buffer) {
    buffer.writeString(jsonResponse, 32767);
}
void stratos::PongResponse::encrypt(PacketBuffer& buffer) {
    buffer.writeLong(timestamp);
}
void stratos::StatusRequest::decrypt(PacketBuffer& buffer) {}
void stratos::PingRequest::decrypt(PacketBuffer& buffer) {
    timestamp = buffer.readLong();
}
void stratos::LoginStart::decrypt(PacketBuffer& buffer) {
    name = buffer.readString(16);
    uuid = buffer.readUUID();
}
void stratos::EncryptionResponse::decrypt(PacketBuffer& buffer) {
    sharedSecret = buffer.readByteArray(buffer.readVarInt());
    verifyToken  = buffer.readByteArray(buffer.readVarInt());
}
void stratos::LoginPluginResponse::decrypt(PacketBuffer& buffer) {
    messageId = buffer.readVarInt();
    data = buffer.readPrefixedOptionalInferredByteArray();
}
void stratos::LoginCookieResponse::decrypt(PacketBuffer& buffer) {
    cookie = buffer.readIdentifier();
    payload = buffer.readPrefixedOptionalPrefixedByteArray();
}
void stratos::LoginDisconnect::encrypt(PacketBuffer& buffer) {
    buffer.writeString(reason, 32767);
}
void stratos::EncryptionRequest::encrypt(PacketBuffer& buffer) {
    buffer.writeString(serverId, 20);
    buffer.writePrefixedByteArray(publicKey);
    buffer.writePrefixedByteArray(verifyToken);
    buffer.writeBoolean(shouldAuthenticate);
}
void stratos::LoginSuccess::encrypt(PacketBuffer& buffer) {
    buffer.writeUUID(uuid);
    buffer.writeString(username, 16);
    buffer.writeLoginProperty(properties);
}
void stratos::SetCompression::encrypt(PacketBuffer& buffer) {
    buffer.writeVarInt(threshold);
}
void stratos::LoginPluginRequest::encrypt(PacketBuffer& buffer) {
    buffer.writeVarInt(messageId);
    buffer.writeIdentifier(channel);
    buffer.writeByteArray(data);
}
void stratos::LoginCookieRequest::encrypt(PacketBuffer& buffer) {
    buffer.writeIdentifier(cookie);
}
bool stratos::HandshakePacketHandler::handle(ClientHandshake& packet) {
    switch (packet.intent) {
    case ClientHandshake::Intent::Status:
        connection->changeState(Status);
        break;
    case ClientHandshake::Intent::Login:
    case ClientHandshake::Intent::Transfer: // TODO: Figure out how to handle transfer
        connection->changeState(Login);
    default:;
    }
    return true;
}
bool stratos::HandshakePacketHandler::handle(LegacyServerListPing& packet) {
    connection->sendPacket(std::make_unique<LegacyServerListPong>(47, "1.21.5", "A Minecraft Server", 0, 20)); // TODO: Replace with actual server info
    connection->disconnect();
    return true;
}
bool stratos::StatusPacketHandler::handle(StatusRequest& packet) {
    if (connection->getState() == Status)
        connection->sendPacket(std::make_unique<StatusResponse>(
            R"({"version":{"name":"1.21.5","protocol":770},"players":{"max":20,"online":0,"sample":[]},"description":{"text":"A Minecraft Server"}})"));
    return true;
}
bool stratos::StatusPacketHandler::handle(PingRequest& packet) {
    if (connection->getState() == Status)
        connection->sendPacket(std::make_unique<PongResponse>(packet.timestamp));
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginStart& packet) {
    connection->updateSessionInfo({packet.name, generateOfflineUUID(packet.name)});
    if (connection->getNetwork()->useEncryption()) {
        connection->encryptionKey = &connection->getNetwork()->getEncryptionKey();
        std::vector<uint8_t> token = connection->verifyToken = generateRandomBytes(16);
        connection->sendPacket(std::make_unique<EncryptionRequest>("", encodeServerPublicKey(connection->encryptionKey), std::move(token), false));
    } else {
        connection->sendPacket(std::make_unique<LoginSuccess>(packet.uuid, std::move(packet.name), std::vector<LoginProperty>()));
    }
    return true;
}
bool stratos::LoginPacketHandler::handle(EncryptionResponse& packet) {
    if (const std::vector<uint8_t> decryptToken = rsaDecrypt(connection->encryptionKey, packet.verifyToken); decryptToken != connection->verifyToken) {
        connection->disconnect();
        return false;
    }
    connection->clientSecret = std::move(rsaDecrypt(connection->encryptionKey, packet.sharedSecret));
    connection->encryptionEnabled = true;
    SessionInfo sessionInfo = *connection->getSessionInfo();
    connection->sendPacket(std::make_unique<LoginSuccess>(sessionInfo.uuid, std::move(sessionInfo.username), std::vector<LoginProperty>()));
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginPluginResponse& packet) { return false; }
bool stratos::LoginPacketHandler::handle(LoginAcknowledge& packet) {
    connection->changeState(Configuration);
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginCookieResponse& packet) { return false; }
