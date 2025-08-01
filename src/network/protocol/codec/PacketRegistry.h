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

#ifndef PACKETREGISTRY_H
#define PACKETREGISTRY_H
#include "network/protocol/Packet.h"

#include <functional>

namespace stratos::network {
class Packet;
class PacketRegistry final {
public:
    PacketRegistry();

    static const PacketRegistry* instance();

    const Packet* create(const PacketKey& key);
    const PacketDefinition* getDefinition(const PacketKey& key) const {
        if (packets.contains(key)) {
            return packets.at(key);
        }
        return nullptr;
    }
private:
    std::unordered_map<PacketKey, const PacketDefinition*> packets;

    void setup();
    void registerPacket(const PacketKey& key, const PacketDefinition* definition);
};
} // namespace stratos::network

#endif //PACKETREGISTRY_H
