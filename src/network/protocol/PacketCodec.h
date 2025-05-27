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
#include "PacketSerialization.h"

#include <cstdint>
#include <string>

namespace stratos {

// Handshake Packets

class ClientHandshake final : public ServerboundPacket {
  public:
    enum class Intent {
        Status = 0x01,
        Login = 0x02,
        Transfer = 0x03
    };

    constexpr static int ID = 0x00;
    int protocolVersion = 0;
    std::string serverAddress = "";
    uint16_t serverPort = 0;
    Intent intent = Intent::Status;

    explicit ClientHandshake() : ServerboundPacket(ID) {}
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};

class LegacyServerListPing final : public ServerboundPacket {
public:
    constexpr static int ID = 0xFE;
    uint8_t payload = 0x01; // Legacy server list ping payload

    explicit LegacyServerListPing() : ServerboundPacket(ID) {}
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};

class LegacyServerListPong final : public ClientboundPacket {
public:
    constexpr static int ID = 0xFF;
    int protocolVersion;
    std::string version;
    std::string motd;
    int onlinePlayers;
    int         maxPlayers;

    LegacyServerListPong(const int protocol_version, const std::string& version, const std::string& motd, const int online_players, const int max_players)
        : ClientboundPacket(ID), protocolVersion(protocol_version), version(version), motd(motd), onlinePlayers(online_players), maxPlayers(max_players) {}
    void encrypt(PacketBuffer& buffer) override;
};

// Status Packets

class StatusResponse final : public ClientboundPacket {
public:
    constexpr static int ID = 0x00;
    std::string          jsonResponse;

    explicit StatusResponse(std::string&& jsonResponse) : ClientboundPacket(ID), jsonResponse(std::move(jsonResponse)) {}
    void encrypt(PacketBuffer& buffer) override { buffer.writeString(jsonResponse, 32767); }
};

class PongResponse final : public ClientboundPacket {
    constexpr static int ID = 0x01;
    int64_t timestamp;

    explicit PongResponse(const int64_t timestamp) : ClientboundPacket(ID), timestamp(timestamp) {}
    void encrypt(PacketBuffer& buffer) override { buffer.writeLong(timestamp); }
};

class StatusRequest final : public ServerboundPacket {
public:
    constexpr static int ID = 0x00;
    explicit StatusRequest() : ServerboundPacket(ID) {}
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};

class PingRequest final : public ServerboundPacket {
  public:
    constexpr static int ID = 0x01;

    explicit PingRequest() : ServerboundPacket(ID) {}
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};


} // namespace stratos

#endif //PACKETCODEC_H
