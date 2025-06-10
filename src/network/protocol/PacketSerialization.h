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
#include "math/Angle.h"
#include "math/Ints.h"
#include "math/Position.h"
#include "utils/Types.h"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace stratos {
struct Identifier;
using ByteVec = std::vector<unsigned char>;
using UUID = std::array<uint8_t, 16>;

class PacketSerializationException final : public std::logic_error {
  public:
    explicit PacketSerializationException(const char* message) : logic_error(message) {};
    explicit PacketSerializationException(const std::string& message) : logic_error(message) {};
};

int constexpr SEGMENT_BITS = 0x7F;
int constexpr CONTINUE_BIT = 0x80;

// Generic serialization functions
bool                  readBoolean(const ByteVec& buffer, size_t& offset);
int8_t                readByte(const ByteVec& buffer, size_t& offset);
uint8_t               readUnsignedByte(const ByteVec& buffer, size_t& offset);
math::int12_t         readInt12(const ByteVec& buffer, size_t& offset);
short                 readShort(const ByteVec& buffer, size_t& offset);
uint16_t              readUnsignedShort(const ByteVec& buffer, size_t& offset);
math::int26_t         readInt26(const ByteVec& buffer, size_t& offset);
int                   readInt(const ByteVec& buffer, size_t& offset);
int64_t               readLong(const ByteVec& buffer, size_t& offset);
float                 readFloat(const ByteVec& buffer, size_t& offset);
double                readDouble(const ByteVec& buffer, size_t& offset);
std::string           readString(const ByteVec& buffer, size_t& offset, int maxChars);
std::string           readStringUTF16BE(const ByteVec& buffer, size_t& offset);
int                   readVarInt(const ByteVec& buffer, size_t& offset);
int64_t               readVarLong(const ByteVec& buffer, size_t& offset);
std::vector<uint64_t> readBitSet(const ByteVec& buffer, size_t& offset);
std::vector<bool>     readFixedBitSet(const ByteVec& buffer, size_t& offset, size_t length);
ByteVec               readByteArray(const ByteVec& buffer, size_t& offset, size_t length);

void writeBoolean(ByteVec& buffer, bool value);
void writeByte(ByteVec& buffer, int8_t value);
void writeUnsignedByte(ByteVec& buffer, uint8_t value);
void writeInt12(ByteVec& buffer, math::int12_t value);
void writeShort(ByteVec& buffer, short value);
void writeUnsignedShort(ByteVec& buffer, uint16_t value);
void writeInt26(ByteVec& buffer, math::int26_t value);
void writeInt(ByteVec& buffer, int value);
void writeLong(ByteVec& buffer, int64_t value);
void writeFloat(ByteVec& buffer, float value);
void writeDouble(ByteVec& buffer, double value);
void writeString(ByteVec& buffer, const std::string& value, int maxChars);
void writeStringUTF16BE(ByteVec& buffer, const std::string& value);
void writeVarInt(ByteVec& buffer, int value);
void writeVarLong(ByteVec& buffer, int64_t value);
void writeBitSet(ByteVec& buffer, const std::vector<uint64_t>& longs);
void writeFixedBitSet(ByteVec& buffer, const std::vector<bool>& bits, size_t length);
void writeByteArray(ByteVec& buffer, const ByteVec& values);

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
    // TODO: readTextComponent
    // TODO: readJSONTextComponent
    Identifier            readIdentifier();
    // TODO: readEntityMetaData
    // TODO: readSlot
    // TODO: readHashedSlot
    // TODO: readNBT
    math::Position        readPosition();
    math::Angle           readAngle();
    UUID                  readUUID();
    std::vector<uint64_t> readBitSet() { return stratos::readBitSet(buffer, offset); }
    std::vector<bool>     readFixedBitSet(const size_t length) { return stratos::readFixedBitSet(buffer, offset, length); }
    template <typename T, typename ReadFunc>
    T readVarIntEnum(const ReadFunc& enumMapper) { return enumMapper(stratos::readVarInt(buffer, offset)); }
    ByteVec readByteArray(const size_t length) { return stratos::readByteArray(buffer, offset, length); }
    std::vector<uint8_t> readPrefixedByteArray();
    std::vector<LoginProperty> readLoginProperty();
    std::optional<std::string> readPrefixedOptionalString(int maxChars);
    std::vector<uint8_t> readInferredByteArray();
    ResourcePackHeader readResourcePackHeader();
    std::optional<std::vector<uint8_t>> readPrefixedOptionalInferredByteArray();
    std::optional<std::vector<uint8_t>> readPrefixedOptionalPrefixedByteArray();
    std::vector<ResourcePackHeader> readPrefixedResourcePackHeaderArray();

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
    // TODO: writeTextComponent
    // TODO: writeJSONTextComponent
    void writeIdentifier(const Identifier& identifier);
    // TODO: writeEntityMetaData
    // TODO: writeSlot
    // TODO: writeHashedSlot
    // TODO: writeNBT
    void writePosition(const math::Position& position);
    void writeAngle(const math::Angle& angle);
    void writeUUID(const UUID& uuid);
    void writeBitSet(const std::vector<uint64_t>& longs) { stratos::writeBitSet(buffer, longs); }
    void writeFixedBitSet(const std::vector<bool>& bits, const size_t length) { stratos::writeFixedBitSet(buffer, bits, length); }
    void writeByteArray(const ByteVec& values) { stratos::writeByteArray(buffer, values); }
    void writePrefixedByteArray(const std::vector<uint8_t>& bytes);
    void writeLoginProperty(const std::vector<LoginProperty>& properties);
    void writeResourcePackHeader(const ResourcePackHeader& header);
    void writeRegistryEntry(const RegistryEntry& entry);
    void writeRegistryTagData(const RegistryTagData& data);
    void writeReportDetail(const ReportDetail& detail);
    void writeServerLink(const ServerLink& link);
    void writePrefixedOptionalString(const std::optional<std::string>& str, int maxChars);
    void writePrefixedOptionalUUID(const std::optional<UUID>& uuid);
    void writePrefixedOptionalByteArray(const std::optional<std::vector<uint8_t>>& bytes);
    void writePrefixedOptionalPrefixedByteArray(const std::optional<std::vector<uint8_t>>& bytes);
    void writePrefixedResourcePackHeaderArray(const std::vector<ResourcePackHeader>& headers);
    void writePrefixedRegistryEntryArray(const std::vector<RegistryEntry>& entries);
    void writePrefixedRegistryTagDataArray(const std::vector<RegistryTagData>& data);
    void writePrefixedIdentifierArray(const std::vector<Identifier>& identifiers);
    void writePrefixedReportDetailArray(const std::vector<ReportDetail>& details);
    void writePrefixedServerLinkArray(const std::vector<ServerLink>& serverLinks);

    [[nodiscard]] const ByteVec& getBuffer() const { return buffer; }
    [[nodiscard]] size_t         getOffset() const { return offset; }
    [[nodiscard]] size_t         getSize() const { return buffer.size(); }
    [[nodiscard]] bool           isEmpty() const { return buffer.empty(); }
    [[nodiscard]] bool           isReadable() const { return offset < buffer.size(); }
    [[nodiscard]] bool           isReadable(const size_t& bytes) const { return offset + bytes < buffer.size(); }
};
} // namespace stratos

#endif
