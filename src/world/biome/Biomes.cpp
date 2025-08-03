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

namespace stratos::world {

Biome* registerBiome(const utils::Identifier& id, Biome* biome) {
    registry::Registries::BIOMES()->registerEntry({{"minecraft", "biome"}, id}, biome);
    return biome;
}

// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

const Biome* Biomes::BADLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "badlands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::BAMBOO_JUNGLE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "bamboo_jungle"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.95).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7842047).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::BASALT_DELTAS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "basalt_deltas"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(6840176).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::BEACH() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "beach"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::BIRCH_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "birch_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.6).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.6).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8037887).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::CHERRY_GROVE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "cherry_grove"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(6141935).setWaterFogColor(6141935).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::COLD_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "cold_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4020182).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::CRIMSON_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "crimson_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(3343107).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DARK_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "dark_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7972607).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DEEP_COLD_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "deep_cold_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4020182).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DEEP_DARK() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "deep_dark"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DEEP_FROZEN_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "deep_frozen_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::Frozen).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(3750089).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DEEP_LUKEWARM_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "deep_lukewarm_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4566514).setWaterFogColor(267827).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DEEP_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "deep_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DESERT() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "desert"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::DRIPSTONE_CAVES() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "dripstone_caves"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::END_BARRENS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "end_barrens"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(10518688).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(0).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::END_HIGHLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "end_highlands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(10518688).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(0).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::END_MIDLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "end_midlands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(10518688).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(0).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::ERODED_BADLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "eroded_badlands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::FLOWER_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "flower_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7972607).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7972607).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::FROZEN_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "frozen_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.0).setTemperatureModifier(BiomeTemperatureModifier::Frozen).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(3750089).setWaterFogColor(329011).setSkyColor(8364543).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::FROZEN_PEAKS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "frozen_peaks"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(-0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8756735).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::FROZEN_RIVER() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "frozen_river"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(3750089).setWaterFogColor(329011).setSkyColor(8364543).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::GROVE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "grove"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(-0.2).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8495359).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::ICE_SPIKES() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "ice_spikes"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8364543).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::JAGGED_PEAKS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "jagged_peaks"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(-0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8756735).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::JUNGLE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "jungle"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.95).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7842047).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::LUKEWARM_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "lukewarm_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4566514).setWaterFogColor(267827).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::LUSH_CAVES() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "lush_caves"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::MANGROVE_SWAMP() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "mangrove_swamp"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(3832426).setWaterFogColor(5077600).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::MEADOW() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "meadow"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(937679).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::MUSHROOM_FIELDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "mushroom_fields"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.9).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(1.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7842047).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::NETHER_WASTES() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "nether_wastes"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(3344392).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::OLD_GROWTH_BIRCH_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "old_growth_birch_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.6).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.6).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8037887).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::OLD_GROWTH_PINE_TAIGA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "old_growth_pine_taiga"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.3).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8168447).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::OLD_GROWTH_SPRUCE_TAIGA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "old_growth_spruce_taiga"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.25).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233983).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::PALE_GARDEN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "pale_garden"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.7).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(8484720).setWaterColor(7768221).setWaterFogColor(5597568).setSkyColor(12171705).setMusicVolume(0.0).build()));
    return biome;
}

const Biome* Biomes::PLAINS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "plains"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::RIVER() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "river"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SAVANNA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "savanna"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SAVANNA_PLATEAU() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "savanna_plateau"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SMALL_END_ISLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "small_end_islands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(10518688).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(0).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SNOWY_BEACH() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "snowy_beach"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.05).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4020182).setWaterFogColor(329011).setSkyColor(8364543).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SNOWY_PLAINS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "snowy_plains"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8364543).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SNOWY_SLOPES() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "snowy_slopes"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(-0.3).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8560639).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SNOWY_TAIGA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "snowy_taiga"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(-0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4020182).setWaterFogColor(329011).setSkyColor(8625919).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SOUL_SAND_VALLEY() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "soul_sand_valley"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(1787717).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SPARSE_JUNGLE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "sparse_jungle"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.95).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7842047).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::STONY_PEAKS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "stony_peaks"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(1.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7776511).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::STONY_SHORE() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "stony_shore"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.2).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233727).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SUNFLOWER_PLAINS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "sunflower_plains"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.4).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::SWAMP() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "swamp"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.8).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.9).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(6388580).setWaterFogColor(2302743).setSkyColor(7907327).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::TAIGA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "taiga"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.25).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.8).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233983).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::THE_END() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "the_end"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(10518688).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(0).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::THE_VOID() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "the_void"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WARM_OCEAN() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "warm_ocean"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.5).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.5).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4445678).setWaterFogColor(270131).setSkyColor(8103167).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WARPED_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "warped_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(1705242).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WINDSWEPT_FOREST() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "windswept_forest"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.2).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233727).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WINDSWEPT_GRAVELLY_HILLS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "windswept_gravelly_hills"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.2).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233727).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WINDSWEPT_HILLS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "windswept_hills"), new Biome(BiomeWeather::Builder().setPrecipitation(true).setTemperature(0.2).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.3).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(8233727).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WINDSWEPT_SAVANNA() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "windswept_savanna"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}

const Biome* Biomes::WOODED_BADLANDS() {
    static const Biome* biome = registerBiome(utils::Identifier("minecraft", "wooded_badlands"), new Biome(BiomeWeather::Builder().setPrecipitation(false).setTemperature(2.0).setTemperatureModifier(BiomeTemperatureModifier::None).setDownFall(0.0).build(), BiomeEffects::Builder().setFogColor(12638463).setWaterColor(4159204).setWaterFogColor(329011).setSkyColor(7254527).setMusicVolume(1.0).build()));
    return biome;
}


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
