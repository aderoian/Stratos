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

#ifndef PACKETSERIALIZATION_H
#define PACKETSERIALIZATION_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace stratos::network {
using ByteVec = std::vector<unsigned char>;
using UUID = std::array<uint8_t, 16>;

int8_t readByte(const ByteVec& buffer, size_t& offset);
uint8_t readUnsignedByte(const ByteVec& buffer, size_t& offset);
int readVarInt(const ByteVec& buffer, size_t& offset);

class PacketSerializationException final : public std::logic_error {
  public:
    explicit PacketSerializationException(const char* message) : logic_error(message) {};
    explicit PacketSerializationException(const std::string& message) : logic_error(message) {};
};
} // namespace stratos::network

#endif
