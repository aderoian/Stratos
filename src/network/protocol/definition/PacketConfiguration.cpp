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

#include "PacketConfiguration.h"

#include "network/protocol/serialization/PacketBuffer.h"
#include "network/protocol/serialization/PacketSerialization.h"

namespace stratos::network {
void ConfigurationClientInformation::decrypt(const PacketBuffer& buffer) {
    locale = buffer.readString(16);
    viewDistance = buffer.readByte();
    chatMode = buffer.readVarIntEnum<ChatMode>([](const int& value) -> ChatMode {
        switch (value) {
        case 0:
            return ChatMode::Enabled;
        case 1:
            return ChatMode::CommandsOnly;
        case 2:
            return ChatMode::Hidden;
        default:
            throw PacketSerializationException("Unknown chat mode value: " + std::to_string(value));
        }
    });
    chatColors = buffer.readBoolean();
    skinParts = buffer.readUnsignedByte();
    mainHand = buffer.readVarIntEnum<Hand>([](const int& value) -> Hand {
        switch (value) {
        case 0:
            return Hand::Left;
        case 1:
            return Hand::Right;
        default:
            throw PacketSerializationException("Unknown hand value: " + std::to_string(value));
        }
    });
    enableTextFiltering = buffer.readBoolean();
    allowServerListing = buffer.readBoolean();
    particleStatus = buffer.readVarIntEnum<ParticleStatus>([](const int& value) -> ParticleStatus {
        switch (value) {
        case 0:
            return ParticleStatus::All;
        case 1:
            return ParticleStatus::Decreased;
        case 2:
            return ParticleStatus::Minimal;
        default:
            throw PacketSerializationException("Unknown particle status value: " + std::to_string(value));
        }
    });
}
void ConfigurationCookieResponse::decrypt(const PacketBuffer& buffer) {
    key = buffer.readIdentifier();
    value = buffer.readPrefixedOptionalPrefixedByteArray();
}
void ConfigurationServerPluginMessage::decrypt(const PacketBuffer& buffer) {
    channel = buffer.readIdentifier();
    data    = buffer.readInferredByteArray();
}
void AcknowledgeFinishConfiguration::decrypt(const PacketBuffer& buffer) {}
void ConfigurationServerboundKeepAlive::decrypt(const PacketBuffer& buffer) {
    id = buffer.readLong();
}
void ConfigurationPong::decrypt(const PacketBuffer& buffer) {
    id = buffer.readInt();
}
void ConfigurationResourcePackResponse::decrypt(const PacketBuffer& buffer) {
    uuid = buffer.readUUID();
    result = buffer.readVarIntEnum<ResourcePackResult>([](const int& value) -> ResourcePackResult {
        switch (value) {
        case 0:
            return ResourcePackResult::SuccessfullyDownloaded;
        case 1:
            return ResourcePackResult::Declined;
        case 2:
            return ResourcePackResult::FailedDownload;
        case 3:
            return ResourcePackResult::Accepted;
        case 4:
            return ResourcePackResult::Downloaded;
        case 5:
            return ResourcePackResult::InvalidURL;
        case 6:
            return ResourcePackResult::FailedReload;
        case 7:
            return ResourcePackResult::Discarded;
        default:
            throw PacketSerializationException("Unknown resource pack result value: " + std::to_string(value));
        }
    });
}
void ServerboundKnownPacks::decrypt(const PacketBuffer& buffer) {
    knownPacks = buffer.readPrefixedResourcePackHeaderArray();
}
void ConfigurationCookieRequest::encrypt(PacketBuffer& buffer) const {
    buffer.writeIdentifier(key);
}
void ConfigurationClientboundPluginMessage::encrypt(PacketBuffer& buffer) const {
    buffer.writeIdentifier(channel);
    buffer.writeByteArray(data);
}
void ConfigurationDisconnect::encrypt(PacketBuffer& buffer) const {
    buffer.writeString(reason, 32767);
}
void FinishConfiguration::encrypt(PacketBuffer& buffer) const {}
void ConfigurationClientboundKeepAlive::encrypt(PacketBuffer& buffer) const {
    buffer.writeLong(id);
}
void ConfigurationPing::encrypt(PacketBuffer& buffer) const {
    buffer.writeInt(id);
}
void ResetChat::encrypt(PacketBuffer& buffer) const {}
void RegistryDataPacket::encrypt(PacketBuffer& buffer) const {
    buffer.writeIdentifier(registryKey);
    buffer.writePrefixedRegistryEntryArray(entries);
}
void ConfigurationRemoveRemoveResourcePack::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedOptionalUUID(uuid);
}
void ConfigurationAddResourcePack::encrypt(PacketBuffer& buffer) const {
    buffer.writeUUID(uuid);
    buffer.writeString(url, 32767);
    buffer.writeString(hash, 40);
    buffer.writeBoolean(forced);
    buffer.writePrefixedOptionalString(prompt, 32767);
}
void ConfigurationStoreCookie::encrypt(PacketBuffer& buffer) const {
    buffer.writeIdentifier(key);
    buffer.writePrefixedByteArray(value);
}
void ConfigurationTransfer::encrypt(PacketBuffer& buffer) const {
    buffer.writeString(host, 255);
    buffer.writeVarInt(port);
}
void FeatureFlags::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedIdentifierArray(features);
}
void ConfigurationUpdateTags::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedRegistryTagDataArray(tags);
}
void ClientboundKnownPacks::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedResourcePackHeaderArray(knownPackets);
}
void ConfigurationCustomReportDetails::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedReportDetailArray(details);
}
void ConfigurationServerLinks::encrypt(PacketBuffer& buffer) const {
    buffer.writePrefixedServerLinkArray(links);
}
} // namespace stratos::network