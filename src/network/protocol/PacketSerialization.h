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
struct Identifier;
using ByteVec = std::vector<unsigned char>;

class PacketSerializationException final : public std::logic_error {
  public:
    explicit PacketSerializationException(const char* message) : logic_error(message) {};
    explicit PacketSerializationException(const std::string& message) : logic_error(message) {};
};

// Generic serialization functions
bool        readBoolean(const ByteVec& buffer, size_t& offset);
int8_t      readByte(const ByteVec& buffer, size_t& offset);
uint8_t     readUnsignedByte(const ByteVec& buffer, size_t& offset);
short       readShort(const ByteVec& buffer, size_t& offset);
uint16_t    readUnsignedShort(const ByteVec& buffer, size_t& offset);
int         readInt(const ByteVec& buffer, size_t& offset);
int64_t     readLong(const ByteVec& buffer, size_t& offset);
float       readFloat(const ByteVec& buffer, size_t& offset);
double      readDouble(const ByteVec& buffer, size_t& offset);
std::string readString(const ByteVec& buffer, size_t& offset, int maxChars);
std::string readStringUTF16BE(const ByteVec& buffer, size_t& offset);

void writeBoolean(ByteVec& buffer, bool value);
void writeByte(ByteVec& buffer, int8_t value);
void writeUnsignedByte(ByteVec& buffer, uint8_t value);
void writeShort(ByteVec& buffer, short value);
void writeUnsignedShort(ByteVec& buffer, uint16_t value);
void writeInt(ByteVec& buffer, int value);
void writeLong(ByteVec& buffer, int64_t value);
void writeFloat(ByteVec& buffer, float value);
void writeDouble(ByteVec& buffer, double value);
void writeString(ByteVec& buffer, const std::string& value, int maxChars);
void writeStringUTF16BE(ByteVec& buffer, const std::string& value);

