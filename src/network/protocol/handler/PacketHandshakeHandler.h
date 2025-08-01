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

#ifndef PACKETHANDSHAKEHANDLER_H
#define PACKETHANDSHAKEHANDLER_H
#include "network/protocol/Packet.h"

namespace stratos::network {
class NetworkConnection;
class ClientHandshake;
class LegacyServerListPing;

class PacketHandshakeHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit PacketHandshakeHandler(NetworkConnection* connection) : connection(connection) {}
    bool handle(const ClientHandshake* packet) override;
    bool handle(const LegacyServerListPing* packet) override;
protected:
    NetworkConnection* connection;
};

} // namespace stratos::network

#endif //PACKETHANDSHAKEHANDLER_H
