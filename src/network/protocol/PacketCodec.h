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
    void handle(NetworkSession& session) override;
};

class LegacyServerListPing final : public ServerboundPacket {
public:
    constexpr static int ID = 0xFE;
    uint8_t payload = 0x01; // Legacy server list ping payload

    explicit LegacyServerListPing() : Packet(ID), ServerboundPacket(ID) {}
    ~LegacyServerListPing() override = default;
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
    constexpr static int ID = 0x00;

    explicit StatusRequest() : Packet(ID), ServerboundPacket(ID) {}
    ~StatusRequest() override = default;
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};

class PingRequest final : public ServerboundPacket {
  public:
    constexpr static int ID = 0x01;

    explicit PingRequest() : Packet(ID), ServerboundPacket(ID) {}
    ~PingRequest() override = default;
    void decrypt(PacketBuffer& buffer) override;
    void handle(NetworkSession& session) override;
};


} // namespace stratos

#endif //PACKETCODEC_H