// Minecraft type serialization functions
int constexpr SEGMENT_BITS = 0x7F;
int constexpr CONTINUE_BIT = 0x80;
int     readVarInt(const ByteVec& buffer, size_t& offset);
int64_t readVarLong(const ByteVec& buffer, size_t& offset);
// TODO: readTextComponent
// TODO: readJSONTextComponent
Identifier readIdentifier(const ByteVec& buffer, size_t& offset);
// TODO: readEntityMetaData
// TODO: readSlot
// TODO: readHashedSlot
// TODO: readNBT
// TODO: readPosition
// TODO: readAngle
// TODO: readUUID
std::vector<uint64_t> readBitSet(const ByteVec& buffer, size_t& offset);
std::vector<bool>     readFixedBitSet(const ByteVec& buffer, size_t& offset, size_t length);
template <typename T, typename ReadFunc> bool readOptionalX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, T& readValue, const bool isPresent) {
    if (!isPresent) return false;
    readValue = &readFunc(buffer, offset);
    return true;
}
template <typename T, typename ReadFunc> bool readPrefixedOptionalX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, T& readValue) {
    const bool isPresent = readBoolean(buffer, offset);
    if (isPresent) readValue = readFunc(buffer, offset);
    return isPresent;
}
template <typename T, typename ReadFunc> std::vector<T> readArrayOfX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, size_t count) {
    std::vector<T> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) result.push_back(readFunc(buffer, offset));
    return result;
}
template <typename T, typename ReadFunc>
std::vector<T> readArrayOfX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, size_t count, int length) {
    std::vector<T> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) result.push_back(readFunc(buffer, offset, length));
    return result;
}
template <typename T, typename ReadFunc> std::vector<T> readPrefixedArrayOfX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc) {
    return readArrayOfX<T>(buffer, offset, readFunc, readVarInt(buffer, offset));
}
template <typename T, typename ReadFunc>
std::vector<T> readPrefixedArrayOfX(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, const int length) {
    return readArrayOfX<T>(buffer, offset, readFunc, readVarInt(buffer, offset), length);
}
template <typename T, typename U, typename ReadFunc, typename EnumConverter>
U readXEnum(const ByteVec& buffer, size_t& offset, const ReadFunc& readFunc, const EnumConverter& enumConverter) {
    T value = readFunc(buffer, offset);
    return enumConverter(value);
}
template <typename T, typename EnumConverter> std::vector<T> readEnumSet(const ByteVec& buffer, size_t& offset, const EnumConverter& enumConverter, const size_t length) {
    std::vector<T> result;
    for (bool bit : readFixedBitSet(buffer, offset, length)) result.push_back(enumConverter(bit));
    return result;
}
ByteVec readByteArray(const ByteVec& buffer, size_t& offset, size_t length);
// TODO: readIDOrX
// TODO: readIDSet
// TODO: readSoundEvent
// TODO: readChatType
// TODO: readChunkData ??
// TODO: readLightData ??
void writeVarInt(ByteVec& buffer, int value);
void writeVarLong(ByteVec& buffer, int64_t value);
// TODO: writeTextComponent
// TODO: writeJSONTextComponent
void writeIdentifier(ByteVec& buffer, const Identifier& identifier);
// TODO: writeEntityMetaData
// TODO: writeSlot
// TODO: writeHashedSlot
// TODO: writeNBT
// TODO: writePosition
// TODO: writeAngle
// TODO: writeUUID
void                       writeBitSet(ByteVec& buffer, const std::vector<uint64_t>& longs);
void                       writeFixedBitSet(ByteVec& buffer, const std::vector<bool>& bits, size_t length);
template <typename T, typename WriteFunc> void writeOptionalX(ByteVec& buffer, const T* value, const WriteFunc& writeFunc, const bool isPresent) {
    if (!isPresent || value == nullptr) return;
    writeFunc(buffer, *value);
}
template <typename T, typename WriteFunc>
void writeOptionalX(ByteVec& buffer, const T* value, const WriteFunc& writeFunc, const bool isPresent, const int length) {
    if (!isPresent || value == nullptr) return;
    writeFunc(buffer, *value, length);
}
template <typename T, typename WriteFunc> void writePrefixedOptionalX(ByteVec& buffer, const T* value, const WriteFunc& writeFunc) {
    const bool present = value != nullptr;
    writeBoolean(buffer, present);
    if (!present) return;
    writeFunc(buffer, *value);
}
template <typename T, typename WriteFunc> void writePrefixedOptionalX(ByteVec& buffer, const T* value, const WriteFunc& writeFunc, const int length) {
    const bool present = value != nullptr;
    writeBoolean(buffer, present);
    if (!present) return;
    writeFunc(buffer, *value, length);
}
template <typename T, typename WriteFunc> void writeArrayOfX(ByteVec& buffer, const std::vector<T>& values, const WriteFunc& writeFunc) {
    for (const auto& value : values) {
        writeFunc(buffer, value);
    }
}
template <typename T, typename WriteFunc> void writeArrayOfX(ByteVec& buffer, const std::vector<T>& values, const WriteFunc& writeFunc, int length) {
    for (const auto& value : values) {
        writeFunc(buffer, value, length);
    }
}
template <typename T, typename WriteFunc> void writePrefixedArrayOfX(ByteVec& buffer, const std::vector<T>& values, const WriteFunc& writeFunc) {
    writeVarInt(buffer, static_cast<int>(values.size()));
    writeArrayOfX(buffer, values, writeFunc);
}
template <typename T, typename WriteFunc> void writeXEnum(ByteVec& buffer, const T& value, const WriteFunc& writeFunc) {
    writeFunc(buffer, value);
}
template <typename T, typename WriteFunc> void writeXEnum(ByteVec& buffer, const T& value, const WriteFunc& writeFunc, const int length) {
    writeFunc(buffer, value, length);
}
void writeEnumSet(ByteVec& buffer, const std::vector<bool>& values);
void writeByteArray(ByteVec& buffer, const ByteVec& values);
// TODO: writeIDOrX
// TODO: writeIDSet
// TODO: writeSoundEvent
// TODO: writeChatType
// TODO: writeChunkData ??
// TODO: writeLightData ??

// Helper functions
inline bool isReadable(const ByteVec& buffer, const size_t& offset, const size_t& bytes) {
    if (offset + bytes > buffer.size()) throw PacketSerializationException("Buffer overflow: Tried reading beyond buffer size.");

    return true;
}
int countUTF16CodeUnits(const std::string& utf8);

class PacketBuffer {
    ByteVec buffer;
    size_t  offset;

  public:
    PacketBuffer() : offset(0) {};
    explicit PacketBuffer(const ByteVec& buffer) : buffer(buffer), offset(0) {};
    explicit PacketBuffer(ByteVec&& buffer) : buffer(std::move(buffer)), offset(0) {};
    PacketBuffer(const ByteVec& buffer, const int offset) : buffer(buffer), offset(offset) {};
    PacketBuffer(ByteVec&& buffer, const int offset) : buffer(std::move(buffer)), offset(offset) {};
    PacketBuffer(const PacketBuffer&) = default;
    PacketBuffer(PacketBuffer&&)      = default;
    ~PacketBuffer()                   = default;

