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

#include <cstring>

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

bool stratos::ByteBuffer::readBoolean() const {
    checkRead(sizeof(bool));
    return this->buffer[this->offset++] != 0;
}

int8_t stratos::ByteBuffer::readByte() const {
    checkRead(sizeof(int8_t));
    return static_cast<int8_t>(this->buffer[offset++]);
}

uint8_t stratos::ByteBuffer::readUnsignedByte() const {
    checkRead(sizeof(uint8_t));
    return static_cast<uint8_t>(this->buffer[offset++]);
}

short stratos::ByteBuffer::readShort() const {
    checkRead(sizeof(short));
    const auto high = static_cast<int16_t>(buffer[offset++]);
    const auto low  = static_cast<int16_t>(buffer[offset++]);
    return static_cast<short>(high << 8 | low & 0xFF);
}

uint16_t stratos::ByteBuffer::readUnsignedShort() const {
    checkRead(sizeof(uint16_t));
    const auto high = static_cast<uint16_t>(buffer[offset++]);
    const auto low  = static_cast<uint16_t>(buffer[offset++]);
    return static_cast<uint16_t>(high << 8 | low & 0xFF);
}

int stratos::ByteBuffer::readInt() const {
    checkRead(sizeof(int));
    const auto b1 = static_cast<int32_t>(buffer[offset++]);
    const auto b2 = static_cast<int32_t>(buffer[offset++]);
    const auto b3 = static_cast<int32_t>(buffer[offset++]);
    const auto b4 = static_cast<int32_t>(buffer[offset++]);
    return b1 << 24 | b2 << 16 | b3 << 8 | b4 & 0xFF;
}
int stratos::ByteBuffer::readInt24() const {
    checkRead(3);
    const auto b1 = static_cast<int32_t>(buffer[offset++]);
    const auto b2 = static_cast<int32_t>(buffer[offset++]);
    const auto b3 = static_cast<int32_t>(buffer[offset++]);
    return b1 << 16 | b2 << 8 | b3 & 0xFF;
}

int64_t stratos::ByteBuffer::readLong() const {
    checkRead(sizeof(int64_t));
    int64_t result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= static_cast<int64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    return result;
}

