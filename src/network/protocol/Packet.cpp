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

#include "Packet.h"

#include "PacketCodec.h"

void stratos::PacketRegistry::setup() {
    // Handshaking Packets
    registerPacket({Handshaking, Serverbound, ClientHandshake::ID}, [] { return std::make_unique<ClientHandshake>(); });
    registerPacket({Handshaking, Serverbound, LegacyServerListPing::ID}, [] { return std::make_unique<LegacyServerListPing>(); });
    registerPacket({Handshaking, Clientbound, LegacyServerListPong::ID}, [] { return std::make_unique<LegacyServerListPong>(); });

    // Status Packets
    registerPacket({Status, Serverbound, StatusRequest::ID}, [] { return std::make_unique<StatusRequest>(); });
    registerPacket({Status, Serverbound, PingRequest::ID}, [] { return std::make_unique<PingRequest>(); });
    registerPacket({Status, Clientbound, StatusResponse::ID}, [] { return std::make_unique<StatusResponse>(); });
    registerPacket({Status, Clientbound, PongResponse::ID}, [] { return std::make_unique<PongResponse>(); });



}
