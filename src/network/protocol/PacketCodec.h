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
#include "Packet.h"
#include "utils/Types.h"

#include <cstdint>
#include <optional>
#include <string>

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

#define PACKET_ACCEPT \
bool accept(PacketHandler& handler) override { return handler.handle(*this); }

// Handshake Packets

class ClientHandshake final : public ServerboundPacket {
  public:
    PACKET_ACCEPT
    enum class Intent {
        None = 0,
        Status = 0x01,
        Login = 0x02,
        Transfer = 0x03
    };

    constexpr static int ID = 0x00;
    int protocolVersion = 0;
    std::string serverAddress = "";
    uint16_t serverPort = 0;
    Intent intent = Intent::Status;

    explicit ClientHandshake() : Packet(ID), ServerboundPacket(ID) {}
    ~ClientHandshake() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class LegacyServerListPing final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0xFE;
    uint8_t payload = 0x01; // Legacy server list ping payload

    explicit LegacyServerListPing() : Packet(ID), ServerboundPacket(ID) {}
    ~LegacyServerListPing() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class LegacyServerListPong final : public ClientboundPacket {
public:
    constexpr static int ID = 0xFF;
    int protocolVersion;
    std::string version;
    std::string motd;
    int onlinePlayers;
    int         maxPlayers;

    LegacyServerListPong() : Packet(ID), ClientboundPacket(ID), protocolVersion(0), version(""), motd(""), onlinePlayers(0), maxPlayers(0) {}
    LegacyServerListPong(const int protocol_version, const std::string& version, const std::string& motd, const int online_players, const int max_players)
        : Packet(ID), ClientboundPacket(ID), protocolVersion(protocol_version), version(version), motd(motd), onlinePlayers(online_players), maxPlayers(max_players) {}
    ~LegacyServerListPong() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

// Status Packets

class StatusResponse final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string          jsonResponse;

    StatusResponse() : Packet(ID), ClientboundPacket(ID), jsonResponse("") {}
    explicit StatusResponse(std::string&& jsonResponse) : Packet(ID), ClientboundPacket(ID), jsonResponse(std::move(jsonResponse)) {}
    ~StatusResponse() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class PongResponse final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;
    int64_t timestamp;

    PongResponse() : Packet(ID), ClientboundPacket(ID), timestamp(0) {}
    explicit PongResponse(const int64_t timestamp) : Packet(ID), ClientboundPacket(ID), timestamp(timestamp) {}
    ~PongResponse() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class StatusRequest final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x00;

    explicit StatusRequest() : Packet(ID), ServerboundPacket(ID) {}
    ~StatusRequest() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class PingRequest final : public ServerboundPacket {
  public:
    PACKET_ACCEPT
    constexpr static int ID = 0x01;

    int64_t timestamp = 0;
    explicit PingRequest() : Packet(ID), ServerboundPacket(ID) {}
    ~PingRequest() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

// Login Packets

class LoginStart final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x00;

    std::string name; // String(16)
    UUID uuid;
    LoginStart() : Packet(ID), ServerboundPacket(ID), name(""), uuid() {}
    ~LoginStart() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class EncryptionResponse final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x01;

    std::vector<uint8_t> sharedSecret; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray
    EncryptionResponse() : Packet(ID), ServerboundPacket(ID), sharedSecret(), verifyToken() {}
    ~EncryptionResponse() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class LoginPluginResponse final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x02;

    int messageId; // VarInt
    std::optional<std::vector<uint8_t>> data; // prefixed optional ByteArray
    LoginPluginResponse() : Packet(ID), ServerboundPacket(ID), messageId(0), data() {}
    ~LoginPluginResponse() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class LoginAcknowledge final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x03;

    LoginAcknowledge() : Packet(ID), ServerboundPacket(ID) {}
    ~LoginAcknowledge() override = default;
    void decrypt(PacketBuffer& buffer) override {};
};

class LoginCookieResponse final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x04;

    Identifier cookie;
    std::optional<std::vector<uint8_t>> payload; // prefixed optional ByteArray
    LoginCookieResponse() : Packet(ID), ServerboundPacket(ID), cookie({"",""}), payload() {}
    ~LoginCookieResponse() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class LoginDisconnect final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;

    std::string reason; // JSON Text Component
    LoginDisconnect() : Packet(ID), ClientboundPacket(ID), reason("") {}
    explicit LoginDisconnect(std::string&& reason) : Packet(ID), ClientboundPacket(ID), reason(std::move(reason)) {}
    ~LoginDisconnect() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class EncryptionRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;

    std::string serverId; // String(20)
    std::vector<uint8_t> publicKey; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray
    bool shouldAuthenticate;
    EncryptionRequest() : Packet(ID), ClientboundPacket(ID), serverId(""), publicKey(), verifyToken(), shouldAuthenticate(false) {}
    EncryptionRequest(std::string&& serverId, std::vector<uint8_t>&& publicKey, std::vector<uint8_t>&& verifyToken, bool shouldAuthenticate)
        : Packet(ID), ClientboundPacket(ID), serverId(std::move(serverId)), publicKey(std::move(publicKey)), verifyToken(std::move(verifyToken)), shouldAuthenticate(shouldAuthenticate) {}
    ~EncryptionRequest() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class LoginSuccess final : public ClientboundPacket {
public:

    constexpr static int ID = 0x02;

    UUID uuid;
    std::string username; // String(16)
    std::vector<LoginProperty> properties; // prefixed array(16)
    LoginSuccess() : Packet(ID), ClientboundPacket(ID), uuid(), username(""), properties() {}
    LoginSuccess(const UUID& uuid, std::string&& username, std::vector<LoginProperty>&& properties)
        : Packet(ID), ClientboundPacket(ID), uuid(uuid), username(std::move(username)), properties(std::move(properties)) {}
    ~LoginSuccess() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class SetCompression final : public ClientboundPacket {
public:
    constexpr static int ID = 0x03;

    int threshold; // VarInt
    SetCompression() : Packet(ID), ClientboundPacket(ID), threshold(0) {}
    explicit SetCompression(const int threshold) : Packet(ID), ClientboundPacket(ID), threshold(threshold) {}
    ~SetCompression() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class LoginPluginRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x04;

    int messageId; // VarInt
    Identifier channel;
    std::vector<uint8_t> data; // ByteArray
    LoginPluginRequest() : Packet(ID), ClientboundPacket(ID), messageId(0), channel({"",""}), data() {}
    LoginPluginRequest(const int messageId, const Identifier& channel, const std::vector<uint8_t>&& data)
        : Packet(ID), ClientboundPacket(ID), messageId(messageId), channel(std::move(channel)), data(std::move(data)) {}
    ~LoginPluginRequest() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class LoginCookieRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x05;

    Identifier cookie;
    LoginCookieRequest() : Packet(ID), ClientboundPacket(ID), cookie({"",""}) {}
    explicit LoginCookieRequest(const Identifier& cookie) : Packet(ID), ClientboundPacket(ID), cookie(cookie) {}
    ~LoginCookieRequest() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

// Configuration Packets

class ConfigurationClientInformation final : public ServerboundPacket {
public:
    PACKET_ACCEPT
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
    ~ConfigurationClientInformation() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ConfigurationCookieResponse final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x01;

    Identifier key;
    std::optional<std::vector<uint8_t>> value; // prefixed optional prefixed ByteArray(5120)
    ConfigurationCookieResponse() : Packet(ID), ServerboundPacket(ID), key({"",""}), value() {}
    ~ConfigurationCookieResponse() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ConfigurationServerPluginMessage final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x02;

    Identifier channel;
    std::vector<uint8_t> data; // prefixed ByteArray(32767)
    ConfigurationServerPluginMessage() : Packet(ID), ServerboundPacket(ID), channel({"",""}), data() {}
    ~ConfigurationServerPluginMessage() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class AcknowledgeFinishConfiguration final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x03;

    AcknowledgeFinishConfiguration() : Packet(ID), ServerboundPacket(ID) {}
    ~AcknowledgeFinishConfiguration() override = default;
    void decrypt(PacketBuffer& buffer) override {}
};

class ConfigurationServerboundKeepAlive final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x04;

    int64_t id;
    ConfigurationServerboundKeepAlive() : Packet(ID), ServerboundPacket(ID), id(0) {}
    ~ConfigurationServerboundKeepAlive() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ConfigurationPong final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x05;

    int id;
    ConfigurationPong() : Packet(ID), ServerboundPacket(ID), id(0) {}
    ~ConfigurationPong() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ConfigurationResourcePackResponse final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x06;

    UUID uuid;
    ResourcePackResult result; // VarInt Enum
    ConfigurationResourcePackResponse() : Packet(ID), ServerboundPacket(ID), uuid(), result() {}
    ~ConfigurationResourcePackResponse() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ServerboundKnownPacks final : public ServerboundPacket {
public:
    PACKET_ACCEPT
    constexpr static int ID = 0x07;

    std::vector<ResourcePackHeader> knownPacks; // prefixed array;
    ServerboundKnownPacks() : Packet(ID), ServerboundPacket(ID) {}
    ~ServerboundKnownPacks() override = default;
    void decrypt(PacketBuffer& buffer) override;
};

class ConfigurationCookieRequest final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;

    Identifier key;
    ConfigurationCookieRequest() : Packet(ID), ClientboundPacket(ID), key({"",""}) {}
    explicit ConfigurationCookieRequest(Identifier  key) : Packet(ID), ClientboundPacket(ID), key(std::move(key)) {}
    ~ConfigurationCookieRequest() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationClientboundPluginMessage final : public ClientboundPacket {
public:
    constexpr static int ID = 0x01;

    Identifier channel;
    std::vector<uint8_t> data; // ByteArray
    ConfigurationClientboundPluginMessage() : Packet(ID), ClientboundPacket(ID), channel({"",""}) {}
    ConfigurationClientboundPluginMessage(Identifier channel, std::vector<uint8_t> data)
        : Packet(ID), ClientboundPacket(ID), channel(std::move(channel)), data(std::move(data)) {}
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationDisconnect final : public ClientboundPacket {
public:
    constexpr static int ID = 0x02;

    std::string reason; // Text Component
    ConfigurationDisconnect() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationDisconnect(std::string&& reason) : Packet(ID), ClientboundPacket(ID), reason(std::move(reason)) {}
    ~ConfigurationDisconnect() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class FinishConfiguration final : public ClientboundPacket {
public:
    constexpr static int ID = 0x03;

    FinishConfiguration() : Packet(ID), ClientboundPacket(ID) {}
    ~FinishConfiguration() override = default;
    void encrypt(PacketBuffer& buffer) override {}
};

class ConfigurationClientboundKeepAlive final : public ClientboundPacket {
public:
    constexpr static int ID = 0x04;

    int64_t id;
    ConfigurationClientboundKeepAlive() : Packet(ID), ClientboundPacket(ID), id(0) {}
    explicit ConfigurationClientboundKeepAlive(const int64_t id) : Packet(ID), ClientboundPacket(ID), id(id) {}
    ~ConfigurationClientboundKeepAlive() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationPing final : public ClientboundPacket {
public:
    constexpr static int ID = 0x05;

    int id;
    ConfigurationPing() : Packet(ID), ClientboundPacket(ID), id(0) {}
    explicit ConfigurationPing(const int id) : Packet(ID), ClientboundPacket(ID), id(id) {}
    ~ConfigurationPing() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ResetChat final : public ClientboundPacket {
public:
    constexpr static int ID = 0x06;

    ResetChat() : Packet(ID), ClientboundPacket(ID) {}
    ~ResetChat() override = default;
    void encrypt(PacketBuffer& buffer) override {}
};

class RegistryDataPacket final : public ClientboundPacket {
public:
    constexpr static int ID = 0x07;

    Identifier registryKey;
    std::vector<RegistryEntry> entries;
    RegistryDataPacket() : Packet(ID), ClientboundPacket(ID), registryKey({"",""}) {}
    RegistryDataPacket(Identifier registryKey, std::vector<RegistryEntry>& entries)
        : Packet(ID), ClientboundPacket(ID), registryKey(std::move(registryKey)), entries(std::move(entries)) {}
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationRemoveRemoveResourcePack final : public ClientboundPacket {
public:
    constexpr static int ID = 0x08;

    std::optional<UUID> uuid; // prefixed optional UUID
    ConfigurationRemoveRemoveResourcePack() : Packet(ID), ClientboundPacket(ID), uuid(std::nullopt) {}
    explicit ConfigurationRemoveRemoveResourcePack(const UUID& uuid) : Packet(ID), ClientboundPacket(ID), uuid(uuid) {}
    ~ConfigurationRemoveRemoveResourcePack() override = default;
    void encrypt(PacketBuffer& buffer) override;
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
    ~ConfigurationAddResourcePack() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationStoreCookie final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0A;

    Identifier key;
    std::vector<uint8_t> value; // prefixed ByteArray(5120)
    ConfigurationStoreCookie() : Packet(ID), ClientboundPacket(ID), key({"",""}), value() {}
    ConfigurationStoreCookie(Identifier  key, std::vector<uint8_t>&& value) : Packet(ID), ClientboundPacket(ID), key(std::move(key)), value(std::move(value)) {}
    ~ConfigurationStoreCookie() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationTransfer final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0B;

    std::string host; // String(32767)
    int port; // VarInt
    ConfigurationTransfer() : Packet(ID), ClientboundPacket(ID), port(0) {}
    ConfigurationTransfer(std::string host, const int port) : Packet(ID), ClientboundPacket(ID), host(std::move(host)), port(port) {}
    ~ConfigurationTransfer() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class FeatureFlags final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0C;

    std::vector<Identifier> features; // prefixed array
    FeatureFlags() : Packet(ID), ClientboundPacket(ID) {}
    explicit FeatureFlags(std::vector<Identifier>& features) : Packet(ID), ClientboundPacket(ID), features(std::move(features)) {}
    ~FeatureFlags() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationUpdateTags final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0D;

    std::vector<RegistryTagData> tags; // prefixed array
    ConfigurationUpdateTags() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationUpdateTags(std::vector<RegistryTagData>& tags) : Packet(ID), ClientboundPacket(ID), tags(std::move(tags)) {}
    ~ConfigurationUpdateTags() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ClientboundKnownPacks final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0E;

    std::vector<ResourcePackHeader> knownPackets; // prefixed array
    ClientboundKnownPacks() : Packet(ID), ClientboundPacket(ID) {}
    explicit ClientboundKnownPacks(std::vector<ResourcePackHeader>& knownPackets) : Packet(ID), ClientboundPacket(ID), knownPackets(std::move(knownPackets)) {}
    ~ClientboundKnownPacks() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationCustomReportDetails final : public ClientboundPacket {
public:
    constexpr static int ID = 0x0F;

    std::vector<ReportDetail> details; // prefixed array [{String(128), String(4096)}]
    ConfigurationCustomReportDetails() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationCustomReportDetails(std::vector<ReportDetail>& details) : Packet(ID), ClientboundPacket(ID), details(std::move(details)) {}
    ~ConfigurationCustomReportDetails() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class ConfigurationServerLinks final : public ClientboundPacket {
public:
    constexpr static int ID = 0x10;

    std::vector<ServerLink> links; // prefixed array
    ConfigurationServerLinks() : Packet(ID), ClientboundPacket(ID) {}
    explicit ConfigurationServerLinks(std::vector<ServerLink>& links) : Packet(ID), ClientboundPacket(ID), links(std::move(links)) {}
    ~ConfigurationServerLinks() override = default;
    void encrypt(PacketBuffer& buffer) override;
};

class HandshakePacketHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit HandshakePacketHandler(NetworkConnection* connection) : connection(std::move(connection)) {}
    bool handle(ClientHandshake& packet) override;
    bool handle(LegacyServerListPing& packet) override;
protected:
    NetworkConnection* connection;
};

class StatusPacketHandler final : public PacketHandler {
  public:
    using PacketHandler::handle;
    explicit StatusPacketHandler(NetworkConnection* connection) : connection(std::move(connection)) {}
    bool handle(StatusRequest& packet) override;
    bool handle(PingRequest& packet) override;

  protected:
    NetworkConnection* connection;
};

class LoginPacketHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit LoginPacketHandler(NetworkConnection* connection) : connection(std::move(connection)) {}
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
    explicit ConfigurationPacketHandler(NetworkConnection* connection) : connection(std::move(connection)) {}
    bool handle(ConfigurationClientInformation& packet) override;
    bool handle(ConfigurationCookieResponse& packet) override;
    bool handle(ConfigurationServerPluginMessage& packet) override;
    bool handle(AcknowledgeFinishConfiguration& packet) override;
    bool handle(ConfigurationServerboundKeepAlive& packet) override;
    bool handle(ConfigurationPong& packet) override;
    bool handle(ConfigurationResourcePackResponse& packet) override;
    bool handle(ServerboundKnownPacks& packet) override;
protected:
    NetworkConnection* connection;
};

class PlayPacketHandler final : public PacketHandler {
public:
    explicit PlayPacketHandler(NetworkSession* session) : PacketHandler(), session(std::move(session)) {}
private:
    NetworkSession* session;
};

} // namespace stratos

#endif //PACKETCODEC_H
