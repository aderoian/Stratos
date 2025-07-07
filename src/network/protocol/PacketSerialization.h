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
#include "math/Position.h"
#include "nbt/io/NBTBuffer.h"
#include "utils/Identifier.h"
#include "utils/Types.h"

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

namespace stratos {
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

// Helper functions
inline bool isReadable(const ByteVec& buffer, const size_t& offset, const size_t& bytes) {
    if (offset + bytes > buffer.size()) throw PacketSerializationException("Buffer overflow: Tried reading beyond buffer size.");

    return true;
}

class PacketBuffer final : public nbt::NBTBuffer {
  public:
    PacketBuffer() = default;
    explicit PacketBuffer(const ByteVec& data) : NBTBuffer(data, 0) {}
    explicit PacketBuffer(ByteVec&& data) : NBTBuffer(std::move(data), 0) {}
    PacketBuffer(const ByteVec& data, const size_t offset) : NBTBuffer(data, offset) {}
    PacketBuffer(ByteVec&& data, const size_t offset) : NBTBuffer(std::move(data), offset) {}
    PacketBuffer(const PacketBuffer&) = delete;
    PacketBuffer& operator=(const PacketBuffer&) = delete;
    PacketBuffer(PacketBuffer&&) = default;
    PacketBuffer& operator=(PacketBuffer&&) = default;

    std::string           readStringUTF16BE();
    // TODO: readTextComponent
    // TODO: readJSONTextComponent
    stratos::utils::Identifier readIdentifier();
    // TODO: readEntityMetaData
    // TODO: readSlot
    // TODO: readHashedSlot
    // TODO: readNBT
    math::Position        readPosition();
    math::Angle           readAngle();
    UUID                  readUUID();
    template <typename T, typename ReadFunc>
    T readVarIntEnum(const ReadFunc& enumMapper) { return enumMapper(readVarInt()); }
    std::vector<uint8_t> readPrefixedByteArray();
    std::vector<LoginProperty> readLoginProperty();
    std::optional<std::string> readPrefixedOptionalString(int maxChars);
    std::vector<uint8_t> readInferredByteArray();
    ResourcePackHeader readResourcePackHeader();
    std::optional<std::vector<uint8_t>> readPrefixedOptionalInferredByteArray();
    std::optional<std::vector<uint8_t>> readPrefixedOptionalPrefixedByteArray();
    std::vector<ResourcePackHeader> readPrefixedResourcePackHeaderArray();

    void writeStringUTF16BE(const std::string& value);
    // TODO: writeTextComponent
    // TODO: writeJSONTextComponent
    void writeIdentifier(const utils::Identifier& identifier);
    // TODO: writeEntityMetaData
    // TODO: writeSlot
    // TODO: writeHashedSlot
    // TODO: writeNBT
    void writePosition(const math::Position& position);
    void writeAngle(const math::Angle& angle);
    void writeUUID(const UUID& uuid);
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
    void writePrefixedIdentifierArray(const std::vector<utils::Identifier>& identifiers);
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
