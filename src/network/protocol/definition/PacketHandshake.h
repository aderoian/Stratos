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

#ifndef PACKETHANDSHAKE_H
#define PACKETHANDSHAKE_H

#include "network/protocol/Packet.h"
#include "utils/Types.h"

namespace stratos::network {

class ClientHandshake final : public ServerboundPacket {//<ClientHandshake> {
public:
    constexpr static int ID = 0x00;

    int protocolVersion;
    std::string serverAddress;
    uint16_t serverPort;
    HandshakeIntent intent;
    explicit ClientHandshake() : ServerboundPacket(ID), protocolVersion(0), serverPort(0), intent() {}
    //SERVERBOUND_PACKET_FOOTER(ClientHandshake)
    bool accept(PacketHandler& handler) const override { return handler.handle(this); }

    ~ClientHandshake() override = default;

    void decrypt(const PacketBuffer& buffer) override;
};

class LegacyServerListPing final : public ServerboundPacket {//<LegacyServerListPing> {
public:
    constexpr static int ID = 0xFE;
    uint8_t payload = 0x01; // Legacy server list ping payload

    explicit LegacyServerListPing() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(LegacyServerListPing)
};

class LegacyServerListPong final : public ClientboundPacket {//LegacyServerListPong> {
public:
    constexpr static int ID = 0xFF;
    int protocolVersion;
    std::string version;
    std::string motd;
    int onlinePlayers;
    int  maxPlayers;

    LegacyServerListPong() : ClientboundPacket(ID), protocolVersion(0), onlinePlayers(0), maxPlayers(0) {}
    LegacyServerListPong(const int protocol_version, std::string  version, std::string  motd, const int online_players, const int max_players)
         : ClientboundPacket(ID), protocolVersion(protocol_version), version(std::move(version)), motd(std::move(motd)), onlinePlayers(online_players), maxPlayers(max_players) {}
    CLIENTBOUND_PACKET_FOOTER(LegacyServerListPong)
};

} // namespace stratos::network

#endif //PACKETHANDSHAKE_H
