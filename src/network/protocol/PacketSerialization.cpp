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

#include <codecvt>
#include <cstring>
#include <locale>

bool stratos::readBoolean(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(bool));
    const bool value = buffer[offset++] != 0;
    return value;
}
int8_t stratos::readByte(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(int8_t));
    const auto value = static_cast<int8_t>(buffer[offset++]);
    return value;
}
uint8_t stratos::readUnsignedByte(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(uint8_t));
    const auto value = static_cast<uint8_t>(buffer[offset++]);
    return value;
}
short stratos::readShort(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(short));
    const auto high = static_cast<int16_t>(buffer[offset++]);
    const auto low  = static_cast<int16_t>(buffer[offset++]);
    return static_cast<short>(high << 8 | low & 0xFF);
}
uint16_t stratos::readUnsignedShort(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(uint16_t));
    const auto high = static_cast<uint16_t>(buffer[offset++]);
    const auto low  = static_cast<uint16_t>(buffer[offset++]);
    return static_cast<uint16_t>(high << 8 | low & 0xFF);
}
int stratos::readInt(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(int));
    const auto b1 = static_cast<int32_t>(buffer[offset++]);
    const auto b2 = static_cast<int32_t>(buffer[offset++]);
    const auto b3 = static_cast<int32_t>(buffer[offset++]);
    const auto b4 = static_cast<int32_t>(buffer[offset++]);
    return b1 << 24 | b2 << 16 | b3 << 8 | b4 & 0xFF;
}
int64_t stratos::readLong(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(long));
    int64_t result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= static_cast<int64_t>(buffer[offset++]) << ((7 - i) * 8);
    }
    return result;
}
float stratos::readFloat(const ByteVec& buffer, size_t& offset) {
    isReadable(buffer, offset, sizeof(float));
    const uint32_t bits = static_cast<uint32_t>(buffer[offset]) << 24 | static_cast<uint32_t>(buffer[offset + 1]) << 16 | static_cast<uint32_t>(buffer[offset + 2]) << 8 |
                          static_cast<uint32_t>(buffer[offset + 3]);
    offset += 4;
    float value;
    std::memcpy(&value, &bits, sizeof(float));
    return value;
}
double stratos::readDouble(const ByteVec& buffer, size_t& offset) {
    uint64_t bits = 0;
    for (int i = 0; i < 8; ++i) bits |= static_cast<uint64_t>(buffer[offset++]) << ((7 - i) * 8);
    double value;
    std::memcpy(&value, &bits, sizeof(double));
    return value;
}
std::string stratos::readString(const ByteVec& buffer, size_t& offset, const int maxChars) {
    const uint32_t length = readVarInt(buffer, offset);

    if (length > maxChars * 3) throw PacketSerializationException("String: length exceeds UTF-8 byte size limit");
    if (offset + length > buffer.size()) throw PacketSerializationException("Buffer overflow: Tried reading beyond buffer size.");

    std::string str(buffer.begin() + offset, buffer.begin() + offset + length);
    offset += length;
    if (const int utf16Units = countUTF16CodeUnits(str); utf16Units > maxChars) {
        throw PacketSerializationException("String: character length exceeds maximum");
    }

    return str;
}
std::string stratos::readStringUTF16BE(const ByteVec& buffer, size_t& offset) {
    if (offset + 2 > buffer.size()) {
        throw std::out_of_range("StringUTF16BE: not enough bytes for length");
    }
    const uint16_t length = static_cast<uint16_t>(buffer[offset++]) << 8 | static_cast<uint16_t>(buffer[offset++]);
    if (const size_t byteLength = length * 2; offset + byteLength > buffer.size())
        throw PacketSerializationException("StringUTF16BE: not enough bytes for string content");
    std::u16string utf16;
    utf16.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        const char16_t ch = static_cast<char16_t>(buffer[offset++]) << 8 | static_cast<char16_t>(buffer[offset++]);
        utf16.push_back(ch);
    }
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(utf16);
}
void stratos::writeBoolean(ByteVec& buffer, const bool value) {
    buffer.push_back(static_cast<unsigned char>(value ? 1 : 0));
}
void stratos::writeByte(ByteVec& buffer, const int8_t value) {
    buffer.push_back(static_cast<unsigned char>(value));
}
void stratos::writeUnsignedByte(ByteVec& buffer, const uint8_t value) {
    buffer.push_back(value);
}
void stratos::writeShort(ByteVec& buffer, const short value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::writeUnsignedShort(ByteVec& buffer, const uint16_t value) {
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::writeInt(ByteVec& buffer, const int value) {
    buffer.push_back(static_cast<unsigned char>(value >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(value & 0xFF));
}
void stratos::writeLong(ByteVec& buffer, const int64_t value) {
    for (int i = 7; i >= 0; --i) {
        buffer.push_back(static_cast<unsigned char>(value >> (i * 8) & 0xFF));
    }
}
void stratos::writeFloat(ByteVec& buffer, const float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(float));
    buffer.push_back(static_cast<unsigned char>(bits >> 24 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 16 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits >> 8 & 0xFF));
    buffer.push_back(static_cast<unsigned char>(bits & 0xFF));
}
void stratos::writeDouble(ByteVec& buffer, const double value) {
    uint64_t bits;
    std::memcpy(&bits, &value, sizeof(double));
    for (int i = 7; i >= 0; --i) {
        buffer.push_back(static_cast<unsigned char>(bits >> (i * 8) & 0xFF));
    }
}
void stratos::writeString(ByteVec& buffer, const std::string& value, const int maxChars) {
    if (const int utf16Units = countUTF16CodeUnits(value); utf16Units > maxChars) {
        throw PacketSerializationException("String: exceeds character limit");
    }

    if (value.size() > maxChars * 3) {
        throw PacketSerializationException("String: exceeds UTF-8 byte size limit");
    }

    auto length = static_cast<int32_t>(value.size());
    writeVarInt(buffer, length);
    buffer.insert(buffer.end(), value.begin(), value.end());
}
void stratos::writeStringUTF16BE(ByteVec& buffer, const std::string& value) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    const std::u16string                                              utf16  = convert.from_bytes(value);
    const auto length = static_cast<uint16_t>(utf16.size());
    buffer.push_back(length >> 8 & 0xFF); // big-endian
    buffer.push_back(length & 0xFF);
    for (const char16_t& ch : utf16) {
        buffer.push_back(ch >> 8 & 0xFF);  // high byte
        buffer.push_back(ch & 0xFF);         // low byte
    }
}
int stratos::readVarInt(const ByteVec& buffer, size_t& offset) {
    int value    = 0;
    int position = 0;
    while (true) {
        const uint8_t currentByte = readByte(buffer, offset);
        value |= (currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 32) throw PacketSerializationException("VarInt: too many bytes");
    }
    return value;
}
int64_t stratos::readVarLong(const ByteVec& buffer, size_t& offset) {
    int64_t value    = 0;
    int     position = 0;
    while (true) {
        const uint8_t currentByte = readByte(buffer, offset);
        value |= static_cast<int64_t>(currentByte & SEGMENT_BITS) << position;
        if ((currentByte & CONTINUE_BIT) == 0) break;
        position += 7;
        if (position >= 64) throw PacketSerializationException("VarLong is too big");
    }
    return value;
}
std::vector<uint64_t> stratos::readBitSet(const ByteVec& buffer, size_t& offset) {
    const uint32_t        length = readVarInt(buffer, offset);
    std::vector<uint64_t> longs(length);
    for (uint32_t i = 0; i < length; ++i) {
        if (offset + 7 >= buffer.size()) throw PacketSerializationException("BitSet: buffer underflow");
        uint64_t value = 0;
        for (int j = 0; j < 8; ++j) value |= static_cast<uint64_t>(buffer[offset++]) << ((7 - j) * 8);
        longs[i] = value;
    }
    return longs;
}
std::vector<bool> stratos::readFixedBitSet(const ByteVec& buffer, size_t& offset, const size_t length) {
    const size_t byteLength = (length + 7) / 8;
    if (offset + byteLength > buffer.size()) throw PacketSerializationException("FixedBitSet: buffer underflow");
    std::vector<bool> bits(length);
    for (size_t i = 0; i < length; ++i) {
        const uint8_t byte = buffer[offset + i / 8];
        bits[i]            = (byte >> (i % 8)) & 1;
    }
    offset += byteLength;
    return bits;
}
template <typename T>
bool stratos::readOptionalX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&)>& readFunc, T& readValue, const bool isPresent) {
    if (!isPresent) return false;
    readValue = &readFunc(buffer, offset);
    return true;
}
template <typename T> bool stratos::readPrefixedOptionalX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&)>& readFunc, T& readValue) {
    const bool isPresent = readBoolean(buffer, offset);
    if (isPresent) readValue = readFunc(buffer, offset);
    return isPresent;
}
template <typename T> std::vector<T> stratos::readArrayOfX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&)>& readFunc, size_t count) {
    std::vector<T> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) result.push_back(readFunc(buffer, offset));
    return result;
}
template <typename T>
std::vector<T> stratos::readArrayOfX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&, int)>& readFunc, size_t count, int length) {
    std::vector<T> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) result.push_back(readFunc(buffer, offset, length));
    return result;
}
template <typename T> std::vector<T> stratos::readPrefixedArrayOfX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&)>& readFunc) {
    return readArrayOfX<T>(buffer, offset, readFunc, readVarInt(buffer, offset));
}
template <typename T>
std::vector<T> stratos::readPrefixedArrayOfX(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&, int)>& readFunc, const int length) {
    return readArrayOfX<T>(buffer, offset, readFunc, readVarInt(buffer, offset), length);
}
template <typename T, typename U>
U stratos::readXEnum(const ByteVec& buffer, size_t& offset, const std::function<T(const ByteVec&, size_t&)>& readFunc, std::function<U(const T&)> enumConverter) {
    T value = readFunc(buffer, offset);
    return enumConverter(value);
}
template <typename T> std::vector<T> stratos::readEnumSet(const ByteVec& buffer, size_t& offset, const std::function<T(const bool& bit)>& enumConverter, const size_t length) {
    std::vector<T> result;
    for (bool bit : readFixedBitSet(buffer, offset, length)) result.push_back(enumConverter(bit));
    return result;
}
stratos::ByteVec stratos::readByteArray(const ByteVec& buffer, size_t& offset, const size_t length) {
    ByteVec result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) result.push_back(readByte(buffer, offset));
    return result;
}
void stratos::writeVarInt(ByteVec& buffer, int value) {
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
void stratos::writeBitSet(ByteVec& buffer, const std::vector<uint64_t>& longs) {
    const int length = static_cast<int>(longs.size());
    writeVarInt(buffer, length);
    for (const uint64_t value : longs) {
        for (int i = 7; i >= 0; --i) buffer.push_back(value >> (i * 8) & 0xFF);
    }
}
void stratos::writeFixedBitSet(ByteVec& buffer, const std::vector<bool>& bits, const size_t length) {
    const size_t byteLength = (length + 7) / 8;
    for (size_t byteIndex = 0; byteIndex < byteLength; ++byteIndex) {
        uint8_t byte = 0;
        for (int bit = 0; bit < 8; ++bit)
            if (const size_t bitIndex = byteIndex * 8 + bit; bitIndex < bits.size() && bits[bitIndex]) byte |= 1 << bit;
        buffer.push_back(byte);
    }
}
template <typename T> void stratos::writeOptionalX(ByteVec& buffer, const T* value, const std::function<void(ByteVec&, const T&)>& writeFunc, const bool isPresent) {
    if (!isPresent || value == nullptr) return;
    writeFunc(buffer, *value);
}
template <typename T>
void stratos::writeOptionalX(ByteVec& buffer, const T* value, const std::function<void(ByteVec&, const T&, int)>& writeFunc, const bool isPresent, const int length) {
    if (!isPresent || value == nullptr) return;
    writeFunc(buffer, *value, length);
}
template <typename T> void stratos::writePrefixedOptionalX(ByteVec& buffer, const T* value, const std::function<void(ByteVec&, const T&)>& writeFunc) {
    const bool present = value != nullptr;
    writeBoolean(buffer, present);
    if (!present) return;
    writeFunc(buffer, *value);
}
template <typename T> void stratos::writePrefixedOptionalX(ByteVec& buffer, const T* value, const std::function<void(ByteVec&, const T&, int)>& writeFunc, const int length) {
    const bool present = value != nullptr;
    writeBoolean(buffer, present);
    if (!present) return;
    writeFunc(buffer, *value, length);
}
template <typename T> void stratos::writeArrayOfX(ByteVec& buffer, const std::vector<T>& values, const std::function<void(ByteVec&, const T&)>& writeFunc) {
    for (const auto& value : values) {
        writeFunc(buffer, value);
    }
}
template <typename T> void stratos::writeArrayOfX(ByteVec& buffer, const std::vector<T>& values, const std::function<void(ByteVec&, const T&, int)>& writeFunc, int length) {
    for (const auto& value : values) {
        writeFunc(buffer, value, length);
    }
}
template <typename T> void stratos::writePrefixedArrayOfX(ByteVec& buffer, const std::vector<T>& values, const std::function<void(ByteVec&, const T&)>& writeFunc) {
    writeVarInt(buffer, static_cast<int>(values.size()));
    writeArrayOfX(buffer, values, writeFunc);
}
template <typename T> void stratos::writeXEnum(ByteVec& buffer, const T& value, const std::function<void(ByteVec&, const T&)>& writeFunc) {
    writeFunc(buffer, value);
}
template <typename T> void stratos::writeXEnum(ByteVec& buffer, const T& value, void (*writeFunc)(ByteVec&, const T&, const int&), const int length) {
    writeFunc(buffer, value, length);
}
void stratos::writeByteArray(ByteVec& buffer, const ByteVec& values) {
    for (const auto& value : values) buffer.push_back(value);
}
int stratos::countUTF16CodeUnits(const std::string& utf8) {
    int    count = 0;
    size_t i     = 0;

    while (i < utf8.size()) {
        unsigned char c = utf8[i];

        if (c < 0x80) {
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