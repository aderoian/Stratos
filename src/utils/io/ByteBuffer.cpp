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

#include "ByteBuffer.h"

int constexpr SEGMENT_BITS = 0x7F;
int constexpr CONTINUE_BIT = 0x80;

int countCodeUnits(const std::string& utf8) {
    int    count = 0;
    size_t i     = 0;
    while (i < utf8.size()) {
        if (const unsigned char c = utf8[i]; c < 0x80) {
            ++i;
            ++count;
        } else if (c >> 5 == 0x6) {
            i += 2;
            ++count;
        } else if (c >> 4 == 0xE) {
            i += 3;
            ++count;
        } else if (c >> 3 == 0x1E) {
            i += 4;
            count += 2;
        } else {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
    }
    return count;
}

bool stratos::ByteBuffer::readBoolean() {
    checkRead(sizeof(bool));
    return this->buffer[this->offset++] != 0;
}

int8_t stratos::ByteBuffer::readByte() {
    checkRead(sizeof(int8_t));
    return static_cast<int8_t>(this->buffer[offset++]);
}

uint8_t stratos::ByteBuffer::readUnsignedByte() {
    checkRead(sizeof(uint8_t));
    return static_cast<uint8_t>(this->buffer[offset++]);
}

short stratos::ByteBuffer::readShort() {
    checkRead(sizeof(short));
    const auto high = static_cast<int16_t>(buffer[offset++]);
    const auto low  = static_cast<int16_t>(buffer[offset++]);
    return static_cast<short>(high << 8 | low & 0xFF);
}

uint16_t stratos::ByteBuffer::readUnsignedShort() {
    checkRead(sizeof(uint16_t));
    const auto high = static_cast<uint16_t>(buffer[offset++]);
    const auto low  = static_cast<uint16_t>(buffer[offset++]);
    return static_cast<uint16_t>(high << 8 | low & 0xFF);
}

int stratos::ByteBuffer::readInt() {
    checkRead(sizeof(int));
    const auto b1 = static_cast<int32_t>(buffer[offset++]);
    const auto b2 = static_cast<int32_t>(buffer[offset++]);
    const auto b3 = static_cast<int32_t>(buffer[offset++]);
    const auto b4 = static_cast<int32_t>(buffer[offset++]);
    return b1 << 24 | b2 << 16 | b3 << 8 | b4 & 0xFF;
}

int64_t stratos::ByteBuffer::readLong() {
    checkRead(sizeof(int64_t));
    int64_t result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= static_cast<int64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    return result;
}

float stratos::ByteBuffer::readFloat() {
    checkRead(sizeof(float));
    const uint32_t bits =
        static_cast<uint32_t>(buffer[offset]) << 24 |
        static_cast<uint32_t>(buffer[offset + 1]) << 16 |
        static_cast<uint32_t>(buffer[offset + 2]) << 8 |
        static_cast<uint32_t>(buffer[offset + 3]);
    offset += 4;
    float value;
    memcpy(&value, &bits, sizeof(float));
    return value;
}

double stratos::ByteBuffer::readDouble() {
    checkRead(sizeof(double));
    uint64_t bits = 0;
    for (int i = 0; i < 8; ++i) {
        bits |= static_cast<uint64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    double value;
    memcpy(&value, &bits, sizeof(double));
    return value;
}

std::string stratos::ByteBuffer::readString(int maxChars) {
    const uint32_t length = readVarInt();
    if (length > maxChars * 3) {
        throw BufferOverflowException("String length exceeds maximum allowed characters.");
    }
    if (offset + length > buffer.size()) {
        throw BufferUnderflowException("Not enough data to read the string.");
    }

    std::string str(buffer.begin() + offset, buffer.begin() + offset + length);
    offset += length;
    if (const int utf16Units = countCodeUnits(str); utf16Units > maxChars) {
        throw BufferOverflowException("String length exceeds maximum allowed UTF-16 code units.");
    }

    return str;
}

int stratos::ByteBuffer::readVarInt() {
    int value    = 0;
    int position = 0;
    while (true) {
        const uint8_t currentByte = readByte();
        value |= (currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 32) {
            throw BufferOverflowException("VarInt is too big to fit in an int.");
        }
    }
    return value;
}

int64_t stratos::ByteBuffer::readVarLong() {
    int64_t value    = 0;
    int     position = 0;
    while (true) {
        const uint8_t currentByte = readByte();
        value |= static_cast<int64_t>(currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 64) {
            throw BufferOverflowException("VarLong is too big to fit in an int64_t.");
        }
    }
    return value;
}

std::vector<uint64_t> stratos::ByteBuffer::readBitSet() {
    const uint32_t        length = readVarInt();
    std::vector<uint64_t> longs(length);
    for (uint32_t i = 0; i < length; ++i) {
        if (offset + 7 >= buffer.size()) {
            throw BufferUnderflowException("Not enough data to read a long from BitSet.");
        }
        uint64_t value = 0;
        for (int j = 0; j < 8; ++j) value |= static_cast<uint64_t>(buffer[offset++]) << ((7 - j) * 8);
        longs[i] = value;
    }
    return longs;
}

std::vector<bool> stratos::ByteBuffer::readFixedBitSet(size_t length) {
    const size_t byteLength = (length + 7) / 8;
    if (offset + byteLength > buffer.size()) {
        throw BufferUnderflowException("Not enough data to read FixedBitSet.");
    }
    std::vector<bool> bits(length);
    for (size_t i = 0; i < length; ++i) {
        const uint8_t byte = buffer[offset + i / 8];
        bits[i]            = (byte >> (i % 8)) & 1;
    }
    offset += byteLength;
    return bits;
}

ByteVec stratos::ByteBuffer::readByteArray(size_t length) {
    ByteVec result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result.push_back(readByte());
    }
    return result;
}
