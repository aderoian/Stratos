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

#ifndef PACKETCODEC_H
#define PACKETCODEC_H
#include "math/Position.h"
#include "Packet.h"
#include "utils/Types.h"

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

#define PROTOCOL_VERSION 770
#define PROTOCOL_VERSION_STRING "1.21.5"

namespace stratos {
class ServerboundKnownPacks;
class ConfigurationResourcePackResponse;
class ConfigurationPong;
class ConfigurationServerboundKeepAlive;
class AcknowledgeFinishConfiguration;
class ConfigurationServerPluginMessage;
class ConfigurationCookieResponse;
class ConfigurationClientInformation;
class EncryptionResponse;
class LoginCookieResponse;
class LoginAcknowledge;
class LoginPluginResponse;
class LoginStart;
class PingRequest;
class StatusRequest;
class LegacyServerListPing;
class ClientHandshake;
class NetworkConnection;

using UUID = std::array<uint8_t, 16>;

class PacketHandler {
public:
    virtual ~PacketHandler() = default;
    virtual bool handle(Packet&) { return false; }

    virtual bool handle(ClientHandshake&) { return false; }
    virtual bool handle(LegacyServerListPing&) { return false; }
    virtual bool handle(StatusRequest&) { return false; }
    virtual bool handle(PingRequest&) { return false; }

    virtual bool handle(LoginStart&) { return false; }
    virtual bool handle(EncryptionResponse&) { return false; }
    virtual bool handle(LoginPluginResponse&) { return false; }
    virtual bool handle(LoginAcknowledge&) { return false; }
    virtual bool handle(LoginCookieResponse&) { return false; }

    virtual bool handle(ConfigurationClientInformation&) { return false; }
    virtual bool handle(ConfigurationCookieResponse&) { return false; }
    virtual bool handle(ConfigurationServerPluginMessage&) { return false; }
    virtual bool handle(AcknowledgeFinishConfiguration&) { return false; }
    virtual bool handle(ConfigurationServerboundKeepAlive&) { return false; }
    virtual bool handle(ConfigurationPong&) { return false; }
    virtual bool handle(ConfigurationResourcePackResponse&) { return false; }
    virtual bool handle(ServerboundKnownPacks&) { return false; }
};

#define SERVERBOUND_PACKET_FOOTER(clazz) \
bool accept(PacketHandler& handler) override { return handler.handle(*this); } \
~clazz() override = default; \
void decrypt(PacketBuffer& buffer) override;
#define CLIENTBOUND_PACKET_FOOTER(clazz) \
~clazz() override = default; \
void encrypt(PacketBuffer& buffer) override;

// Handshake Packets

class ClientHandshake final : public ServerboundPacket {
  public:
    constexpr static int ID = 0x00;

    int protocolVersion;
    std::string serverAddress;
    uint16_t serverPort;
    HandshakeIntent intent;
    explicit ClientHandshake() : Packet(ID), ServerboundPacket(ID), protocolVersion(0), serverPort(0), intent() {}
    SERVERBOUND_PACKET_FOOTER(ClientHandshake)
};

class LegacyServerListPing final : public ServerboundPacket {
public:
    constexpr static int ID = 0xFE;
    uint8_t payload = 0x01; // Legacy server list ping payload

    explicit LegacyServerListPing() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(LegacyServerListPing)
};

class LegacyServerListPong final : public ClientboundPacket {
public:
    constexpr static int ID = 0xFF;
    int protocolVersion;
    std::string version;
    std::string motd;
    int onlinePlayers;
    int  maxPlayers;

    LegacyServerListPong() : Packet(ID), ClientboundPacket(ID), protocolVersion(0), onlinePlayers(0), maxPlayers(0) {}
    LegacyServerListPong(const int protocol_version, std::string  version, std::string  motd, const int online_players, const int max_players)
        : Packet(ID), ClientboundPacket(ID), protocolVersion(protocol_version), version(std::move(version)), motd(std::move(motd)), onlinePlayers(online_players), maxPlayers(max_players) {}
    CLIENTBOUND_PACKET_FOOTER(LegacyServerListPong)
};

// Status Packets

class StatusResponse final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string          jsonResponse;

