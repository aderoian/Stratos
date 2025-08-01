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

#include "PacketCodec.h"

#include "network/protocol/serialization/PacketBuffer.h"
void stratos::network::PacketCodec::registerPacket(const PacketDefinition* definition) {
    registerPacket({definition->state, definition->direction, definition->id}, definition);
}
void stratos::network::PacketCodec::registerPacket(const PacketKey& key, const PacketDefinition* definition) {
    packetDefinitions[key] = definition;
}
void stratos::network::PacketCodec::unregisterPacket(const PacketKey& key) {
    packetDefinitions.erase(key);
}
const stratos::network::PacketDefinition* stratos::network::PacketCodec::getPacket(const PacketKey& key) const {
    return packetDefinitions.contains(key) ? packetDefinitions.at(key) : nullptr;
}
bool stratos::network::PacketCodec::hasPacket(const PacketKey& key) const {
    return packetDefinitions.contains(key);
}
const std::unordered_map<stratos::network::PacketKey, const stratos::network::PacketDefinition*>& stratos::network::PacketCodec::getPacketDefinitions() const {
    return packetDefinitions;
}
const stratos::network::Packet* stratos::network::PacketCodec::create(const PacketKey& key) const {
    return packetDefinitions.contains(key) ? packetDefinitions.at(key)->factory() : nullptr;
}
const stratos::network::Packet* stratos::network::PacketCodec::decode(const PacketBuffer& buffer, const ProtocolState state, const PacketDirection direction) const {
    const PacketDefinition* definition = getPacket({state, direction, buffer.readVarInt()});
    if (!definition)
        return nullptr; // No packet definition found for the given key

    auto* packet = const_cast<Packet*>(definition->factory());
    if (!packet)
        return nullptr;

    try {
        packet->decrypt(buffer);
    } catch (const std::exception& e) {
        delete packet;
        throw;
    }

    return packet;
}
void stratos::network::PacketCodec::encode(PacketBuffer& buffer, const Packet* packet) const {
    buffer.writeVarInt(packet->getId());
    packet->encrypt(buffer);
}