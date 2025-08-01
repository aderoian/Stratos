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

#include "PacketHandshakeHandler.h"

#include "network/protocol/definition/PacketHandshake.h"
#include "network/session/NetworkClient.h"
#include "Server.h"
#include "utils/config/Config.h"
#include "utils/Types.h"

#define PROTOCOL_VERSION_STRING "1.21.5"

namespace stratos::network {
bool PacketHandshakeHandler::handle(const ClientHandshake* packet) {
    switch (packet->intent) {
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
bool PacketHandshakeHandler::handle(const LegacyServerListPing* packet) {
    connection->sendPacket(new LegacyServerListPong(47, PROTOCOL_VERSION_STRING, server->getMotd(), server->getOnlinePlayers(), server->getServerProperties()->getProperty("max-players").value().get().asInt()));
    connection->disconnect();
    return true;
}
} // namespace stratos::network