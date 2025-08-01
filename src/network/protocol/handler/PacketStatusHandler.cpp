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

#include "PacketStatusHandler.h"

#include "network/protocol/definition/PacketStatus.h"
#include "network/session/NetworkClient.h"
#include "Server.h"

#define PROTOCOL_VERSION 770
#define PROTOCOL_VERSION_STRING "1.21.5"

namespace stratos::network {
bool PacketStatusHandler::handle(const StatusRequest* packet) {
    if (connection->getState() == Status) {
        constexpr auto STATUS_RESPONSE_FORMAT = R"({{"version":{{"name":"{}","protocol":{}}},"players":{{"max":{},"online":{},"sample":[]}},"description":{{"text":"{}"}}}})";
        connection->sendPacket(new StatusResponse(
            std::format(STATUS_RESPONSE_FORMAT, std::string(PROTOCOL_VERSION_STRING), PROTOCOL_VERSION, server->getMaxPlayers(), server->getOnlinePlayers(), server->getMotd())));
    }
    return true;
}
bool PacketStatusHandler::handle(const PingRequest* packet) {
    if (connection->getState() == Status)
        connection->sendPacket(new PongResponse(packet->timestamp));
    return true;
}
} // namespace stratos::network