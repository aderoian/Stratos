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

#include "PacketSerialization.h"

#include "utils/io/ByteBuffer.h"

namespace stratos::network {
int8_t  readByte(const ByteVec& buffer, size_t& offset) {
    if (offset + sizeof(int8_t) > buffer.size()) throw PacketSerializationException("Buffer overflow: Not enough bytes to read byte.");
    return static_cast<int8_t>(buffer[offset++]);
}
uint8_t readUnsignedByte(const ByteVec& buffer, size_t& offset) {
    if (offset + sizeof(uint8_t) > buffer.size()) throw PacketSerializationException("Buffer overflow: Not enough bytes to read unsigned byte.");
    return buffer[offset++];
}
int readVarInt(const ByteVec& buffer, size_t& offset) {
    int value    = 0;
    int position = 0;
    while (true) {
        const uint8_t currentByte = readByte(buffer, offset);
        value |= (currentByte & 0x7F) << position;
        if ((currentByte & 0x80) == 0) break;
        position += 7;
        if (position >= 32) {
            throw BufferOverflowException("VarInt is too big to fit in an int.");
        }
    }
    return value;
}
} // namespace stratos::network
