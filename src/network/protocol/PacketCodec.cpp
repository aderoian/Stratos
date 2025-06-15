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

#include "../session/NetworkClient.h"
#include "network/Network.h"
#include "network/session/SessionAuth.h"
#include "nlohmann/detail/input/parser.hpp"
#include "PacketSerialization.h"
#include "Server.h"
#include "utils/config/Config.h"
#include "utils/UUID.h"

void stratos::ClientHandshake::decrypt(PacketBuffer& buffer) {
    protocolVersion = buffer.readVarInt();
    serverAddress   = buffer.readString(255);
    serverPort      = buffer.readUnsignedShort();

    // Read the intent
    intent = buffer.readVarIntEnum<HandshakeIntent>([](const int& value) -> HandshakeIntent {
        switch (value) {
        case 0x01:
            return HandshakeIntent::Status;
        case 0x02:
            return HandshakeIntent::Login;
        case 0x03:
            return HandshakeIntent::Transfer;
        default:
            throw PacketSerializationException("Unknown intent value: " + std::to_string(value));
        }
    });
}
void stratos::LegacyServerListPing::decrypt(PacketBuffer& buffer) {
    payload = buffer.readByte();

    // None of this matters, but we need to read the payload to avoid deserialization errors
    buffer.readByte();          // Packet identifier
    buffer.readStringUTF16BE(); // MC|Pinghost
    buffer.readShort();         // Remaining length
    buffer.readByte();          // Protocol version
    buffer.readStringUTF16BE(); // Server address
    buffer.readInt();           // Server port
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
    data      = buffer.readPrefixedOptionalInferredByteArray();
}
void stratos::LoginAcknowledge::decrypt(PacketBuffer& buffer) {}
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
void stratos::ConfigurationClientInformation::decrypt(PacketBuffer& buffer) {
    locale = buffer.readString(16);
    viewDistance = buffer.readByte();
    chatMode = buffer.readVarIntEnum<ChatMode>([](const int& value) -> ChatMode {
        switch (value) {
        case 0:
            return ChatMode::Enabled;
        case 1:
            return ChatMode::CommandsOnly;
        case 2:
            return ChatMode::Hidden;
        default:
            throw PacketSerializationException("Unknown chat mode value: " + std::to_string(value));
        }
    });
    chatColors = buffer.readBoolean();
    skinParts = buffer.readUnsignedByte();
    mainHand = buffer.readVarIntEnum<Hand>([](const int& value) -> Hand {
        switch (value) {
        case 0:
            return Hand::Left;
        case 1:
            return Hand::Right;
        default:
            throw PacketSerializationException("Unknown hand value: " + std::to_string(value));
        }
    });
    enableTextFiltering = buffer.readBoolean();
    allowServerListing = buffer.readBoolean();
    particleStatus = buffer.readVarIntEnum<ParticleStatus>([](const int& value) -> ParticleStatus {
        switch (value) {
        case 0:
            return ParticleStatus::All;
        case 1:
            return ParticleStatus::Decreased;
        case 2:
            return ParticleStatus::Minimal;
        default:
            throw PacketSerializationException("Unknown particle status value: " + std::to_string(value));
        }
    });
}
void stratos::ConfigurationCookieResponse::decrypt(PacketBuffer& buffer) {
    key = buffer.readIdentifier();
    value = buffer.readPrefixedOptionalPrefixedByteArray();
}
void stratos::ConfigurationServerPluginMessage::decrypt(PacketBuffer& buffer) {
    channel = buffer.readIdentifier();
    data    = buffer.readInferredByteArray();
}
void stratos::AcknowledgeFinishConfiguration::decrypt(PacketBuffer& buffer) {}
void stratos::ConfigurationServerboundKeepAlive::decrypt(PacketBuffer& buffer) {
    id = buffer.readLong();
}
void stratos::ConfigurationPong::decrypt(PacketBuffer& buffer) {
    id = buffer.readInt();
}
void stratos::ConfigurationResourcePackResponse::decrypt(PacketBuffer& buffer) {
    uuid = buffer.readUUID();
    result = buffer.readVarIntEnum<ResourcePackResult>([](const int& value) -> ResourcePackResult {
        switch (value) {
        case 0:
            return ResourcePackResult::SuccessfullyDownloaded;
        case 1:
            return ResourcePackResult::Declined;
        case 2:
            return ResourcePackResult::FailedDownload;
        case 3:
            return ResourcePackResult::Accepted;
        case 4:
            return ResourcePackResult::Downloaded;
        case 5:
            return ResourcePackResult::InvalidURL;
        case 6:
            return ResourcePackResult::FailedReload;
        case 7:
            return ResourcePackResult::Discarded;
        default:
            throw PacketSerializationException("Unknown resource pack result value: " + std::to_string(value));
        }
    });
}
void stratos::ServerboundKnownPacks::decrypt(PacketBuffer& buffer) {
    knownPacks = buffer.readPrefixedResourcePackHeaderArray();
}
void stratos::ConfigurationCookieRequest::encrypt(PacketBuffer& buffer) {
    buffer.writeIdentifier(key);
}
void stratos::ConfigurationClientboundPluginMessage::encrypt(PacketBuffer& buffer) {
    buffer.writeIdentifier(channel);
    buffer.writeByteArray(data);
}
void stratos::ConfigurationDisconnect::encrypt(PacketBuffer& buffer) {
    buffer.writeString(reason, 32767);
}
void stratos::FinishConfiguration::encrypt(PacketBuffer& buffer) {}
void stratos::ConfigurationClientboundKeepAlive::encrypt(PacketBuffer& buffer) {
    buffer.writeLong(id);
}
void stratos::ConfigurationPing::encrypt(PacketBuffer& buffer) {
    buffer.writeInt(id);
}
void stratos::ResetChat::encrypt(PacketBuffer& buffer) {}
void stratos::RegistryDataPacket::encrypt(PacketBuffer& buffer) {
    buffer.writeIdentifier(registryKey);
    buffer.writePrefixedRegistryEntryArray(entries);
}
void stratos::ConfigurationRemoveRemoveResourcePack::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedOptionalUUID(uuid);
}
void stratos::ConfigurationAddResourcePack::encrypt(PacketBuffer& buffer) {
    buffer.writeUUID(uuid);
    buffer.writeString(url, 32767);
    buffer.writeString(hash, 40);
    buffer.writeBoolean(forced);
    buffer.writePrefixedOptionalString(prompt, 32767);
}
void stratos::ConfigurationStoreCookie::encrypt(PacketBuffer& buffer) {
    buffer.writeIdentifier(key);
    buffer.writePrefixedByteArray(value);
}
void stratos::ConfigurationTransfer::encrypt(PacketBuffer& buffer) {
    buffer.writeString(host, 255);
    buffer.writeVarInt(port);
}
void stratos::FeatureFlags::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedIdentifierArray(features);
}
void stratos::ConfigurationUpdateTags::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedRegistryTagDataArray(tags);
}
void stratos::ClientboundKnownPacks::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedResourcePackHeaderArray(knownPackets);
}
void stratos::ConfigurationCustomReportDetails::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedReportDetailArray(details);
}
void stratos::ConfigurationServerLinks::encrypt(PacketBuffer& buffer) {
    buffer.writePrefixedServerLinkArray(links);
}
void stratos::LoginPlay::encrypt(PacketBuffer& buffer) {
    buffer.writeInt(entityId);
    buffer.writeBoolean(isHardcore);
    buffer.writePrefixedIdentifierArray(dimensions);
    buffer.writeVarInt(maxPlayers);
    buffer.writeVarInt(viewDistance);
    buffer.writeVarInt(simulationDistance);
    buffer.writeBoolean(reducedDebugInfo);
    buffer.writeBoolean(enableRespawnScreen);
    buffer.writeBoolean(doLimitedCrafting);
    buffer.writeVarInt(dimensionType);
    buffer.writeIdentifier(dimensionName);
    buffer.writeLong(hashedSeed);
    buffer.writeVarInt(gamemode);
    buffer.writeVarInt(previousGamemode);
    buffer.writeBoolean(debug);
    buffer.writeBoolean(flat);
    buffer.writeBoolean(hasDeathLocation);
    if (hasDeathLocation) {
        buffer.writeIdentifier(deathDimension.value());
        buffer.writePosition(deathPosition.value());
    }
    buffer.writeVarInt(portalCooldown);
    buffer.writeVarInt(seaLevel);
    buffer.writeBoolean(enforcesSecureChat);
}
bool stratos::HandshakePacketHandler::handle(ClientHandshake& packet) {
    switch (packet.intent) {
    case HandshakeIntent::Status:
        connection->changeState(Status);
        break;
    case HandshakeIntent::Login:
    case HandshakeIntent::Transfer: // TODO: Figure out how to handle transfer
        connection->changeState(Login);
    default:;
    }
    return true;
}
bool stratos::HandshakePacketHandler::handle(LegacyServerListPing& packet) {
    connection->sendPacket(std::make_unique<LegacyServerListPong>(47, PROTOCOL_VERSION_STRING, server->getMotd(), server->getOnlinePlayers(), server->getServerProperties()->getProperty("max-players").value().get().asInt()));
    connection->disconnect();
    return true;
}
bool stratos::StatusPacketHandler::handle(StatusRequest& packet) {
    if (connection->getState() == ProtocolState::Status) {
        constexpr auto STATUS_RESPONSE_FORMAT = R"({{"version":{{"name":"{}","protocol":{}}},"players":{{"max":{},"online":{},"sample":[]}},"description":{{"text":"{}"}}}})";
        connection->sendPacket(std::make_unique<StatusResponse>(
            std::format(STATUS_RESPONSE_FORMAT, std::string(PROTOCOL_VERSION_STRING), PROTOCOL_VERSION, server->getMaxPlayers(), server->getOnlinePlayers(), server->getMotd())));
    }
    return true;
}
bool stratos::StatusPacketHandler::handle(PingRequest& packet) {
    if (connection->getState() == ProtocolState::Status)
        connection->sendPacket(std::make_unique<PongResponse>(packet.timestamp));
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginStart& packet) {
    if (connection->getNetwork()->useEncryption()) {
        connection->updateSessionInfo({packet.name, packet.uuid});
        connection->encryptionKey = &connection->getNetwork()->getEncryptionKey();
        std::vector<uint8_t> token = connection->verifyToken = generateRandomBytes(16);
        connection->sendPacket(std::make_unique<EncryptionRequest>(server->getName(), encodeServerPublicKey(connection->encryptionKey), std::move(token), server->isOnlineMode()));
    } else {
        connection->updateSessionInfo({packet.name, generateOfflineUUID(packet.name)});
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
    connection->encryptionEnabled = false;

    if (server->isOnlineMode()) {
        authenticate(connection, server->getName(), connection->clientSecret, *connection->encryptionKey);
    } else {
        std::string username = connection->getSessionInfo()->get().username;
        connection->updateSessionInfo({username, generateOfflineUUID(username)});
        connection->sendPacket(std::make_unique<LoginSuccess>(connection->getSessionInfo()->get().uuid, std::move(username), std::vector<LoginProperty>()));
    }
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginPluginResponse& packet) { return false; }
bool stratos::LoginPacketHandler::handle(LoginAcknowledge& packet) {
    connection->createNetworkSession();
    connection->changeState(Configuration);
    return true;
}
bool stratos::LoginPacketHandler::handle(LoginCookieResponse& packet) { return false; }
bool stratos::ConfigurationPacketHandler::handle(ConfigurationClientInformation& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(ConfigurationCookieResponse& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(ConfigurationServerPluginMessage& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(AcknowledgeFinishConfiguration& packet) {
    session->changeState(Play);
    session->loginPlayer();
    return true;
}
bool stratos::ConfigurationPacketHandler::handle(ConfigurationServerboundKeepAlive& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(ConfigurationPong& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(ConfigurationResourcePackResponse& packet) {
    return PacketHandler::handle(packet);
}
bool stratos::ConfigurationPacketHandler::handle(ServerboundKnownPacks& packet) {
    return PacketHandler::handle(packet);
}
