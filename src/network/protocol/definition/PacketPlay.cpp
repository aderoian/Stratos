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

#include "PacketPlay.h"

#include "network/protocol/serialization/PacketBuffer.h"

namespace stratos::network {
void GameEventPacket::encrypt(PacketBuffer& buffer) const {
    buffer.writeUnsignedByte(static_cast<uint8_t>(event));
    buffer.writeFloat(data);
}
void SynchronizePlayerPosition::encrypt(PacketBuffer& buffer) const {
    buffer.writeVarInt(teleportId);
    buffer.writeDouble(x);
    buffer.writeDouble(y);
    buffer.writeDouble(z);
    buffer.writeDouble(velocityX);
    buffer.writeDouble(velocityY);
    buffer.writeDouble(velocityZ);
    buffer.writeFloat(yaw);
    buffer.writeFloat(pitch);
    buffer.writeInt(flags);
}
void LoginPlay::encrypt(PacketBuffer& buffer) const {
    buffer.writeInt(entityId);
    buffer.writeBoolean(isHardcore);
    buffer.writePrefixedIdentifierArray(dimensions);
    buffer.writeVarInt(maxPlayers);
    buffer.writeVarInt(viewDistance);
    buffer.writeVarInt(simulationDistance);
    buffer.writeBoolean(reducedDebugInfo);
    buffer.writeBoolean(enableRespawnScreen);
    buffer.writeBoolean(doLimitedCrafting);
    buffer.writeVarInt(dimensionType);
    buffer.writeIdentifier(dimensionName);
    buffer.writeLong(hashedSeed);
    buffer.writeByte(gamemode);
    buffer.writeByte(previousGamemode);
    buffer.writeBoolean(debug);
    buffer.writeBoolean(flat);
    buffer.writeBoolean(hasDeathLocation);
    if (hasDeathLocation) {
        buffer.writeIdentifier(deathDimension.value());
        buffer.writePosition(deathPosition.value());
    }
    buffer.writeVarInt(portalCooldown);
    buffer.writeVarInt(seaLevel);
    buffer.writeBoolean(enforcesSecureChat);
}
void SetCenterChunk::encrypt(PacketBuffer& buffer) const {
    buffer.writeVarInt(chunkX);
    buffer.writeVarInt(chunkZ);
}
void SetDefaultSpawnPosition::encrypt(PacketBuffer& buffer) const {
    buffer.writePosition(location);
    buffer.writeFloat(angle);
}
} // namespace stratos::network