float stratos::ByteBuffer::readFloat() const {
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

double stratos::ByteBuffer::readDouble() const {
    checkRead(sizeof(double));
    uint64_t bits = 0;
    for (int i = 0; i < 8; ++i) {
        bits |= static_cast<uint64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    double value;
    memcpy(&value, &bits, sizeof(double));
    return value;
}

std::string stratos::ByteBuffer::readString(const int maxChars) const {
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

int stratos::ByteBuffer::readVarInt() const {
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

int64_t stratos::ByteBuffer::readVarLong() const {
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

std::vector<uint64_t> stratos::ByteBuffer::readBitSet() const {
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

std::vector<bool> stratos::ByteBuffer::readFixedBitSet(size_t length) const {
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

ByteVec stratos::ByteBuffer::readByteArray(size_t length) const {
    ByteVec result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result.push_back(readByte());
    }
    return result;
}
void stratos::ByteBuffer::readFixedLongArray(std::vector<int64_t>& longs) const {
    for (size_t i = 0; i < longs.size(); ++i)
        longs[i] = readLong();
}
void stratos::ByteBuffer::writeBoolean(const bool value) {
    buffer.push_back(static_cast<unsigned char>(value ? 1 : 0));
}
void stratos::ByteBuffer::writeByte(const int8_t value) {
    buffer.push_back(static_cast<unsigned char>(value));
}
void stratos::ByteBuffer::writeUnsignedByte(const uint8_t value) {
    buffer.push_back(value);
}
void stratos::ByteBuffer::writeShort(const short value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::ByteBuffer::writeUnsignedShort(const uint16_t value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::ByteBuffer::writeInt(const int value) {
    buffer.push_back(static_cast<unsigned char>(value >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::ByteBuffer::writeLong(const int64_t value) {
    for (int i = 7; i >= 0; --i) buffer.push_back(static_cast<unsigned char>(value >> (i * 8) & 0xFF));
}
void stratos::ByteBuffer::writeFloat(const float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(float));
    buffer.push_back(static_cast<unsigned char>(bits >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits & 0xFF));
}
void stratos::ByteBuffer::writeDouble(const double value) {
    uint64_t bits;
    std::memcpy(&bits, &value, sizeof(double));
    for (int i = 7; i >= 0; --i) buffer.push_back(static_cast<unsigned char>(bits >> (i * 8) & 0xFF));
}
void stratos::ByteBuffer::writeString(const std::string& value, const int maxChars) {
    if (const int utf16Units = countCodeUnits(value); utf16Units > maxChars) throw BufferOverflowException("String: exceeds character limit");
    if (value.size() > maxChars * 3) throw BufferOverflowException("String: exceeds UTF-8 byte size limit");
    const auto length = static_cast<int32_t>(value.size());
    writeVarInt(length);
    buffer.insert(buffer.end(), value.begin(), value.end());
}
void stratos::ByteBuffer::writeVarInt(int value) {
    while (true) {
        if ((value & ~SEGMENT_BITS) == 0) {
            writeByte(static_cast<uint8_t>(value));
            return;
        }
        writeByte(static_cast<uint8_t>((value & SEGMENT_BITS) | CONTINUE_BIT));
        value = static_cast<uint32_t>(value) >> 7;
    }
}
void stratos::ByteBuffer::writeVarLong(int64_t value) {
    while (true) {
        if ((value & ~static_cast<int64_t>(SEGMENT_BITS)) == 0) {
            writeByte(static_cast<uint8_t>(value));
            return;
        }
        writeByte(static_cast<uint8_t>((value & SEGMENT_BITS) | CONTINUE_BIT));
        value = static_cast<uint64_t>(value) >> 7;
    }
}
void stratos::ByteBuffer::writeBitSet(const std::vector<uint64_t>& longs) {
    const int length = static_cast<int>(longs.size());
    writeVarInt(length);
    for (const uint64_t value : longs)
        for (int i = 7; i >= 0; --i) buffer.push_back(value >> (i * 8) & 0xFF);
}
void stratos::ByteBuffer::writeFixedBitSet(const std::vector<bool>& bits, const size_t length) {
    const size_t byteLength = (length + 7) / 8;
    for (size_t byteIndex = 0; byteIndex < byteLength; ++byteIndex) {
        uint8_t byte = 0;
        for (int bit = 0; bit < 8; ++bit)
            if (const size_t bitIndex = byteIndex * 8 + bit; bitIndex < bits.size() && bits[bitIndex]) byte |= 1 << bit;
        buffer.push_back(byte);
    }
}
void stratos::ByteBuffer::writeByteArray(const ByteVec& values) {
    for (const auto& value : values) buffer.push_back(value);
}
void stratos::ByteBuffer::writeFixedLongArray(const std::vector<int64_t>& longs) {
    for (const auto& value : longs)
        writeLong(value);
}
void    stratos::ByteBuffer::setOffset(const size_t newOffset) {
    if (newOffset > buffer.size()) {
        throw BufferOverflowException("Offset exceeds buffer size");
    }
    offset = newOffset;
}
uint8_t stratos::ByteBuffer::operator[](const size_t index) const {
    if (index >= buffer.size()) {
        throw BufferUnderflowException("Index out of bounds for buffer access");
    }
    return buffer[index];
}
uint8_t& stratos::ByteBuffer::operator[](const size_t index) {
    if (index >= buffer.size()) {
        throw BufferUnderflowException("Index out of bounds for buffer access");
    }
    return buffer[index];
}
int stratos::getEncodedSizeInBytes(const int value) {
    if (value == 0) return 1;
    for (int i = 0; i < 5; ++i) {
        if ((value & -1 << i * 7) != 0) continue;
        return i;
    }
    return 5;
}
int stratos::getEncodedSizeInBytes(const int64_t value) {
    if (value == 0) return 1;
    for (int i = 0; i < 10; ++i) {
        if ((value & -1LL << i * 7) != 0) continue;
        return i;
    }
    return 10;
}
