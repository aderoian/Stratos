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

#include "NetworkClient.h"

#include "nbt/CompoundTag.h"
#include "nbt/ListTag.h"
#include "nbt/NBT.h"
#include "nbt/PrimitiveTag.h"
#include "nbt/StringTag.h"
#include "network/Network.h"
#include "network/protocol/definition/PacketConfiguration.h"
#include "network/protocol/definition/PacketHandshake.h"
#include "network/protocol/definition/PacketLogin.h"
#include "network/protocol/definition/PacketPlay.h"
#include "network/protocol/handler/PacketHandshakeHandler.h"
#include "network/protocol/handler/PacketLoginHandler.h"
#include "network/protocol/handler/PacketStatusHandler.h"
#include "network/protocol/serialization/PacketBuffer.h"
#include "network/protocol/serialization/PacketSerialization.h"
#include "registry/Registries.h"
#include "Server.h"
#include "spdlog/logger.h"
#include "world/format/io/Region.h"

namespace stratos::network {
void NetworkSession::tick() {
    if (!isConnected()) return;

    // Empty received queue
    // TODO: Should we always empty or consume a fix amount per tick?
    processReceived();
}
void NetworkSession::beginConfiguration() const {
    // TODO: R&D the proper configuration process

    // Send Registries
    // TODO: Registry API

    // TODO: Dimension API (really part of the World API)
    const nbt::CompoundTag dimensionType{
        nbt::CompoundTag::CompoundElement{"has_skylight", nbt::ByteTag{true}},
        nbt::CompoundTag::CompoundElement{"has_ceiling", nbt::ByteTag{false}},
        nbt::CompoundTag::CompoundElement{"ultrawarm", nbt::ByteTag{false}},
        nbt::CompoundTag::CompoundElement{"natural", nbt::ByteTag{true}},
        nbt::CompoundTag::CompoundElement{"coordinate_scale", nbt::DoubleTag{1.0}},
        nbt::CompoundTag::CompoundElement{"bed_works", nbt::ByteTag{true}},
        nbt::CompoundTag::CompoundElement{"respawn_anchor_works", nbt::ByteTag{false}},
        nbt::CompoundTag::CompoundElement{"min_y", nbt::IntTag{-64}},
        nbt::CompoundTag::CompoundElement{"height", nbt::IntTag{384}},
        nbt::CompoundTag::CompoundElement{"logical_height", nbt::IntTag{384}},
        nbt::CompoundTag::CompoundElement{"infiniburn", nbt::StringTag{"#minecraft:infiniburn_overworld"}},
        nbt::CompoundTag::CompoundElement{"effects", nbt::StringTag{"minecraft:overworld"}},
        nbt::CompoundTag::CompoundElement{"ambient_light", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"piglin_safe", nbt::ByteTag{false}},
        nbt::CompoundTag::CompoundElement{"has_raids", nbt::ByteTag{false}},
        nbt::CompoundTag::CompoundElement{"monster_spawn_light_level", nbt::CompoundTag{nbt::CompoundTag::CompoundElement{"type", nbt::StringTag{"minecraft:uniform"}},
                                                                                        nbt::CompoundTag::CompoundElement{"max_inclusive", nbt::IntTag{7}},
                                                                                        nbt::CompoundTag::CompoundElement{"min_inclusive", nbt::IntTag{0}}}},
        nbt::CompoundTag::CompoundElement{"monster_spawn_block_light_limit", nbt::IntTag{0}}};
    const nbt::CompoundTag catVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:entity/cat/all_black"}}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag cowVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:entity/cow/temperate_cow"}}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag chickenVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:entity/chicken/temperate_chicken"}}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag frogVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:entity/frog/temperate_frog"}}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag paintingVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:earth"}}, nbt::CompoundTag::CompoundElement{"height", nbt::IntTag{2}},
        nbt::CompoundTag::CompoundElement{"width", nbt::IntTag{2}},nbt::CompoundTag::CompoundElement{"title", nbt::CompoundTag{
            nbt::CompoundTag::CompoundElement{"translate", nbt::StringTag{"painting.minecraft.earth.title"}},
            nbt::CompoundTag::CompoundElement{"color", nbt::StringTag{"yellow"}}
        }}
    };
    const nbt::CompoundTag pigVariant{
        nbt::CompoundTag::CompoundElement{"asset_id", nbt::StringTag{"minecraft:entity/pig/temperate_pig"}}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag wolfVariant{
        nbt::CompoundTag::CompoundElement{"assets", nbt::CompoundTag{
            nbt::CompoundTag::CompoundElement{"angry", nbt::StringTag{"minecraft:entity/wolf/wolf_ashen_angry"}},
            nbt::CompoundTag::CompoundElement{"tame", nbt::StringTag{"minecraft:entity/wolf/wolf_ashen_tame"}},
            nbt::CompoundTag::CompoundElement{"wild", nbt::StringTag{"minecraft:entity/wolf/wolf_ashen"}}
        }}, nbt::CompoundTag::CompoundElement{"spawn_conditions", nbt::ListTag{}}
    };
    const nbt::CompoundTag wolfSoundVariant{
        nbt::CompoundTag::CompoundElement{"ambient_sound", nbt::StringTag{"minecraft:entity.wolf_angry.ambient"}},
        nbt::CompoundTag::CompoundElement{"death_sound", nbt::StringTag{"minecraft:entity.wolf_angry.death"}},
        nbt::CompoundTag::CompoundElement{"growl_sound", nbt::StringTag{"minecraft:entity.wolf_angry.growl"}},
        nbt::CompoundTag::CompoundElement{"hurt_sound", nbt::StringTag{"minecraft:entity.wolf_angry.hurt"}},
        nbt::CompoundTag::CompoundElement{"pant_sound", nbt::StringTag{"minecraft:entity.wolf_angry.pant"}},
        nbt::CompoundTag::CompoundElement{"whine_sound", nbt::StringTag{"minecraft:entity.wolf_angry.whine"}}
    };

    const nbt::CompoundTag inFireDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"inFire"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag campfireDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"inFire"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag lightningDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"lightningBold"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag onFireDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"onFire"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag lavaDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"lava"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag hotFloorDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"hotFloor"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag inWallDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"inWall"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag crammingDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"cramming"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag drownDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"drown"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag starveDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"starve"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag cactusDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.1}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"cactus"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag fallDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"fall"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag enderPearlDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"fall"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag flyIntoWallDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"flyIntoWall"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag outOfWorldDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"outOfWorld"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };

    const nbt::CompoundTag genericDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"generic"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };

    const nbt::CompoundTag magicDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"magic"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag witherDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"wither"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag dragonBreathDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"dragonBreath"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag dryOutDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"dryOut"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag sweetBerryBushDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"sweetBerryBush"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag freezeDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"freeze"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag stalagmiteDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"stalagmite"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag outsideBorderDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"outsideBorder"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };
    const nbt::CompoundTag genericKillDamageEntry{
        nbt::CompoundTag::CompoundElement{"exhaustion", nbt::FloatTag{0.0}},
        nbt::CompoundTag::CompoundElement{"message_id", nbt::StringTag{"genericKill"}},
        nbt::CompoundTag::CompoundElement{"scaling", nbt::StringTag{"when_caused_by_living_non_player"}}
    };


    RegistryEntry dimensionTypeEntry{utils::Identifier{"minecraft", "overworld"}, std::make_optional(nbt::writeNetworkNBT(dimensionType))};
    RegistryEntry catVariantEntry{utils::Identifier{"minecraft", "cat/all_black"}, std::make_optional(nbt::writeNetworkNBT(catVariant))};
    RegistryEntry cowVariantEntry{utils::Identifier{"minecraft", "cow/temperate"}, std::make_optional(nbt::writeNetworkNBT(cowVariant))};
    RegistryEntry chickenVariantEntry{utils::Identifier{"minecraft", "chicken/temperate"}, std::make_optional(nbt::writeNetworkNBT(chickenVariant))};
    RegistryEntry frogVariantEntry{utils::Identifier{"minecraft", "frog/temperate"}, std::make_optional(nbt::writeNetworkNBT(frogVariant))};
    RegistryEntry paintingVariantEntry{utils::Identifier{"minecraft", "earth"}, std::make_optional(nbt::writeNetworkNBT(paintingVariant))};
    RegistryEntry pigVariantEntry{utils::Identifier{"minecraft", "pig/temperate"}, std::make_optional(nbt::writeNetworkNBT(pigVariant))};
    RegistryEntry wolfVariantEntry{utils::Identifier{"minecraft", "ashen"}, std::make_optional(nbt::writeNetworkNBT(wolfVariant))};
    RegistryEntry wolfSoundVariantEntry{utils::Identifier{"minecraft", "angry"}, std::make_optional(nbt::writeNetworkNBT(wolfSoundVariant))};

    send(new RegistryDataPacket(utils::Identifier{"minecraft", "dimension_type"}, std::vector{std::move(dimensionTypeEntry)}));
    send(registry::Registries::BIOMES()->createDynamicEntryPacket(utils::Identifier{"minecraft", "worldgen/biome"}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "cat_variant"}, std::vector{std::move(catVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "cow_variant"}, std::vector{std::move(cowVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "chicken_variant"}, std::vector{std::move(chickenVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "frog_variant"}, std::vector{std::move(frogVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "painting_variant"}, std::vector{std::move(paintingVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "pig_variant"}, std::vector{std::move(pigVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "wolf_variant"}, std::vector{std::move(wolfVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "wolf_sound_variant"}, std::vector{std::move(wolfSoundVariantEntry)}));
    send(new RegistryDataPacket(utils::Identifier{"minecraft", "damage_type"}, std::vector{
        RegistryEntry{utils::Identifier{"minecraft", "in_fire"}, std::make_optional(nbt::writeNetworkNBT(inFireDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "campfire"}, std::make_optional(nbt::writeNetworkNBT(campfireDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "lightning_bolt"}, std::make_optional(nbt::writeNetworkNBT(lightningDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "on_fire"}, std::make_optional(nbt::writeNetworkNBT(onFireDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "lava"}, std::make_optional(nbt::writeNetworkNBT(lavaDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "hot_floor"}, std::make_optional(nbt::writeNetworkNBT(hotFloorDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "in_wall"}, std::make_optional(nbt::writeNetworkNBT(inWallDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "cramming"}, std::make_optional(nbt::writeNetworkNBT(crammingDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "drown"}, std::make_optional(nbt::writeNetworkNBT(drownDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "starve"}, std::make_optional(nbt::writeNetworkNBT(starveDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "cactus"}, std::make_optional(nbt::writeNetworkNBT(cactusDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "fall"}, std::make_optional(nbt::writeNetworkNBT(fallDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "ender_pearl"}, std::make_optional(nbt::writeNetworkNBT(enderPearlDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "fly_into_wall"}, std::make_optional(nbt::writeNetworkNBT(flyIntoWallDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "out_of_world"}, std::make_optional(nbt::writeNetworkNBT(outOfWorldDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "generic"}, std::make_optional(nbt::writeNetworkNBT(genericDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "magic"}, std::make_optional(nbt::writeNetworkNBT(magicDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "wither"}, std::make_optional(nbt::writeNetworkNBT(witherDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "dragon_breath"}, std::make_optional(nbt::writeNetworkNBT(dragonBreathDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "dry_out"}, std::make_optional(nbt::writeNetworkNBT(dryOutDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "sweet_berry_bush"}, std::make_optional(nbt::writeNetworkNBT(sweetBerryBushDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "freeze"}, std::make_optional(nbt::writeNetworkNBT(freezeDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "stalagmite"}, std::make_optional(nbt::writeNetworkNBT(stalagmiteDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "outside_border"}, std::make_optional(nbt::writeNetworkNBT(outsideBorderDamageEntry))},
        RegistryEntry{utils::Identifier{"minecraft", "generic_kill"}, std::make_optional(nbt::writeNetworkNBT(genericKillDamageEntry))}
    }));
    send(new FinishConfiguration());
}
void NetworkSession::changeState(const ProtocolState newState) const {
    connection->changeState(newState);
}
void NetworkSession::loginPlayer() {
    send(new LoginPlay(
        0,
        false,
        std::vector{utils::Identifier{"minecraft", "overworld"}},
        networkManager->getServer()->getMaxPlayers(),
        12, // TODO: View distance from server.properties
        10, // TODO: Simulation distance from server.properties
        false,
        true,
        false,
        0, // TODO: Figure out what Dimension ID is
        utils::Identifier{"minecraft", "overworld"},
        0, // TODO: Hashed seed, should be generated by the server
        1,
        -1, // Previous gamemode, -1 means no previous gamemode
        false,
        false,
        false,
        std::nullopt,
        std::nullopt,
        0, // Portal cooldown
        63, // Sea level, default value
        true
        ));

    send(new SetRenderDistance(12));
    send(new SetDefaultSpawnPosition(math::Position{24, 100, 24}, 0)); // TODO: Spawn position should be determined by the server
    send(new SetCenterChunk(1, 1));
    send(new SynchronizePlayerPosition(0, 24, 100, 24, 0, 0, 0, 0, 0));
    send(new GameEventPacket(GameEvent::StartWaitingForChunks));

    Path          worldRegion = server->getServerDirectory() / "world" / "region";
    world::Region region(0, 0, worldRegion);

    for (int i = 0 ; i <= 2; ++i)
        for (int j = 0; j <= 2; ++j)
            if (const world::Chunk* neighbor = region.loadChunk(i, j)) send(new ChunkDataAndLight(i, j, ChunkData::fromChunk(neighbor), LightData::fromChunk(neighbor)));
}
void NetworkSession::processReceived() {
    while (true) {
        const ServerboundPacket* packet = connection->receivePacket();
        if (!packet) break; // No more packets to process
        if (!packet->accept(*packetHandler)) {
            networkManager->getLogger()->warn("Unhandled packet with ID {} from client {}:{}", packet->getId(), sessionId.ip, sessionId.port);
        }
        delete packet;
    }
}
const ServerboundPacket* NetworkConnection::receivePacket() {
    if (isDisconnected()) return nullptr;
    if (const ServerboundPacket* packet; receiveQueue.try_dequeue(packet)) return packet;
    return nullptr;
}
void NetworkConnection::sendPacket(const ClientboundPacket* packet) {
    if (isDisconnected()) return;
    sendQueue.enqueue(packet);
    if (bool expected = false; dirty.compare_exchange_strong(expected, true)) eventLoop->notifySend(socketFd);
}
int NetworkConnection::handleReceive() {
    const int received = flushReceive();
    if (received <= 0) return received; // Connection closed or error

    size_t offset = 0;
    while (!receiveBuf.empty()) {
        if (handleLegacyPing()) {
            // Legacy ping handled, continue to next iteration
            continue;
        }

        try {
            const int packetLength = readVarInt(receiveBuf, offset);
            if (packetLength <= 0 || packetLength > receiveBuf.size() - offset) {
                // Not enough data to read a full packet, wait for more data
                return received;
            }

            const int frameLength = offset + packetLength;
            int initLength = receiveBuf.size();

            PacketBuffer packetBuffer(packetLength);
            packetBuffer.insert(packetBuffer.begin(), std::make_move_iterator(receiveBuf.begin() + offset), std::make_move_iterator(receiveBuf.begin() + frameLength));
            receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + frameLength);
            ByteVec before = receiveBuf;
            assert(receiveBuf.size() == initLength - frameLength);
            try {
                const auto* packet = network->getPacketCodec().decode(packetBuffer, state, Serverbound, packetLength);
                if (!packet) {
                    // receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + offset + packetLength);
                    return received;
                }

                if (!packet->accept(*packetHandler))
                    receiveQueue.enqueue(dynamic_cast<const ServerboundPacket*>(packet)); // Enqueue the packet for further processing
                else delete packet;
            } catch (const PacketSerializationException& e) {
                logger->error("Failed to read packet from client {}:{}: {}", address, port, e.what());
            } catch (const std::exception& e) {
                logger->error("Encountered an exception when handing a packet for client {}:{}: {}", address, port, e.what());
            }

            // receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + offset + packetLength);
            assert(receiveBuf.size() == initLength - frameLength);
            assert(before == receiveBuf);
            offset = 0; // Reset offset for the next packet
        } catch (const PacketSerializationException& ignored) { // Failed to read packet length
            // Not enough data to read a packet, wait for more data
            break;
        } catch (const std::exception& e) {
            logger->error("Failed to read packet from client {}:{}: {}", address, port, e.what());
        }
    }
    return received;
}
void NetworkConnection::changeState(const ProtocolState newState) {
    state = newState;
    switch (state) {
    case Handshaking:
        packetHandler = std::make_unique<PacketHandshakeHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Status:
        packetHandler = std::make_unique<PacketStatusHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Login:
        packetHandler = std::make_unique<PacketLoginHandler>(this);
        receiveBuf.reserve(512);
        break;
    case Configuration:
        packetHandler = std::make_unique<PacketHandler>(); // Configuration state does not handle packets directly
        receiveBuf.reserve(1024);
        break;
    case Play:
        packetHandler = std::make_unique<PacketHandler>(); // Network connection does not handle play packets directly
        receiveBuf.reserve(4096);
    }
}
bool NetworkConnection::disconnect() {
    if (bool expected = false; !disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) return false;
    return true;
}
bool NetworkConnection::disconnect(const std::string& reason) {
    if (bool expected = false; !disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) return false;
    if (state == Login)
        sendPacket(new LoginDisconnect(reason.data()));
    return true;
}
bool NetworkConnection::close() {
    if (TCPConnection::close()) {
        bool expected = false;
        disconnected.compare_exchange_strong(expected, true, std::memory_order_acq_rel);

        // Clear queues and buffers
        receiveBuf.clear();
        const ServerboundPacket* receiveConsumer;
        while (receiveQueue.try_dequeue(receiveConsumer)) {
        }
        const ClientboundPacket* sendConsumer;
        while (sendQueue.try_dequeue(sendConsumer)) {
        }
        return true;
    }
    return false;
}
void NetworkConnection::updateSessionInfo(SessionInfo&& info) {
    if (sessionInfo) {
        sessionInfo->username = std::move(info.username);
        sessionInfo->uuid     = std::move(info.uuid);
    } else {
        sessionInfo = std::make_unique<SessionInfo>(std::move(info));
    }
}
void NetworkConnection::createNetworkSession() {
    const std::shared_ptr<NetworkConnection> self = eventLoop->getConnection(socketFd);
    if (!self) { // Edge case, should never happen
        logger->critical("Cannot create network session for client {}:{}, failed to get instance of self", address, port);
        disconnect("Internal server error.");
    }
    network->createSession(self);
}
int NetworkConnection::flushReceive () {
    int totalReceived = 0;
    ByteVec segment;
    segment.resize(1050);
    while (true) {
        const int received = receive(1050, segment);
        if (received == 0) return 0; // Connection closed
        if (received < 0) break;

        totalReceived += received;
        if (encryptionEnabled) {
            try {
                ByteVec decrypted = aesDecryptCFB8(clientSecret, clientSecret, segment);
                if (decrypted.empty()) {
                    logger->error("Failed to decrypt received data, disconnecting client {}:{}", address, port);
                    disconnect("Decryption failed");
                    return -1; // Decryption failed
                }
                receiveBuf.insert(receiveBuf.end(), decrypted.begin(), decrypted.begin() + received);
            } catch (std::runtime_error & e) {
                logger->error("Decryption error for client {}:{}: {}", address, port, e.what());
                disconnect("Decryption error");
                return -1; // Decryption error
            }
        } else {
            receiveBuf.insert(receiveBuf.end(), segment.begin(), segment.begin() + received);
        }
        segment.clear();
    }
    return totalReceived > 0 ? totalReceived : -1;
}
int NetworkConnection::flushSend() {
    ByteVec                            sendBuffer;
    const ClientboundPacket* packet;
    while (sendQueue.try_dequeue(packet)) {
        if (!packet) continue; // Skip empty packets
        PacketBuffer pkBuf;
        network->getPacketCodec().encode(pkBuf, packet);

        PacketBuffer framedBuf;
        framedBuf.writeVarInt(static_cast<int>(pkBuf.getSize()));
        framedBuf.append(pkBuf.getBuffer());
        if (encryptionEnabled) {
            ByteVec encrypted = aesEncryptCFB8(clientSecret, clientSecret, framedBuf.getBuffer());
            sendBuffer.insert(sendBuffer.end(), std::make_move_iterator(encrypted.begin()), std::make_move_iterator(encrypted.end()));
        } else {
            sendBuffer.insert(sendBuffer.end(), framedBuf.begin(), framedBuf.end());
        }
        delete packet;
    }

    if (sendBuffer.empty()) return 0;
    return send(sendBuffer, sendBuffer.size(), 0);
}
bool NetworkConnection::handleLegacyPing() {
    if (state != Handshaking) return false;
    try {
        size_t legacyPingOffset = 0;
        if (const uint8_t id = readUnsignedByte(receiveBuf, legacyPingOffset); id == LegacyServerListPing::ID) {
            PacketBuffer buffer(receiveBuf, legacyPingOffset);
            LegacyServerListPing packet;
            packet.decrypt(buffer);

            packet.accept(*packetHandler); // Handle legacy ping packet
            const size_t newOffset = buffer.getOffset();
            receiveBuf.erase(receiveBuf.begin(), receiveBuf.begin() + newOffset);
            return true; // Legacy ping handled
        }
    } catch (PacketSerializationException & ignored) {}
    return false; // No legacy ping found
}
} // stratos::network