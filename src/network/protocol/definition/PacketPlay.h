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

#ifndef PACKETPLAY_H
#define PACKETPLAY_H
#include "math/Position.h"
#include "network/protocol/Packet.h"
#include "utils/Identifier.h"
#include "utils/Types.h"

#include <optional>
#include <vector>

namespace stratos::network {
class GameEventPacket final : public ClientboundPacket {//GameEventPacket> {
public:
    constexpr static int ID = 0x22;
    GameEvent event;
    float data;

    GameEventPacket() : ClientboundPacket(ID), event(), data(0) {}
    explicit GameEventPacket(const GameEvent event, const float data = 0.0f)
         : ClientboundPacket(ID), event(event), data(data){}
    CLIENTBOUND_PACKET_FOOTER(GameEventPacket)
};
class SynchronizePlayerPosition final : public ClientboundPacket {//SynchronizePlayerPosition> {
  public:
    constexpr static int ID = 0x41;
    int teleportId; // VarInt
    double x;
    double y;
    double z;
    double velocityX;
    double velocityY;
    double velocityZ;
    float yaw;
    float pitch;
    int flags;

    SynchronizePlayerPosition() : ClientboundPacket(ID), teleportId(), x(), y(), z(), velocityX(), velocityY(), velocityZ(), yaw(), pitch(), flags() {}
    SynchronizePlayerPosition(const int teleportId, const double x, const double y, const double z, const double velocityX, const double velocityY, const double velocityZ, const float yaw, const float pitch, const int flags = 0)
         : ClientboundPacket(ID), teleportId(teleportId), x(x), y(y), z(z), velocityX(velocityX), velocityY(velocityY), velocityZ(velocityZ), yaw(yaw), pitch(pitch), flags(flags) {}
    CLIENTBOUND_PACKET_FOOTER(SynchronizePlayerPosition)
};
class LoginPlay final : public ClientboundPacket {//LoginPlay> {
public:
    constexpr static int ID = 0x2B;
    int entityId; // int
    bool isHardcore;
    std::vector<utils::Identifier> dimensions; // prefixed array
    int maxPlayers; // VarInt
    int viewDistance; // VarInt
    int simulationDistance; // VarInt
    bool reducedDebugInfo;
    bool enableRespawnScreen;
    bool doLimitedCrafting;
    int dimensionType; // VarInt
    utils::Identifier dimensionName;
    long hashedSeed;
    uint8_t gamemode;
    int8_t previousGamemode;
    bool debug;
    bool flat;
    bool hasDeathLocation;
    std::optional<utils::Identifier> deathDimension; // optional utils::Identifier
    std::optional<math::Position> deathPosition; // optional position
    int portalCooldown; // VarInt
    int seaLevel; // VarInt
    bool                          enforcesSecureChat;

    LoginPlay()
         : ClientboundPacket(ID), entityId(0), isHardcore(false), maxPlayers(0), viewDistance(0), simulationDistance(0), reducedDebugInfo(false),
          enableRespawnScreen(false), doLimitedCrafting(false), dimensionType(0), dimensionName(utils::Identifier{"", ""}), hashedSeed(0), gamemode(0), previousGamemode(0), debug(false),
          flat(false), hasDeathLocation(false), portalCooldown(0), seaLevel(0), enforcesSecureChat(false) {}
    LoginPlay(const int entity_id, const bool is_hardcore, const std::vector<utils::Identifier> dimensions, const int max_players, const int view_distance, const int simulation_distance, const bool reduced_debug_info,
              bool const enable_respawn_screen, bool const do_limited_crafting, const int dimension_type, const utils::Identifier dimension_name, const long hashed_seed, const uint8_t gamemode, const int8_t previous_gamemode,
              const bool debug, const bool flat, const bool has_death_location, const std::optional<utils::Identifier> death_dimension, const std::optional<math::Position> death_position, const int portal_cooldown,
              const int sea_level, const bool enforces_secure_chat)
         : ClientboundPacket(ID), entityId(entity_id), isHardcore(is_hardcore), dimensions(dimensions), maxPlayers(max_players), viewDistance(view_distance),
          simulationDistance(simulation_distance), reducedDebugInfo(reduced_debug_info), enableRespawnScreen(enable_respawn_screen), doLimitedCrafting(do_limited_crafting),
          dimensionType(dimension_type), dimensionName(dimension_name), hashedSeed(hashed_seed), gamemode(gamemode), previousGamemode(previous_gamemode), debug(debug), flat(flat),
          hasDeathLocation(has_death_location), deathDimension(death_dimension), deathPosition(death_position), portalCooldown(portal_cooldown), seaLevel(sea_level),
          enforcesSecureChat(enforces_secure_chat) {}
    CLIENTBOUND_PACKET_FOOTER(LoginPlay)
};

class SetCenterChunk final : public ClientboundPacket {//SetCenterChunk> {
  public:
    constexpr static int ID = 0x57;
    int chunkX; // VarInt
    int chunkZ; // VarInt

    SetCenterChunk() : ClientboundPacket(ID), chunkX(0), chunkZ(0) {}
    SetCenterChunk(const int chunkX, const int chunkZ) : ClientboundPacket(ID), chunkX(chunkX), chunkZ(chunkZ) {}
    CLIENTBOUND_PACKET_FOOTER(SetCenterChunk)
};

class SetDefaultSpawnPosition final : public ClientboundPacket {//SetDefaultSpawnPosition> {
  public:
    constexpr static int ID = 0x5A;
    math::Position location;
    float angle;

    SetDefaultSpawnPosition() : ClientboundPacket(ID), location(), angle() {}
    SetDefaultSpawnPosition(const math::Position location, const float angle)
         : ClientboundPacket(ID), location(location), angle(angle) {}
    CLIENTBOUND_PACKET_FOOTER(SetDefaultSpawnPosition)
};

} // namespace stratos::network

#endif //PACKETPLAY_H
