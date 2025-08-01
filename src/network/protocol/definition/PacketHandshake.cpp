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

#include "PacketHandshake.h"

#include "network/protocol/serialization/PacketBuffer.h"
#include "network/protocol/serialization/PacketSerialization.h"

namespace stratos::network {
void ClientHandshake::decrypt(const PacketBuffer& buffer) {
    protocolVersion = buffer.readVarInt();
    serverAddress   = buffer.readString(255);
    serverPort      = buffer.readUnsignedShort();

    // Read the intent
    intent = buffer.readVarIntEnum<HandshakeIntent>([](const int& value) -> HandshakeIntent {
        switch (value) {
        case 0x01:
            return HandshakeIntent::Status;
        case 0x02:
            return HandshakeIntent::Login;
        case 0x03:
            return HandshakeIntent::Transfer;
        default:
            throw PacketSerializationException("Unknown intent value: " + std::to_string(value));
        }
    });
}
void LegacyServerListPing::decrypt(const PacketBuffer& buffer) {
    payload = buffer.readByte();

    // None of this matters, but we need to read the payload to avoid deserialization errors
    buffer.readByte();          // Packet identifier
    buffer.readStringUTF16BE(); // MC|Pinghost
    buffer.readShort();         // Remaining length
    buffer.readByte();          // Protocol version
    buffer.readStringUTF16BE(); // Server address
    buffer.readInt();           // Server port
}
void LegacyServerListPong::encrypt(PacketBuffer& buffer) const {
    buffer.writeByte(0xFF); // Kick packet identifier
    const std::string payload =
        "§1\0" + std::to_string(protocolVersion) + "\0" + version + "\0" + motd + "\0" + "\0" + std::to_string(onlinePlayers) + "\0" + std::to_string(maxPlayers);
    buffer.writeStringUTF16BE(payload);
}

}