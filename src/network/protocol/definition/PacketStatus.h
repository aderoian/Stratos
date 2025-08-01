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

#ifndef PACKETSTATUS_H
#define PACKETSTATUS_H
#include "network/protocol/Packet.h"

namespace stratos::network {

class StatusResponse final : public ClientboundPacket {//StatusResponse> {
public:
    constexpr static int ID = 0x00;
    std::string          jsonResponse;

    StatusResponse() : ClientboundPacket(ID) {}
    explicit StatusResponse(std::string&& jsonResponse) : ClientboundPacket(ID), jsonResponse(std::move(jsonResponse)) {}
    CLIENTBOUND_PACKET_FOOTER(StatusResponse)
};

class PongResponse final : public ClientboundPacket {//PongResponse> {
public:
    constexpr static int ID = 0x01;
    int64_t timestamp;

    PongResponse() : ClientboundPacket(ID), timestamp(0) {}
    explicit PongResponse(const int64_t timestamp) : ClientboundPacket(ID), timestamp(timestamp) {}
    CLIENTBOUND_PACKET_FOOTER(PongResponse)
};

class StatusRequest final : public ServerboundPacket {//<StatusRequest> {
public:
    constexpr static int ID = 0x00;

    explicit StatusRequest() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(StatusRequest)
};

class PingRequest final : public ServerboundPacket {//<PingRequest> {
public:
    constexpr static int ID = 0x01;
    int64_t timestamp = 0;

    explicit PingRequest() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(PingRequest)
};

} // namespace stratos::network

#endif //PACKETSTATUS_H
