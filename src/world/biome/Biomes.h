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

#ifndef BIOMES_H
#define BIOMES_H

namespace stratos::utils {
struct Identifier;
}
namespace stratos::world {
class Biome;
Biome* registerBiome(const utils::Identifier& id, Biome* biome);

class Biomes {
public:
    // AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

    static const Biome* BADLANDS();
    static const Biome* BAMBOO_JUNGLE();
    static const Biome* BASALT_DELTAS();
    static const Biome* BEACH();
    static const Biome* BIRCH_FOREST();
    static const Biome* CHERRY_GROVE();
    static const Biome* COLD_OCEAN();
    static const Biome* CRIMSON_FOREST();
    static const Biome* DARK_FOREST();
    static const Biome* DEEP_COLD_OCEAN();
    static const Biome* DEEP_DARK();
    static const Biome* DEEP_FROZEN_OCEAN();
    static const Biome* DEEP_LUKEWARM_OCEAN();
    static const Biome* DEEP_OCEAN();
    static const Biome* DESERT();
    static const Biome* DRIPSTONE_CAVES();
    static const Biome* END_BARRENS();
    static const Biome* END_HIGHLANDS();
    static const Biome* END_MIDLANDS();
    static const Biome* ERODED_BADLANDS();
    static const Biome* FLOWER_FOREST();
    static const Biome* FOREST();
    static const Biome* FROZEN_OCEAN();
    static const Biome* FROZEN_PEAKS();
    static const Biome* FROZEN_RIVER();
    static const Biome* GROVE();
    static const Biome* ICE_SPIKES();
    static const Biome* JAGGED_PEAKS();
    static const Biome* JUNGLE();
    static const Biome* LUKEWARM_OCEAN();
    static const Biome* LUSH_CAVES();
    static const Biome* MANGROVE_SWAMP();
    static const Biome* MEADOW();
    static const Biome* MUSHROOM_FIELDS();
    static const Biome* NETHER_WASTES();
    static const Biome* OCEAN();
    static const Biome* OLD_GROWTH_BIRCH_FOREST();
    static const Biome* OLD_GROWTH_PINE_TAIGA();
    static const Biome* OLD_GROWTH_SPRUCE_TAIGA();
    static const Biome* PALE_GARDEN();
    static const Biome* PLAINS();
    static const Biome* RIVER();
    static const Biome* SAVANNA();
    static const Biome* SAVANNA_PLATEAU();
    static const Biome* SMALL_END_ISLANDS();
    static const Biome* SNOWY_BEACH();
    static const Biome* SNOWY_PLAINS();
    static const Biome* SNOWY_SLOPES();
    static const Biome* SNOWY_TAIGA();
    static const Biome* SOUL_SAND_VALLEY();
    static const Biome* SPARSE_JUNGLE();
    static const Biome* STONY_PEAKS();
    static const Biome* STONY_SHORE();
    static const Biome* SUNFLOWER_PLAINS();
    static const Biome* SWAMP();
    static const Biome* TAIGA();
    static const Biome* THE_END();
    static const Biome* THE_VOID();
    static const Biome* WARM_OCEAN();
    static const Biome* WARPED_FOREST();
    static const Biome* WINDSWEPT_FOREST();
    static const Biome* WINDSWEPT_GRAVELLY_HILLS();
    static const Biome* WINDSWEPT_HILLS();
    static const Biome* WINDSWEPT_SAVANNA();
    static const Biome* WOODED_BADLANDS();

    static void registerBiomes();
};
} // namespace stratos::world

#endif // BIOMES_H