    StatusResponse() : Packet(ID), ClientboundPacket(ID) {}
    explicit StatusResponse(std::string&& jsonResponse) : Packet(ID), ClientboundPacket(ID), jsonResponse(std::move(jsonResponse)) {}
    CLIENTBOUND_PACKET_FOOTER(StatusResponse)
};

class PongResponse final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;
    int64_t timestamp;

    PongResponse() : Packet(ID), ClientboundPacket(ID), timestamp(0) {}
    explicit PongResponse(const int64_t timestamp) : Packet(ID), ClientboundPacket(ID), timestamp(timestamp) {}
    CLIENTBOUND_PACKET_FOOTER(PongResponse)
};

class StatusRequest final : public ServerboundPacket {
public:
    constexpr static int ID = 0x00;

    explicit StatusRequest() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(StatusRequest)
};

class PingRequest final : public ServerboundPacket {
  public:
    constexpr static int ID = 0x01;
    int64_t timestamp = 0;

    explicit PingRequest() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(PingRequest)
};

// Login Packets

class LoginStart final : public ServerboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string name; // String(16)
    UUID uuid;

    LoginStart() : Packet(ID), ServerboundPacket(ID), uuid() {}
    SERVERBOUND_PACKET_FOOTER(LoginStart)
};

class EncryptionResponse final : public ServerboundPacket {
public:
    constexpr static int ID = 0x01;
    std::vector<uint8_t> sharedSecret; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray

    EncryptionResponse() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(EncryptionResponse)
};

class LoginPluginResponse final : public ServerboundPacket {
public:
    constexpr static int ID = 0x02;
    int messageId; // VarInt
    std::optional<std::vector<uint8_t>> data; // prefixed optional ByteArray

    LoginPluginResponse() : Packet(ID), ServerboundPacket(ID), messageId(0), data() {}
    SERVERBOUND_PACKET_FOOTER(LoginPluginResponse)
};

class LoginAcknowledge final : public ServerboundPacket {
public:
    constexpr static int ID = 0x03;

    LoginAcknowledge() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(LoginAcknowledge)
};

class LoginCookieResponse final : public ServerboundPacket {
public:
    constexpr static int ID = 0x04;
    Identifier cookie;
    std::optional<std::vector<uint8_t>> payload; // prefixed optional ByteArray

    LoginCookieResponse() : Packet(ID), ServerboundPacket(ID), cookie({"",""}) {}
    SERVERBOUND_PACKET_FOOTER(LoginCookieResponse)
};

class LoginDisconnect final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string reason; // JSON Text Component

    LoginDisconnect() : Packet(ID), ClientboundPacket(ID) {}
    explicit LoginDisconnect(std::string&& reason) : Packet(ID), ClientboundPacket(ID), reason(std::move(reason)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginDisconnect)
};

class EncryptionRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;
    std::string serverId; // String(20)
    std::vector<uint8_t> publicKey; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray
    bool shouldAuthenticate;

    EncryptionRequest() : Packet(ID), ClientboundPacket(ID), shouldAuthenticate(false) {}
    EncryptionRequest(std::string&& serverId, std::vector<uint8_t>&& publicKey, std::vector<uint8_t>&& verifyToken, const bool shouldAuthenticate)
        : Packet(ID), ClientboundPacket(ID), serverId(std::move(serverId)), publicKey(std::move(publicKey)), verifyToken(std::move(verifyToken)), shouldAuthenticate(shouldAuthenticate) {}
    CLIENTBOUND_PACKET_FOOTER(EncryptionRequest)
};

class LoginSuccess final : public ClientboundPacket {
public:
    constexpr static int ID = 0x02;
    UUID uuid;
    std::string username; // String(16)
    std::vector<LoginProperty> properties; // prefixed array(16)

