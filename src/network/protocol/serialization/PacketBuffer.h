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

#ifndef PACKETBUFFER_H
#define PACKETBUFFER_H
#include "math/Angle.h"
#include "math/Position.h"
#include "nbt/io/NBTBuffer.h"
#include "utils/Identifier.h"
#include "utils/Types.h"
#include "utils/UUID.h"

namespace stratos::network {

class PacketBuffer final : public nbt::NBTBuffer {
  public:
    PacketBuffer() = default;
    explicit PacketBuffer(const int size) : NBTBuffer(size) {}
    explicit PacketBuffer(const ByteVec& data) : NBTBuffer(data, 0) {}
    explicit PacketBuffer(ByteVec&& data) : NBTBuffer(std::move(data), 0) {}
    PacketBuffer(const ByteVec& data, const size_t offset) : NBTBuffer(data, offset) {}
    PacketBuffer(ByteVec&& data, const size_t offset) : NBTBuffer(std::move(data), offset) {}
    PacketBuffer(const PacketBuffer&) = delete;
    PacketBuffer& operator=(const PacketBuffer&) = delete;
    PacketBuffer(PacketBuffer&&) = default;
    PacketBuffer& operator=(PacketBuffer&&) = default;

    std::string           readStringUTF16BE() const;
    // TODO: readTextComponent
    // TODO: readJSONTextComponent
    utils::Identifier readIdentifier() const;
    // TODO: readEntityMetaData
    // TODO: readSlot
    // TODO: readHashedSlot
    math::Position        readPosition() const;
    math::Angle           readAngle() const;
    UUID                  readUUID() const;
    template <typename T, typename ReadFunc>
    T readVarIntEnum(const ReadFunc& enumMapper) const { return enumMapper(readVarInt()); }
    std::vector<uint8_t> readPrefixedByteArray() const;
    std::vector<int8_t> readPrefixedSignedByteArray() const;
    std::vector<int64_t> readPrefixedLongArray() const;
    std::vector<LoginProperty> readLoginProperty() const;
    std::optional<std::string> readPrefixedOptionalString(int maxChars) const;
    std::vector<uint8_t> readInferredByteArray() const;
    ResourcePackHeader readResourcePackHeader() const;
    std::optional<std::vector<uint8_t>> readPrefixedOptionalInferredByteArray() const;
    std::optional<std::vector<uint8_t>> readPrefixedOptionalPrefixedByteArray() const;
    std::vector<ResourcePackHeader> readPrefixedResourcePackHeaderArray() const;

    void writeStringUTF16BE(const std::string& value);
    // TODO: writeTextComponent
    // TODO: writeJSONTextComponent
    void writeIdentifier(const utils::Identifier& identifier);
    // TODO: writeEntityMetaData
    // TODO: writeSlot
    // TODO: writeHashedSlot
    void writePosition(const math::Position& position);
    void writeAngle(const math::Angle& angle);
    void writeUUID(const UUID& uuid);
    void writePrefixedByteArray(const std::vector<uint8_t>& bytes);
    void writePrefixedSignedByteArray(const std::vector<int8_t>& bytes);
    void writePrefixedLongArray(const std::vector<int64_t>& longs);
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
    [[nodiscard]] size_t         getSize() const { return buffer.size(); }
    [[nodiscard]] bool           isEmpty() const { return buffer.empty(); }
};

} // namespace stratos::network

#endif //PACKETBUFFER_H
