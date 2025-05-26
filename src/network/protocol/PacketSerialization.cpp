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

#include <cstring>

bool        stratos::readBoolean(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(bool));
    const bool value = buffer[offset++] != 0;
    return value;
}
int8_t      stratos::readByte(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(int8_t));
    const auto value = static_cast<int8_t>(buffer[offset++]);
    return value;
}
uint8_t     stratos::readUnsignedByte(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(uint8_t));
    const auto value = static_cast<uint8_t>(buffer[offset++]);
    return value;
}
short       stratos::readShort(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(short));
    const auto high = static_cast<int16_t>(buffer[offset++]);
    const auto low  = static_cast<int16_t>(buffer[offset++]);
    return static_cast<short>(high << 8 | low & 0xFF);
}
uint16_t    stratos::readUnsignedShort(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(uint16_t));
    const auto high = static_cast<uint16_t>(buffer[offset++]);
    const auto low  = static_cast<uint16_t>(buffer[offset++]);
    return static_cast<uint16_t>(high << 8 | low & 0xFF);
}
int         stratos::readInt(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(int));
    const auto b1 = static_cast<int32_t>(buffer[offset++]);
    const auto b2 = static_cast<int32_t>(buffer[offset++]);
    const auto b3 = static_cast<int32_t>(buffer[offset++]);
    const auto b4 = static_cast<int32_t>(buffer[offset++]);
    return b1 << 24 | b2 << 16 | b3 << 8 | b4 & 0xFF;
}
int64_t        stratos::readLong(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(long));
    int64_t result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= static_cast<int64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    return result;
}
float       stratos::readFloat(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(float));
    const uint32_t bits = static_cast<uint32_t>(buffer[offset]) << 24 |
                    static_cast<uint32_t>(buffer[offset + 1]) << 16 |
                    static_cast<uint32_t>(buffer[offset + 2]) << 8 |
                    static_cast<uint32_t>(buffer[offset + 3]);
    offset += 4;
    float value;
    std::memcpy(&value, &bits, sizeof(float));
    return value;
}
double      stratos::readDouble(const ByteVec& buffer, size_t& offset) {
    uint64_t bits = 0;
    for (int i = 0; i < 8; ++i)
        bits |= static_cast<uint64_t>(buffer[offset++]) << ((7 - i) * 8);
    double value;
    std::memcpy(&value, &bits, sizeof(double));
    return value;
}
std::string stratos::readString(const ByteVec& buffer, size_t& offset, const int maxChars) {
    const uint32_t length = readVarInt(buffer, offset);

    if (length > maxChars * 3)
        throw PacketSerializationException("String: length exceeds UTF-8 byte size limit");
    if (offset + length > buffer.size())
        throw PacketSerializationException("Buffer overflow: Tried reading beyond buffer size.");

    std::string str(buffer.begin() + offset, buffer.begin() + offset + length);
    offset += length;
    if (const int utf16Units = countUTF16CodeUnits(str); utf16Units > maxChars) {
        throw PacketSerializationException("String: character length exceeds maximum");
    }

    return str;
}
void        stratos::writeBoolean(ByteVec& buffer, const bool& value) {
    buffer.push_back(static_cast<unsigned char>(value ? 1 : 0));
}
void        stratos::writeByte(ByteVec& buffer, const int8_t& value) {
    buffer.push_back(static_cast<unsigned char>(value));
}
void        stratos::writeUnsignedByte(ByteVec& buffer, const uint8_t& value) {
    buffer.push_back(value);
}
void        stratos::writeShort(ByteVec& buffer, const short& value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void        stratos::writeUnsignedShort(ByteVec& buffer, const uint16_t& value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void        stratos::writeInt(ByteVec& buffer, const int& value) {
    buffer.push_back(static_cast<unsigned char>(value >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void        stratos::writeLong(ByteVec& buffer, const int64_t& value) {
    for (int i = 7; i >= 0; --i) {
        buffer.push_back(static_cast<unsigned char>(value >> (i * 8) & 0xFF));
    }
}
void        stratos::writeFloat(ByteVec& buffer, const float& value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(float));
    buffer.push_back(static_cast<unsigned char>(bits >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits & 0xFF));
}
void        stratos::writeDouble(ByteVec& buffer, const double& value) {
    uint64_t bits;
    std::memcpy(&bits, &value, sizeof(double));
    for (int i = 7; i >= 0; --i) {
        buffer.push_back(static_cast<unsigned char>((bits >> (i * 8)) & 0xFF));
    }
}
void        stratos::writeString(ByteVec& buffer, const std::string& value, const int maxChars) {
    if (const int utf16Units = countUTF16CodeUnits(value); utf16Units > maxChars) {
        throw PacketSerializationException("String: exceeds character limit");
    }

    if (value.size() > maxChars * 3) {
        throw PacketSerializationException("String: exceeds UTF-8 byte size limit");
    }

    writeVarInt(buffer, static_cast<uint32_t>(value.size()));
    buffer.insert(buffer.end(), value.begin(), value.end());
}
int         stratos::readVarInt(const ByteVec& buffer, size_t& offset) {
    int value = 0;
    int position = 0;
    while (true) {
        const uint8_t currentByte = readByte(buffer, offset);
        value |= (currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 32)
            throw std::runtime_error("VarInt: too many bytes");
    }
    return value;
}
int64_t     stratos::readVarLong(const ByteVec& buffer, size_t& offset) {
    int64_t value = 0;
    int position = 0;
    while (true) {
        const uint8_t currentByte = readByte(buffer, offset);
        value |= static_cast<int64_t>(currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 64)
            throw std::runtime_error("VarLong is too big");
    }
    return value;
}
void        stratos::writeVarInt(ByteVec& buffer, int value) {
    while (true) {
        if ((value & ~SEGMENT_BITS) == 0) {
            writeByte(buffer, static_cast<uint8_t>(value));
            return;
        }
        writeByte(buffer, static_cast<uint8_t>((value & SEGMENT_BITS) | CONTINUE_BIT));
        value = static_cast<uint32_t>(value) >> 7;
    }
}
void stratos::writeVarLong(ByteVec& buffer, int64_t value) {
    while (true) {
        if ((value & ~static_cast<int64_t>(SEGMENT_BITS)) == 0) {
            writeByte(buffer, static_cast<uint8_t>(value));
            return;
        }
        writeByte(buffer, static_cast<uint8_t>((value & SEGMENT_BITS) | CONTINUE_BIT));
        value = static_cast<uint64_t>(value) >> 7;
    }
}
int stratos::countUTF16CodeUnits(const std::string& utf8) {
    int count = 0;
    size_t i = 0;

    while (i < utf8.size()) {
        unsigned char c = utf8[i];

        if (c < 0x80) {
            ++i;
            ++count;
        } else if ((c >> 5) == 0x6) {
            i += 2;
            ++count;
        } else if ((c >> 4) == 0xE) {
            i += 3;
            ++count;
        } else if ((c >> 3) == 0x1E) {
            i += 4;
            count += 2;
        } else {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
    }

    return count;
}