    LoginSuccess() : Packet(ID), ClientboundPacket(ID), uuid() {}
    LoginSuccess(const UUID& uuid, std::string&& username, std::vector<LoginProperty>&& properties)
        : Packet(ID), ClientboundPacket(ID), uuid(uuid), username(std::move(username)), properties(std::move(properties)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginSuccess)
};

class SetCompression final : public ClientboundPacket {
public:
    constexpr static int ID = 0x03;
    int threshold; // VarInt

    SetCompression() : Packet(ID), ClientboundPacket(ID), threshold(0) {}
    explicit SetCompression(const int threshold) : Packet(ID), ClientboundPacket(ID), threshold(threshold) {}
    CLIENTBOUND_PACKET_FOOTER(SetCompression)
};

class LoginPluginRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x04;
    int messageId; // VarInt
    Identifier channel;
    std::vector<uint8_t> data; // ByteArray

    LoginPluginRequest() : Packet(ID), ClientboundPacket(ID), messageId(0), channel({"",""}) {}
    LoginPluginRequest(const int messageId, Identifier channel, std::vector<uint8_t>&& data)
        : Packet(ID), ClientboundPacket(ID), messageId(messageId), channel(std::move(channel)), data(std::move(data)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginPluginRequest)
};

class LoginCookieRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x05;
    Identifier cookie;

    LoginCookieRequest() : Packet(ID), ClientboundPacket(ID), cookie({"",""}) {}
    explicit LoginCookieRequest(Identifier  cookie) : Packet(ID), ClientboundPacket(ID), cookie(std::move(cookie)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginCookieRequest)
};

// Configuration Packets

class ConfigurationClientInformation final : public ServerboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string locale; // String(16)
    int8_t viewDistance;
    ChatMode chatMode; // VarInt Enum
    bool chatColors;
    uint8_t skinParts;
    Hand mainHand; // VarInt Enum
    bool enableTextFiltering;
    bool allowServerListing;
    ParticleStatus particleStatus; // VarInt Enum

    ConfigurationClientInformation() : Packet(ID), ServerboundPacket(ID), viewDistance(0), chatMode(), chatColors(false), skinParts(0), mainHand(), enableTextFiltering(false), allowServerListing(false), particleStatus() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationClientInformation)
};

class ConfigurationCookieResponse final : public ServerboundPacket {
public:
    constexpr static int ID = 0x01;
    Identifier key;
    std::optional<std::vector<uint8_t>> value; // prefixed optional prefixed ByteArray(5120)

    ConfigurationCookieResponse() : Packet(ID), ServerboundPacket(ID), key({"",""}), value() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationCookieResponse)
};

class ConfigurationServerPluginMessage final : public ServerboundPacket {
public:
    constexpr static int ID = 0x02;
    Identifier channel;
    std::vector<uint8_t> data; // prefixed ByteArray(32767)

    ConfigurationServerPluginMessage() : Packet(ID), ServerboundPacket(ID), channel({"",""}), data() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationServerPluginMessage)
};

class AcknowledgeFinishConfiguration final : public ServerboundPacket {
public:
    constexpr static int ID = 0x03;

    AcknowledgeFinishConfiguration() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(AcknowledgeFinishConfiguration)
};

class ConfigurationServerboundKeepAlive final : public ServerboundPacket {
public:
    constexpr static int ID = 0x04;
    int64_t id;

    ConfigurationServerboundKeepAlive() : Packet(ID), ServerboundPacket(ID), id(0) {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationServerboundKeepAlive)
};

class ConfigurationPong final : public ServerboundPacket {
public:
    constexpr static int ID = 0x05;
    int id;

    ConfigurationPong() : Packet(ID), ServerboundPacket(ID), id(0) {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationPong)
};

class ConfigurationResourcePackResponse final : public ServerboundPacket {
public:
    constexpr static int ID = 0x06;
    UUID uuid;
    ResourcePackResult result; // VarInt Enum

