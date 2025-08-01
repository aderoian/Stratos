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

#ifndef PACKETCONFIGURATION_H
#define PACKETCONFIGURATION_H
#include "network/protocol/Packet.h"
#include "utils/Types.h"
#include "utils/UUID.h"

namespace stratos::network {

class ConfigurationClientInformation final : public ServerboundPacket {//<ConfigurationClientInformation> {
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

    ConfigurationClientInformation() : ServerboundPacket(ID), viewDistance(0), chatMode(), chatColors(false), skinParts(0), mainHand(), enableTextFiltering(false),
          allowServerListing(false), particleStatus() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationClientInformation)
};

class ConfigurationCookieResponse final : public ServerboundPacket {//<ConfigurationCookieResponse> {
public:
    constexpr static int ID = 0x01;
    utils::Identifier key;
    std::optional<std::vector<uint8_t>> value; // prefixed optional prefixed ByteArray(5120)

    ConfigurationCookieResponse() : ServerboundPacket(ID), key({"",""}), value() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationCookieResponse)
};

class ConfigurationServerPluginMessage final : public ServerboundPacket {//<ConfigurationServerPluginMessage> {
public:
    constexpr static int ID = 0x02;
    utils::Identifier channel;
    std::vector<uint8_t> data; // prefixed ByteArray(32767)

    ConfigurationServerPluginMessage() : ServerboundPacket(ID), channel({"",""}), data() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationServerPluginMessage)
};

class AcknowledgeFinishConfiguration final : public ServerboundPacket {//<AcknowledgeFinishConfiguration> {
public:
    constexpr static int ID = 0x03;

    AcknowledgeFinishConfiguration() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(AcknowledgeFinishConfiguration)
};

class ConfigurationServerboundKeepAlive final : public ServerboundPacket {//<ConfigurationServerboundKeepAlive> {
public:
    constexpr static int ID = 0x04;
    int64_t id;

    ConfigurationServerboundKeepAlive() : ServerboundPacket(ID), id(0) {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationServerboundKeepAlive)
};

class ConfigurationPong final : public ServerboundPacket {//<ConfigurationPong> {
public:
    constexpr static int ID = 0x05;
    int id;

    ConfigurationPong() : ServerboundPacket(ID), id(0) {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationPong)
};

class ConfigurationResourcePackResponse final : public ServerboundPacket {//<ConfigurationResourcePackResponse> {
public:
    constexpr static int ID = 0x06;
    UUID uuid;
    ResourcePackResult result; // VarInt Enum

    ConfigurationResourcePackResponse() : ServerboundPacket(ID), uuid(), result() {}
    SERVERBOUND_PACKET_FOOTER(ConfigurationResourcePackResponse)
};

class ServerboundKnownPacks final : public ServerboundPacket {//<ServerboundKnownPacks> {
public:
    constexpr static int ID = 0x07;
    std::vector<ResourcePackHeader> knownPacks; // prefixed array;

    ServerboundKnownPacks() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(ServerboundKnownPacks)
};

class ConfigurationCookieRequest final : public ClientboundPacket {//<ConfigurationCookieRequest> {
public:
    constexpr static int ID = 0x00;
    utils::Identifier key;

    ConfigurationCookieRequest() : ClientboundPacket(ID), key({"",""}) {}
    explicit ConfigurationCookieRequest(utils::Identifier  key) : ClientboundPacket(ID), key(std::move(key)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationCookieRequest)
};

class ConfigurationClientboundPluginMessage final : public ClientboundPacket {//<ConfigurationClientboundPluginMessage> {
public:
    constexpr static int ID = 0x01;
    utils::Identifier channel;
    std::vector<uint8_t> data; // ByteArray

    ConfigurationClientboundPluginMessage() : ClientboundPacket(ID), channel({"",""}) {}
    ConfigurationClientboundPluginMessage(utils::Identifier channel, std::vector<uint8_t> data)
        : ClientboundPacket(ID), channel(std::move(channel)), data(std::move(data)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationClientboundPluginMessage)
};

class ConfigurationDisconnect final : public ClientboundPacket {//<ConfigurationDisconnect> {
public:
    constexpr static int ID = 0x02;
    std::string reason; // Text Component

    ConfigurationDisconnect() : ClientboundPacket(ID) {}
    explicit ConfigurationDisconnect(std::string&& reason) : ClientboundPacket(ID), reason(std::move(reason)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationDisconnect)
};

class FinishConfiguration final : public ClientboundPacket {//<FinishConfiguration> {
public:
    constexpr static int ID = 0x03;

    FinishConfiguration() : ClientboundPacket(ID) {}
    CLIENTBOUND_PACKET_FOOTER(FinishConfiguration)
};

class ConfigurationClientboundKeepAlive final : public ClientboundPacket {//<ConfigurationClientboundKeepAlive> {
public:
    constexpr static int ID = 0x04;
    int64_t id;

    ConfigurationClientboundKeepAlive() : ClientboundPacket(ID), id(0) {}
    explicit ConfigurationClientboundKeepAlive(const int64_t id) : ClientboundPacket(ID), id(id) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationClientboundKeepAlive)
};

class ConfigurationPing final : public ClientboundPacket {//<ConfigurationPing> {
public:
    constexpr static int ID = 0x05;
    int id;

    ConfigurationPing() : ClientboundPacket(ID), id(0) {}
    explicit ConfigurationPing(const int id) : ClientboundPacket(ID), id(id) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationPing)
};

class ResetChat final : public ClientboundPacket {//<ResetChat> {
public:
    constexpr static int ID = 0x06;

