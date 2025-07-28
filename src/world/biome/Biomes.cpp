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

#include "Biomes.h"

#include "Biome.h"
#include "registry/Registries.h"
#include "utils/Identifier.h"

#define REGISTER_BIOME(codeName, name) \
    const Biome* Biomes::codeName() { \
        static const Biome* biome = registerBiome(utils::Identifier("minecraft", name), new Biome()); \
        return biome; \
    }

namespace stratos::world {

Biome* registerBiome(const utils::Identifier& id, Biome* biome) {
    registry::Registries::BIOMES()->registerEntry({{"minecraft", "biome"}, id}, biome);
    return biome;
}

// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

REGISTER_BIOME(BADLANDS, "badlands")
REGISTER_BIOME(BAMBOO_JUNGLE, "bamboo_jungle")
REGISTER_BIOME(BASALT_DELTAS, "basalt_deltas")
REGISTER_BIOME(BEACH, "beach")
REGISTER_BIOME(BIRCH_FOREST, "birch_forest")
REGISTER_BIOME(CHERRY_GROVE, "cherry_grove")
REGISTER_BIOME(COLD_OCEAN, "cold_ocean")
REGISTER_BIOME(CRIMSON_FOREST, "crimson_forest")
REGISTER_BIOME(DARK_FOREST, "dark_forest")
REGISTER_BIOME(DEEP_COLD_OCEAN, "deep_cold_ocean")
REGISTER_BIOME(DEEP_DARK, "deep_dark")
REGISTER_BIOME(DEEP_FROZEN_OCEAN, "deep_frozen_ocean")
REGISTER_BIOME(DEEP_LUKEWARM_OCEAN, "deep_lukewarm_ocean")
REGISTER_BIOME(DEEP_OCEAN, "deep_ocean")
REGISTER_BIOME(DESERT, "desert")
REGISTER_BIOME(DRIPSTONE_CAVES, "dripstone_caves")
REGISTER_BIOME(END_BARRENS, "end_barrens")
REGISTER_BIOME(END_HIGHLANDS, "end_highlands")
REGISTER_BIOME(END_MIDLANDS, "end_midlands")
REGISTER_BIOME(ERODED_BADLANDS, "eroded_badlands")
REGISTER_BIOME(FLOWER_FOREST, "flower_forest")
REGISTER_BIOME(FOREST, "forest")
REGISTER_BIOME(FROZEN_OCEAN, "frozen_ocean")
REGISTER_BIOME(FROZEN_PEAKS, "frozen_peaks")
REGISTER_BIOME(FROZEN_RIVER, "frozen_river")
REGISTER_BIOME(GROVE, "grove")
REGISTER_BIOME(ICE_SPIKES, "ice_spikes")
REGISTER_BIOME(JAGGED_PEAKS, "jagged_peaks")
REGISTER_BIOME(JUNGLE, "jungle")
REGISTER_BIOME(LUKEWARM_OCEAN, "lukewarm_ocean")
REGISTER_BIOME(LUSH_CAVES, "lush_caves")
REGISTER_BIOME(MANGROVE_SWAMP, "mangrove_swamp")
REGISTER_BIOME(MEADOW, "meadow")
REGISTER_BIOME(MUSHROOM_FIELDS, "mushroom_fields")
REGISTER_BIOME(NETHER_WASTES, "nether_wastes")
REGISTER_BIOME(OCEAN, "ocean")
REGISTER_BIOME(OLD_GROWTH_BIRCH_FOREST, "old_growth_birch_forest")
REGISTER_BIOME(OLD_GROWTH_PINE_TAIGA, "old_growth_pine_taiga")
REGISTER_BIOME(OLD_GROWTH_SPRUCE_TAIGA, "old_growth_spruce_taiga")
REGISTER_BIOME(PALE_GARDEN, "pale_garden")
REGISTER_BIOME(PLAINS, "plains")
REGISTER_BIOME(RIVER, "river")
REGISTER_BIOME(SAVANNA, "savanna")
REGISTER_BIOME(SAVANNA_PLATEAU, "savanna_plateau")
REGISTER_BIOME(SMALL_END_ISLANDS, "small_end_islands")
REGISTER_BIOME(SNOWY_BEACH, "snowy_beach")
REGISTER_BIOME(SNOWY_PLAINS, "snowy_plains")
REGISTER_BIOME(SNOWY_SLOPES, "snowy_slopes")
REGISTER_BIOME(SNOWY_TAIGA, "snowy_taiga")
REGISTER_BIOME(SOUL_SAND_VALLEY, "soul_sand_valley")
REGISTER_BIOME(SPARSE_JUNGLE, "sparse_jungle")
REGISTER_BIOME(STONY_PEAKS, "stony_peaks")
REGISTER_BIOME(STONY_SHORE, "stony_shore")
REGISTER_BIOME(SUNFLOWER_PLAINS, "sunflower_plains")
REGISTER_BIOME(SWAMP, "swamp")
REGISTER_BIOME(TAIGA, "taiga")
REGISTER_BIOME(THE_END, "the_end")
REGISTER_BIOME(THE_VOID, "the_void")
REGISTER_BIOME(WARM_OCEAN, "warm_ocean")
REGISTER_BIOME(WARPED_FOREST, "warped_forest")
REGISTER_BIOME(WINDSWEPT_FOREST, "windswept_forest")
REGISTER_BIOME(WINDSWEPT_GRAVELLY_HILLS, "windswept_gravelly_hills")
REGISTER_BIOME(WINDSWEPT_HILLS, "windswept_hills")
REGISTER_BIOME(WINDSWEPT_SAVANNA, "windswept_savanna")
REGISTER_BIOME(WOODED_BADLANDS, "wooded_badlands")

void Biomes::registerBiomes() {
    BADLANDS();
    BAMBOO_JUNGLE();
    BASALT_DELTAS();
    BEACH();
    BIRCH_FOREST();
    CHERRY_GROVE();
    COLD_OCEAN();
    CRIMSON_FOREST();
    DARK_FOREST();
    DEEP_COLD_OCEAN();
    DEEP_DARK();
    DEEP_FROZEN_OCEAN();
    DEEP_LUKEWARM_OCEAN();
    DEEP_OCEAN();
    DESERT();
    DRIPSTONE_CAVES();
    END_BARRENS();
    END_HIGHLANDS();
    END_MIDLANDS();
    ERODED_BADLANDS();
    FLOWER_FOREST();
    FOREST();
    FROZEN_OCEAN();
    FROZEN_PEAKS();
    FROZEN_RIVER();
    GROVE();
    ICE_SPIKES();
    JAGGED_PEAKS();
    JUNGLE();
    LUKEWARM_OCEAN();
    LUSH_CAVES();
    MANGROVE_SWAMP();
    MEADOW();
    MUSHROOM_FIELDS();
    NETHER_WASTES();
    OCEAN();
    OLD_GROWTH_BIRCH_FOREST();
    OLD_GROWTH_PINE_TAIGA();
    OLD_GROWTH_SPRUCE_TAIGA();
    PALE_GARDEN();
    PLAINS();
    RIVER();
    SAVANNA();
    SAVANNA_PLATEAU();
    SMALL_END_ISLANDS();
    SNOWY_BEACH();
    SNOWY_PLAINS();
    SNOWY_SLOPES();
    SNOWY_TAIGA();
    SOUL_SAND_VALLEY();
    SPARSE_JUNGLE();
    STONY_PEAKS();
    STONY_SHORE();
    SUNFLOWER_PLAINS();
    SWAMP();
    TAIGA();
    THE_END();
    THE_VOID();
    WARM_OCEAN();
    WARPED_FOREST();
    WINDSWEPT_FOREST();
    WINDSWEPT_GRAVELLY_HILLS();
    WINDSWEPT_HILLS();
    WINDSWEPT_SAVANNA();
    WOODED_BADLANDS();
}

} // namespace stratos::world