    ConfigurationResourcePackResponse() : Packet(ID), ServerboundPacket(ID), uuid(), result() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationResourcePackResponse)
};

class ServerboundKnownPacks final : public ServerboundPacket {
public:
    constexpr static int ID = 0x07;
    std::vector<ResourcePackHeader> knownPacks; // prefixed array;

    ServerboundKnownPacks() : Packet(ID), ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(ServerboundKnownPacks)
};

class ConfigurationCookieRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;
    Identifier key;

    ConfigurationCookieRequest() : Packet(ID), ClientboundPacket(ID), key({"",""}) {}
    explicit ConfigurationCookieRequest(Identifier  key) : Packet(ID), ClientboundPacket(ID), key(std::move(key)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationCookieRequest)
};

class ConfigurationClientboundPluginMessage final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;
    Identifier channel;
    std::vector<uint8_t> data; // ByteArray

    ConfigurationClientboundPluginMessage() : Packet(ID), ClientboundPacket(ID), channel({"",""}) {}
    ConfigurationClientboundPluginMessage(Identifier channel, std::vector<uint8_t> data)
        : Packet(ID), ClientboundPacket(ID), channel(std::move(channel)), data(std::move(data)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationClientboundPluginMessage)
};

class ConfigurationDisconnect final : public ClientboundPacket {
public:
    constexpr static int ID = 0x02;
    std::string reason; // Text Component

    ConfigurationDisconnect() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationDisconnect(std::string&& reason) : Packet(ID), ClientboundPacket(ID), reason(std::move(reason)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationDisconnect)
};

class FinishConfiguration final : public ClientboundPacket {
public:
    constexpr static int ID = 0x03;

    FinishConfiguration() : Packet(ID), ClientboundPacket(ID) {}
    CLIENTBOUND_PACKET_FOOTER(FinishConfiguration)
};

class ConfigurationClientboundKeepAlive final : public ClientboundPacket {
public:
    constexpr static int ID = 0x04;
    int64_t id;

    ConfigurationClientboundKeepAlive() : Packet(ID), ClientboundPacket(ID), id(0) {}
    explicit ConfigurationClientboundKeepAlive(const int64_t id) : Packet(ID), ClientboundPacket(ID), id(id) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationClientboundKeepAlive)
};

class ConfigurationPing final : public ClientboundPacket {
public:
    constexpr static int ID = 0x05;
    int id;

    ConfigurationPing() : Packet(ID), ClientboundPacket(ID), id(0) {}
    explicit ConfigurationPing(const int id) : Packet(ID), ClientboundPacket(ID), id(id) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationPing)
};

class ResetChat final : public ClientboundPacket {
public:
    constexpr static int ID = 0x06;

    ResetChat() : Packet(ID), ClientboundPacket(ID) {}
    CLIENTBOUND_PACKET_FOOTER(ResetChat)
};

class RegistryDataPacket final : public ClientboundPacket {
public:
    constexpr static int ID = 0x07;
    Identifier registryKey;
    std::vector<RegistryEntry> entries;

    RegistryDataPacket() : Packet(ID), ClientboundPacket(ID), registryKey({"",""}) {}
    RegistryDataPacket(Identifier registryKey, std::vector<RegistryEntry>&& entries)
        : Packet(ID), ClientboundPacket(ID), registryKey(std::move(registryKey)), entries(std::move(entries)) {}
    CLIENTBOUND_PACKET_FOOTER(RegistryDataPacket)
};

class ConfigurationRemoveRemoveResourcePack final : public ClientboundPacket {
public:
    constexpr static int ID = 0x08;
    std::optional<UUID> uuid; // prefixed optional UUID

    ConfigurationRemoveRemoveResourcePack() : Packet(ID), ClientboundPacket(ID), uuid(std::nullopt) {}
    explicit ConfigurationRemoveRemoveResourcePack(const UUID& uuid) : Packet(ID), ClientboundPacket(ID), uuid(uuid) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationRemoveRemoveResourcePack)
};