    void clear() {
        buffer.clear();
        offset = 0;
    }
    void resize(const size_t size) { buffer.resize(size); }
    void reserve(const size_t size) { buffer.reserve(size); }
    void append(const ByteVec& data) { buffer.insert(buffer.end(), data.begin(), data.end()); }
    void append(const ByteVec&& data) { buffer.insert(buffer.end(), std::make_move_iterator(data.begin()), std::make_move_iterator(data.end())); }
    auto begin() { return buffer.begin(); }
    auto end() { return buffer.end(); }

    bool                  readBoolean() { return stratos::readBoolean(buffer, offset); }
    int8_t                readByte() { return stratos::readByte(buffer, offset); }
    uint8_t               readUnsignedByte() { return stratos::readUnsignedByte(buffer, offset); }
    short                 readShort() { return stratos::readShort(buffer, offset); }
    uint16_t              readUnsignedShort() { return stratos::readUnsignedShort(buffer, offset); }
    int                   readInt() { return stratos::readInt(buffer, offset); }
    int64_t               readLong() { return stratos::readLong(buffer, offset); }
    float                 readFloat() { return stratos::readFloat(buffer, offset); }
    double                readDouble() { return stratos::readDouble(buffer, offset); }
    std::string           readString(const int maxChars) { return stratos::readString(buffer, offset, maxChars); }
    std::string           readStringUTF16BE() { return stratos::readStringUTF16BE(buffer, offset); }
    int                   readVarInt() { return stratos::readVarInt(buffer, offset); }
    int64_t               readVarLong() { return stratos::readVarLong(buffer, offset); }
    std::vector<uint64_t> readBitSet() { return stratos::readBitSet(buffer, offset); }
    std::vector<bool>     readFixedBitSet(const size_t length) { return stratos::readFixedBitSet(buffer, offset, length); }
    // TODO: Read array of X, optional X, and so on get individual methods per type
    template <typename T, typename U, typename ReadFunc, typename EnumConverter> U readXEnum(const ReadFunc& readFunc, const EnumConverter& enumConverter) {
        return stratos::readXEnum<T, U>(buffer, offset, readFunc, enumConverter);
    }
    ByteVec readByteArray(const size_t length) { return stratos::readByteArray(buffer, offset, length); }

    void writeBoolean(const bool value) { stratos::writeBoolean(buffer, value); }
    void writeByte(const int8_t value) { stratos::writeByte(buffer, value); }
    void writeUnsignedByte(const uint8_t value) { stratos::writeUnsignedByte(buffer, value); }
    void writeShort(const short value) { stratos::writeShort(buffer, value); }
    void writeUnsignedShort(const uint16_t value) { stratos::writeUnsignedShort(buffer, value); }
    void writeInt(const int value) { stratos::writeInt(buffer, value); }
    void writeLong(const int64_t value) { stratos::writeLong(buffer, value); }
    void writeFloat(const float value) { stratos::writeFloat(buffer, value); }
    void writeDouble(const double value) { stratos::writeDouble(buffer, value); }
    void writeString(const std::string& value, const int maxChars) { stratos::writeString(buffer, value, maxChars); }
    void writeStringUTF16BE(const std::string& value) { stratos::writeStringUTF16BE(buffer, value); }
    void writeVarInt(int value) { stratos::writeVarInt(buffer, value); }
    void writeVarLong(int64_t value) { stratos::writeVarLong(buffer, value); }
    void writeBitSet(const std::vector<uint64_t>& longs) { stratos::writeBitSet(buffer, longs); }
    void writeFixedBitSet(const std::vector<bool>& bits, const size_t length) { stratos::writeFixedBitSet(buffer, bits, length); }
    // TODO: Write array of X, optional X, and so on get individual methods per type
    template <typename T, typename WriteFunc> void writeXEnum(const T& value, const WriteFunc& writeFunc) { stratos::writeXEnum<T>(buffer, value, writeFunc); }
    void                       writeByteArray(const ByteVec& values) { stratos::writeByteArray(buffer, values); }

    [[nodiscard]] const ByteVec& getBuffer() const { return buffer; }
    [[nodiscard]] size_t         getOffset() const { return offset; }
    [[nodiscard]] size_t         getSize() const { return buffer.size(); }
    [[nodiscard]] bool           isEmpty() const { return buffer.empty(); }
    [[nodiscard]] bool           isReadable() const { return offset < buffer.size(); }
    [[nodiscard]] bool           isReadable(const size_t& bytes) const { return offset + bytes < buffer.size(); }
};
} // namespace stratos

#endif
