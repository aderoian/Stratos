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

#ifndef PACKETCODEC_H
#define PACKETCODEC_H
#include "network/protocol/Packet.h"

#include <unordered_map>

namespace spdlog {
class logger;
}
namespace stratos::network {
class PacketBuffer;

class PacketCodec {
public:
    explicit PacketCodec(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger)) {};
    ~PacketCodec() = default;
    PacketCodec(const PacketCodec&) = delete;
    PacketCodec& operator=(const PacketCodec&) = delete;
    PacketCodec(PacketCodec&&) = default;
    PacketCodec& operator=(PacketCodec&&) = default;

    void registerPacket(const PacketDefinition* definition);
    void registerPacket(const PacketKey& key, const PacketDefinition* definition);
    void unregisterPacket(const PacketKey& key);

    [[nodiscard]] const PacketDefinition* getPacket(const PacketKey& key) const;
    [[nodiscard]] bool hasPacket(const PacketKey& key) const;
    [[nodiscard]] const std::unordered_map<PacketKey, const PacketDefinition*>& getPacketDefinitions() const;

    [[nodiscard]] const Packet* create(const PacketKey& key) const;
    const Packet* decode(const PacketBuffer& buffer, ProtocolState state, PacketDirection direction, int length) const;
    void encode(PacketBuffer& buffer, const Packet* packet) const;
private:
    std::shared_ptr<spdlog::logger> logger;
    std::unordered_map<PacketKey, const PacketDefinition*> packetDefinitions;
};
}

#endif //PACKETCODEC_H