class ConfigurationAddResourcePack final : public ClientboundPacket {
public:
    constexpr static int ID = 0x09;
    UUID uuid;
    std::string url; // String(32767)
    std::string hash; // String(40)
    bool forced;
    std::optional<std::string> prompt; // prefixed optional Text Component

    ConfigurationAddResourcePack() : Packet(ID), ClientboundPacket(ID), uuid(), forced(false), prompt(std::nullopt) {}
    ConfigurationAddResourcePack(const UUID uuid, std::string url, std::string hash, const bool forced, std::optional<std::string> prompt = std::nullopt)
        : Packet(ID), ClientboundPacket(ID), uuid(uuid), url(std::move(url)), hash(std::move(hash)), forced(forced), prompt(std::move(prompt)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationAddResourcePack)
};

class ConfigurationStoreCookie final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0A;
    Identifier key;
    std::vector<uint8_t> value; // prefixed ByteArray(5120)

    ConfigurationStoreCookie() : Packet(ID), ClientboundPacket(ID), key({"",""}), value() {}
    ConfigurationStoreCookie(Identifier  key, std::vector<uint8_t>&& value) : Packet(ID), ClientboundPacket(ID), key(std::move(key)), value(std::move(value)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationStoreCookie)
};

class ConfigurationTransfer final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0B;
    std::string host; // String(32767)
    int port; // VarInt

    ConfigurationTransfer() : Packet(ID), ClientboundPacket(ID), port(0) {}
    ConfigurationTransfer(std::string host, const int port) : Packet(ID), ClientboundPacket(ID), host(std::move(host)), port(port) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationTransfer)
};

class FeatureFlags final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0C;
    std::vector<Identifier> features; // prefixed array

    FeatureFlags() : Packet(ID), ClientboundPacket(ID) {}
    explicit FeatureFlags(std::vector<Identifier>& features) : Packet(ID), ClientboundPacket(ID), features(std::move(features)) {}
    CLIENTBOUND_PACKET_FOOTER(FeatureFlags)
};

class ConfigurationUpdateTags final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0D;
    std::vector<RegistryTagData> tags; // prefixed array

    ConfigurationUpdateTags() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationUpdateTags(std::vector<RegistryTagData>& tags) : Packet(ID), ClientboundPacket(ID), tags(std::move(tags)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationUpdateTags)
};

class ClientboundKnownPacks final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0E;
    std::vector<ResourcePackHeader> knownPackets; // prefixed array

    ClientboundKnownPacks() : Packet(ID), ClientboundPacket(ID) {}
    explicit ClientboundKnownPacks(std::vector<ResourcePackHeader>& knownPackets) : Packet(ID), ClientboundPacket(ID), knownPackets(std::move(knownPackets)) {}
    CLIENTBOUND_PACKET_FOOTER(ClientboundKnownPacks)
};

class ConfigurationCustomReportDetails final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0F;
    std::vector<ReportDetail> details; // prefixed array [{String(128), String(4096)}]

    ConfigurationCustomReportDetails() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationCustomReportDetails(std::vector<ReportDetail>& details) : Packet(ID), ClientboundPacket(ID), details(std::move(details)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationCustomReportDetails)
};

class ConfigurationServerLinks final : public ClientboundPacket {
public:
    constexpr static int ID = 0x10;
    std::vector<ServerLink> links; // prefixed array

    ConfigurationServerLinks() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationServerLinks(std::vector<ServerLink>& links) : Packet(ID), ClientboundPacket(ID), links(std::move(links)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationServerLinks)
};

