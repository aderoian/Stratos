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

#include "PacketBuffer.h"
#include "PacketSerialization.h"

#include <codecvt>
#include <locale>

namespace stratos::network {
std::string PacketBuffer::readStringUTF16BE() const {
    if (offset + 2 > buffer.size()) throw std::out_of_range("StringUTF16BE: not enough bytes for length");
    const uint16_t length = static_cast<uint16_t>(buffer[offset++]) << 8 | static_cast<uint16_t>(buffer[offset++]);
    if (const size_t byteLength = length * 2; offset + byteLength > buffer.size()) throw PacketSerializationException("StringUTF16BE: not enough bytes for string content");
    std::u16string utf16;
    utf16.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        const char16_t ch = static_cast<char16_t>(buffer[offset++]) << 8 | static_cast<char16_t>(buffer[offset++]);
        utf16.push_back(ch);
    }
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(utf16);
}
utils::Identifier PacketBuffer::readIdentifier() const {
    std::string  rawIdentifier = readString(32767);
    const size_t colonPos      = rawIdentifier.find(':');
    if (colonPos == std::string::npos) throw PacketSerializationException("Identifier: missing namespace separator ':'");
    return {
        rawIdentifier.substr(0, colonPos), // namespace
        rawIdentifier.substr(colonPos + 1) // name
    };
}
math::Position PacketBuffer::readPosition() const {
    const int64_t  rawPosition = readLong();
    math::Position position;
    position.x = static_cast<int32_t>(rawPosition >> 38);
    position.y = static_cast<int32_t>(rawPosition << 52 >> 52);
    position.z = static_cast<int32_t>(rawPosition << 26 >> 38);
    return position;
}
math::Angle PacketBuffer::readAngle() const {
    return readUnsignedByte();
}
UUID PacketBuffer::readUUID() const {
    checkRead(16);
    UUID uuid;
    std::copy(buffer.begin() + offset, buffer.begin() + offset + 16, uuid.begin());
    offset += 16;
    return uuid;
}
std::vector<uint8_t> PacketBuffer::readPrefixedByteArray() const {
    return readByteArray(readVarInt());
}
std::vector<int8_t>  PacketBuffer::readPrefixedSignedByteArray() const {
    std::vector<int8_t> result(readVarInt(), 0);
    for (int8_t& i : result)
        i = readByte();
    return result;
}
std::vector<int64_t> PacketBuffer::readPrefixedLongArray() const {
    std::vector<int64_t> result(readVarInt(), 0);
    for (int64_t & i : result)
        i = readLong();
    return result;
}
std::vector<LoginProperty> PacketBuffer::readLoginProperty() const {
    const int length = readVarInt();
    if (length < 0 || length > 16)
        throw PacketSerializationException("LoginProperty: invalid length " + std::to_string(length));
    std::vector<LoginProperty> properties;
    properties.resize(length);
    for (int i = 0; i < length; ++i)
        properties[i] = {readString(16), readString(32767), readPrefixedOptionalString(1024)};
    return properties;
}
std::optional<std::string> PacketBuffer::readPrefixedOptionalString(const int maxChars) const {
    return readBoolean() ? std::make_optional(readString(maxChars)) : std::nullopt;
}
std::vector<uint8_t> PacketBuffer::readInferredByteArray() const {
    std::vector<uint8_t> result;
    while (offset < buffer.size()) result.push_back(readByte());
    return result;
}
ResourcePackHeader         PacketBuffer::readResourcePackHeader() const {
    return {readString(32767), readString(32767), readString(32767)};
}
std::optional<std::vector<uint8_t>> PacketBuffer::readPrefixedOptionalInferredByteArray() const {
    return readBoolean() ? std::make_optional(readInferredByteArray()) : std::nullopt;
}
std::optional<std::vector<uint8_t>> PacketBuffer::readPrefixedOptionalPrefixedByteArray() const {
    return readBoolean() ? std::make_optional(readPrefixedByteArray()) : std::nullopt;
}
std::vector<ResourcePackHeader> PacketBuffer::readPrefixedResourcePackHeaderArray() const {
    const int                       length = readVarInt();
    std::vector<ResourcePackHeader> headers;
    headers.reserve(length);
    for (int i = 0; i < length; ++i) headers.push_back(readResourcePackHeader());
    return headers;
}
void PacketBuffer::writeStringUTF16BE(const std::string& value) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    const std::u16string                                              utf16  = convert.from_bytes(value);
    const auto                                                        length = static_cast<uint16_t>(utf16.size());
    buffer.push_back(length >> 8 & 0xFF); // big-endian
    buffer.push_back(length & 0xFF);
    for (const char16_t& ch : utf16) {
        buffer.push_back(ch >> 8 & 0xFF); // high byte
        buffer.push_back(ch & 0xFF);      // low byte
    }
}
void PacketBuffer::writeIdentifier(const utils::Identifier& identifier) {
    const std::string fullIdent = identifier.namespaceName + ":" + identifier.name;
    writeString(fullIdent, 32767);
}
void PacketBuffer::writePosition(const math::Position& position) {
    writeLong((static_cast<int64_t>(position.x) & 0x3FFFFFFLL) << 38 | (static_cast<int64_t>(position.z) & 0x3FFFFFFLL) << 12 | static_cast<int64_t>(position.y) & 0xFFFL);
}
void PacketBuffer::writeAngle(const math::Angle& angle) {
    writeUnsignedByte(angle);
}
void PacketBuffer::writeUUID(const UUID& uuid) {
    for (const auto& byte : uuid) buffer.push_back(byte);
}
void PacketBuffer::writePrefixedByteArray(const std::vector<uint8_t>& bytes) {
    writeVarInt(static_cast<int>(bytes.size()));
    writeByteArray(bytes);
}
void PacketBuffer::writePrefixedSignedByteArray(const std::vector<int8_t>& bytes) {
    writeVarInt(static_cast<int>(bytes.size()));
    for (const int8_t& i : bytes) writeByte(i);
}
void PacketBuffer::writePrefixedLongArray(const std::vector<int64_t>& longs) {
    writeVarInt(static_cast<int>(longs.size()));
    for (const int64_t& i : longs) writeLong(i);
}
void PacketBuffer::writeLoginProperty(const std::vector<LoginProperty>& properties) {
    writeVarInt(static_cast<int>(properties.size()));
    for (const auto& [name, value, signature] : properties) {
        writeString(name, 16);
        writeString(value, 32767);
        writePrefixedOptionalString(signature, 1024);
    }
}
void PacketBuffer::writeResourcePackHeader(const ResourcePackHeader& header) {
    writeString(header.packNamespace, 32767);
    writeString(header.id, 32767);
    writeString(header.version, 32767);
}
void PacketBuffer::writeRegistryEntry(const RegistryEntry& entry) {
    writeIdentifier(entry.id);
    writeBoolean(entry.data.has_value());
    if (entry.data.has_value()) writeByteArray(entry.data.value());
}
void PacketBuffer::writeRegistryTagData(const RegistryTagData& data) {
    writeIdentifier(data.registryKey);
    writeVarInt(static_cast<int>(data.entries.size()));
    for (const auto& [key, id] : data.entries) {
        writeIdentifier(key);
        writeVarInt(id);
    }
}
void PacketBuffer::writeReportDetail(const ReportDetail& detail) {
    writeString(detail.title, 128);
    writeString(detail.description, 4096);
}
void PacketBuffer::writeServerLink(const ServerLink& link) {
    link.isDefault ? writeVarInt(static_cast<int>(link.defaultLabel)) : writeString(link.customLabel, 32767);
    writeString(link.url, 32767);
}
void PacketBuffer::writePrefixedOptionalString(const std::optional<std::string>& str, const int maxChars) {
    if (str) {
        writeBoolean(true);
        writeString(*str, maxChars);
    } else {
        writeBoolean(false);
    }
}
void PacketBuffer::writePrefixedOptionalUUID(const std::optional<UUID>& uuid) {
    writeBoolean(uuid.has_value());
    if (uuid.has_value()) writeUUID(uuid.value());
}
void PacketBuffer::writePrefixedOptionalByteArray(const std::optional<std::vector<uint8_t>>& bytes) {
    if (bytes) {
        writeBoolean(true);
        writeByteArray(*bytes);
    } else {
        writeBoolean(false);
    }
}
void PacketBuffer::writePrefixedOptionalPrefixedByteArray(const std::optional<std::vector<uint8_t>>& bytes) {
    if (bytes) {
        writeBoolean(true);
        writePrefixedByteArray(*bytes);
    } else {
        writeBoolean(false);
    }
}
void PacketBuffer::writePrefixedResourcePackHeaderArray(const std::vector<ResourcePackHeader>& headers) {
    writeVarInt(static_cast<int>(headers.size()));
    for (const auto& header : headers) writeResourcePackHeader(header);
}
void PacketBuffer::writePrefixedRegistryEntryArray(const std::vector<RegistryEntry>& entries) {
    writeVarInt(static_cast<int>(entries.size()));
    for (const auto& entry : entries) writeRegistryEntry(entry);
}
void PacketBuffer::writePrefixedRegistryTagDataArray(const std::vector<RegistryTagData>& data) {
    writeVarInt(static_cast<int>(data.size()));
    for (const auto& entry : data) {
        writeRegistryTagData(entry);
    }
}
void PacketBuffer::writePrefixedIdentifierArray(const std::vector<utils::Identifier>& identifiers) {
    writeVarInt(static_cast<int>(identifiers.size()));
    for (const auto& identifier : identifiers) writeIdentifier(identifier);
}
void PacketBuffer::writePrefixedReportDetailArray(const std::vector<ReportDetail>& details) {
    writeVarInt(static_cast<int>(details.size()));
    for (const auto& detail : details) writeReportDetail(detail);
}
void PacketBuffer::writePrefixedServerLinkArray(const std::vector<ServerLink>& serverLinks) {
    writeVarInt(static_cast<int>(serverLinks.size()));
    for (const auto& link : serverLinks) writeServerLink(link);
}
} // namespace stratos::network