    ResetChat() : ClientboundPacket(ID) {}
    CLIENTBOUND_PACKET_FOOTER(ResetChat)
};

class RegistryDataPacket final : public ClientboundPacket {//<RegistryDataPacket> {
public:
    constexpr static int ID = 0x07;
    utils::Identifier registryKey;
    std::vector<RegistryEntry> entries;

    RegistryDataPacket() : ClientboundPacket(ID), registryKey({"",""}) {}
    RegistryDataPacket(utils::Identifier registryKey, std::vector<RegistryEntry>&& entries)
        : ClientboundPacket(ID), registryKey(std::move(registryKey)), entries(std::move(entries)) {}
    CLIENTBOUND_PACKET_FOOTER(RegistryDataPacket)
};

class ConfigurationRemoveRemoveResourcePack final : public ClientboundPacket {//<ConfigurationRemoveRemoveResourcePack> {
public:
    constexpr static int ID = 0x08;
    std::optional<UUID> uuid; // prefixed optional UUID

    ConfigurationRemoveRemoveResourcePack() : ClientboundPacket(ID), uuid(std::nullopt) {}
    explicit ConfigurationRemoveRemoveResourcePack(const UUID& uuid) : ClientboundPacket(ID), uuid(uuid) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationRemoveRemoveResourcePack)
};

class ConfigurationAddResourcePack final : public ClientboundPacket {//<ConfigurationAddResourcePack> {
public:
    constexpr static int ID = 0x09;
    UUID uuid;
    std::string url; // String(32767)
    std::string hash; // String(40)
    bool forced;
    std::optional<std::string> prompt; // prefixed optional Text Component

    ConfigurationAddResourcePack() : ClientboundPacket(ID), uuid(), forced(false), prompt(std::nullopt) {}
    ConfigurationAddResourcePack(const UUID uuid, std::string url, std::string hash, const bool forced, std::optional<std::string> prompt = std::nullopt)
        : ClientboundPacket(ID), uuid(uuid), url(std::move(url)), hash(std::move(hash)), forced(forced), prompt(std::move(prompt)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationAddResourcePack)
};

class ConfigurationStoreCookie final : public ClientboundPacket {//<ConfigurationStoreCookie> {
public:
    constexpr static int ID = 0x0A;
    utils::Identifier key;
    std::vector<uint8_t> value; // prefixed ByteArray(5120)

    ConfigurationStoreCookie() : ClientboundPacket(ID), key({"",""}), value() {}
    ConfigurationStoreCookie(utils::Identifier  key, std::vector<uint8_t>&& value) : ClientboundPacket(ID), key(std::move(key)), value(std::move(value)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationStoreCookie)
};

class ConfigurationTransfer final : public ClientboundPacket {//<ConfigurationTransfer> {
public:
    constexpr static int ID = 0x0B;
    std::string host; // String(32767)
    int port; // VarInt

    ConfigurationTransfer() : ClientboundPacket(ID), port(0) {}
    ConfigurationTransfer(std::string host, const int port) : ClientboundPacket(ID), host(std::move(host)), port(port) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationTransfer)
};

class FeatureFlags final : public ClientboundPacket {//<FeatureFlags> {
public:
    constexpr static int ID = 0x0C;
    std::vector<utils::Identifier> features; // prefixed array

    FeatureFlags() : ClientboundPacket(ID) {}
    explicit FeatureFlags(std::vector<utils::Identifier>& features) : ClientboundPacket(ID), features(std::move(features)) {}
    CLIENTBOUND_PACKET_FOOTER(FeatureFlags)
};

class ConfigurationUpdateTags final : public ClientboundPacket {//<ConfigurationUpdateTags> {
public:
    constexpr static int ID = 0x0D;
    std::vector<RegistryTagData> tags; // prefixed array

    ConfigurationUpdateTags() : ClientboundPacket(ID) {}
    explicit ConfigurationUpdateTags(std::vector<RegistryTagData>& tags) : ClientboundPacket(ID), tags(std::move(tags)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationUpdateTags)
};

class ClientboundKnownPacks final : public ClientboundPacket {//<ClientboundKnownPacks> {
public:
    constexpr static int ID = 0x0E;
    std::vector<ResourcePackHeader> knownPackets; // prefixed array

    ClientboundKnownPacks() : ClientboundPacket(ID) {}
    explicit ClientboundKnownPacks(std::vector<ResourcePackHeader>& knownPackets) : ClientboundPacket(ID), knownPackets(std::move(knownPackets)) {}
    CLIENTBOUND_PACKET_FOOTER(ClientboundKnownPacks)
};

class ConfigurationCustomReportDetails final : public ClientboundPacket {//<ConfigurationCustomReportDetails> {
public:
    constexpr static int ID = 0x0F;
    std::vector<ReportDetail> details; // prefixed array [{String(128), String(4096)}]

    ConfigurationCustomReportDetails() : ClientboundPacket(ID) {}
    explicit ConfigurationCustomReportDetails(std::vector<ReportDetail>& details) : ClientboundPacket(ID), details(std::move(details)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationCustomReportDetails)
};

class ConfigurationServerLinks final : public ClientboundPacket {//<ConfigurationServerLinks> {
public:
    constexpr static int ID = 0x10;
    std::vector<ServerLink> links; // prefixed array

    ConfigurationServerLinks() : ClientboundPacket(ID) {}
    explicit ConfigurationServerLinks(std::vector<ServerLink>& links) : ClientboundPacket(ID), links(std::move(links)) {}
    CLIENTBOUND_PACKET_FOOTER(ConfigurationServerLinks)
};

} // namespace stratos::network

#endif //PACKETCONFIGURATION_H