// Play Packets
class LoginPlay final : public ClientboundPacket {
public:
    constexpr static int ID = 0x2B;
    int entityId; // int
    bool isHardcore;
    std::vector<Identifier> dimensions; // prefixed array
    int maxPlayers; // VarInt
    int viewDistance; // VarInt
    int simulationDistance; // VarInt
    bool reducedDebugInfo;
    bool enableRespawnScreen;
    bool doLimitedCrafting;
    int dimensionType; // VarInt
    Identifier dimensionName;
    long hashedSeed;
    uint8_t gamemode;
    int8_t previousGamemode;
    bool debug;
    bool flat;
    bool hasDeathLocation;
    std::optional<Identifier> deathDimension; // optional identifier
    std::optional<math::Position> deathPosition; // optional position
    int portalCooldown; // VarInt
    int seaLevel; // VarInt
    bool                          enforcesSecureChat;

    LoginPlay(const int entity_id, const bool is_hardcore, const std::vector<Identifier> dimensions, const int max_players, const int view_distance, const int simulation_distance, const bool reduced_debug_info,
              bool const enable_respawn_screen, bool const do_limited_crafting, const int dimension_type, const Identifier dimension_name, const long hashed_seed, const uint8_t gamemode, const int8_t previous_gamemode,
              const bool debug, const bool flat, const bool has_death_location, const std::optional<Identifier> death_dimension, const std::optional<math::Position> death_position, const int portal_cooldown,
              const int sea_level, const bool enforces_secure_chat)
        : Packet(ID), ClientboundPacket(ID), entityId(entity_id), isHardcore(is_hardcore), dimensions(dimensions), maxPlayers(max_players), viewDistance(view_distance),
          simulationDistance(simulation_distance), reducedDebugInfo(reduced_debug_info), enableRespawnScreen(enable_respawn_screen), doLimitedCrafting(do_limited_crafting),
          dimensionType(dimension_type), dimensionName(dimension_name), hashedSeed(hashed_seed), gamemode(gamemode), previousGamemode(previous_gamemode), debug(debug), flat(flat),
          hasDeathLocation(has_death_location), deathDimension(death_dimension), deathPosition(death_position), portalCooldown(portal_cooldown), seaLevel(sea_level),
          enforcesSecureChat(enforces_secure_chat) {}
    CLIENTBOUND_PACKET_FOOTER(LoginPlay)
};

class HandshakePacketHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit HandshakePacketHandler(NetworkConnection* connection) : connection(connection) {}
    bool handle(ClientHandshake& packet) override;
    bool handle(LegacyServerListPing& packet) override;
protected:
    NetworkConnection* connection;
};

class StatusPacketHandler final : public PacketHandler {
  public:
    using PacketHandler::handle;
    explicit StatusPacketHandler(NetworkConnection* connection) : connection(connection) {}
    bool handle(StatusRequest& packet) override;
    bool handle(PingRequest& packet) override;

  protected:
    NetworkConnection* connection;
};

class LoginPacketHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit LoginPacketHandler(NetworkConnection* connection) : connection(connection) {}
    bool handle(LoginStart& packet) override;
    bool handle(EncryptionResponse& packet) override;
    bool handle(LoginPluginResponse& packet) override;
    bool handle(LoginAcknowledge& packet) override;
    bool handle(LoginCookieResponse& packet) override;
protected:
    NetworkConnection* connection;
};

class ConfigurationPacketHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit ConfigurationPacketHandler(NetworkSession* session) : session(session) {}
    bool handle(ConfigurationClientInformation& packet) override;
    bool handle(ConfigurationCookieResponse& packet) override;
    bool handle(ConfigurationServerPluginMessage& packet) override;
    bool handle(AcknowledgeFinishConfiguration& packet) override;
    bool handle(ConfigurationServerboundKeepAlive& packet) override;
    bool handle(ConfigurationPong& packet) override;
    bool handle(ConfigurationResourcePackResponse& packet) override;
    bool handle(ServerboundKnownPacks& packet) override;
protected:
    NetworkSession* session;
};

class PlayPacketHandler final : public PacketHandler {
public:
    explicit PlayPacketHandler(NetworkSession* session) : PacketHandler(), session(session) {}
private:
    NetworkSession* session;
};

} // namespace stratos

#endif //PACKETCODEC_H
