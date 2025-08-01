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

#include "PacketStatus.h"

#include "network/protocol/serialization/PacketBuffer.h"

namespace stratos::network {
void StatusResponse::encrypt(PacketBuffer& buffer) const {
    buffer.writeString(jsonResponse, 32767);
}
void PongResponse::encrypt(PacketBuffer& buffer) const {
    buffer.writeLong(timestamp);
}
void StatusRequest::decrypt(const PacketBuffer& buffer) {}
void PingRequest::decrypt(const PacketBuffer& buffer) {
    timestamp = buffer.readLong();
}
} // namespace stratos::network