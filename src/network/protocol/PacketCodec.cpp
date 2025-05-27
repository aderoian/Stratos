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

#include "PacketCodec.h"
#include "PacketSerialization.h"

void stratos::ClientHandshake::decrypt(PacketBuffer& buffer) {
    protocolVersion = buffer.readInt();
    serverAddress   = buffer.readString(255);
    serverPort      = buffer.readUnsignedShort();

    // Read the intent
    intent = buffer.readXEnum<int, Intent>(readVarInt, [](const int& value) -> Intent {
                                  switch (value) {
                                  case 0x01:
                                      return Intent::Status;
                                  case 0x02:
                                      return Intent::Login;
                                  case 0x03:
                                      return Intent::Transfer;
                                  default:
                                      throw PacketSerializationException("Unknown intent value: " + std::to_string(value));
                                  }
                              });
}
void stratos::ClientHandshake::handle(NetworkSession& session) {}
void stratos::LegacyServerListPing::decrypt(PacketBuffer& buffer) {}
void stratos::LegacyServerListPing::handle(NetworkSession& session) {}
void stratos::LegacyServerListPong::encrypt(PacketBuffer& buffer) {
    const std::string payload =
        "§1\0" + std::to_string(protocolVersion) + "\0" + version + "\0" + motd + "\0" + "\0" + std::to_string(onlinePlayers) + "\0" + std::to_string(maxPlayers);
    buffer.writeStringUTF16BE(payload);
}
void stratos::StatusResponse::encrypt(PacketBuffer& buffer) {
    buffer.writeString(jsonResponse, 32767);
}
void stratos::PongResponse::encrypt(PacketBuffer& buffer) {
    buffer.writeLong(timestamp);
}
void stratos::StatusRequest::decrypt(PacketBuffer& buffer) {}
void stratos::StatusRequest::handle(NetworkSession& session) {}
void stratos::PingRequest::decrypt(PacketBuffer& buffer) {}
void stratos::PingRequest::handle(NetworkSession& session) {}
