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
#include <string>
#include <vector>

namespace stratos {
using ByteVec = std::vector<unsigned char>;

class PacketSerializationException final : public std::logic_error {
public:
    explicit PacketSerializationException(const char* message) : logic_error(message) {};
    explicit PacketSerializationException(const std::string& message) : logic_error(message) {};
};

// Generic serialization functions
bool readBoolean(const ByteVec& buffer, size_t& offset);
int8_t readByte(const ByteVec& buffer, size_t& offset);
uint8_t readUnsignedByte(const ByteVec& buffer, size_t& offset);
short readShort(const ByteVec& buffer, size_t& offset);
uint16_t readUnsignedShort(const ByteVec& buffer, size_t& offset);
int readInt(const ByteVec& buffer, size_t& offset);
int64_t readLong(const ByteVec& buffer, size_t& offset);
float readFloat(const ByteVec& buffer, size_t& offset);
double readDouble(const ByteVec& buffer, size_t& offset);
std::string readString(const ByteVec& buffer, size_t& offset, int maxChars);

void writeBoolean(ByteVec& buffer, const bool& value);
void writeByte(ByteVec& buffer, const int8_t& value);
void writeUnsignedByte(ByteVec& buffer, const uint8_t& value);
void writeShort(ByteVec& buffer, const short& value);
void writeUnsignedShort(ByteVec& buffer, const uint16_t& value);
void writeInt(ByteVec& buffer, const int& value);
void writeLong(ByteVec& buffer, const int64_t& value);
void writeFloat(ByteVec& buffer, const float& value);
void writeDouble(ByteVec& buffer, const double& value);
void writeString(ByteVec& buffer, const std::string& value, int maxChars);

// Minecraft type serialization functions
int constexpr SEGMENT_BITS = 0x7F;
int constexpr CONTINUE_BIT = 0x80;
int readVarInt(const ByteVec& buffer, size_t& offset);
int64_t readVarLong(const ByteVec& buffer, size_t& offset);
void writeVarInt(ByteVec& buffer, int value);
void writeVarLong(ByteVec& buffer, int64_t value);

// Helper functions
inline bool isReadable(const ByteVec& buffer, const size_t& offset, const size_t& bytes) {
    if (offset + bytes > buffer.size())
        throw PacketSerializationException("Buffer overflow: Tried reading beyond buffer size.");

    return true;
}
int countUTF16CodeUnits(const std::string& utf8);
} // namespace stratos

#endif
