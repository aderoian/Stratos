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

#include "Biome.h"

#include "block/Blocks.h"
#include "magic_enum.hpp"
#include "nbt/CompoundTag.h"
#include "nbt/PrimitiveTag.h"
#include "nbt/StringTag.h"
#include "utils/StringUtils.h"

namespace stratos::world {
BiomeWeather::Builder& BiomeWeather::Builder::setPrecipitation(const bool hasPrecipitation) {
    this->hasPrecipitation = hasPrecipitation;
    return *this;
}
BiomeWeather::Builder& BiomeWeather::Builder::setTemperature(float temperature) {
    this->temperature = temperature;
    return *this;
}
BiomeWeather::Builder& BiomeWeather::Builder::setTemperatureModifier(const BiomeTemperatureModifier temperatureModifier) {
    this->temperatureModifier = temperatureModifier;
    return *this;
}
BiomeWeather::Builder& BiomeWeather::Builder::setDownFall(const float downFall) {
    this->downFall = downFall;
    return *this;
}
BiomeWeather BiomeWeather::Builder::build() const {
    return {hasPrecipitation, temperature, temperatureModifier, downFall};
}
BiomeEffects::Builder& BiomeEffects::Builder::setFogColor(const int fogColor) {
    this->fogColor = fogColor;
    return *this;
}
BiomeEffects::Builder& BiomeEffects::Builder::setWaterColor(const int waterColor) {
    this->waterColor = waterColor;
    return *this;
}
BiomeEffects::Builder& BiomeEffects::Builder::setWaterFogColor(const int waterFogColor) {
    this->waterFogColor = waterFogColor;
    return *this;
}
BiomeEffects::Builder& BiomeEffects::Builder::setSkyColor(const int skyColor) {
    this->skyColor = skyColor;
    return *this;
}
BiomeEffects::Builder& BiomeEffects::Builder::setMusicVolume(const float musicVolume) {
    this->musicVolume = musicVolume;
    return *this;
}
BiomeEffects BiomeEffects::Builder::build() const {
    return {fogColor, waterColor, waterFogColor, skyColor, musicVolume};
}
nbt::CompoundTag Biome::toNetworkNBT() const {
    return nbt::CompoundTag{
        nbt::CompoundTag::CompoundElement{"has_precipitation", nbt::ByteTag{weather.hasPrecipitation}},
            nbt::CompoundTag::CompoundElement{"temperature", nbt::FloatTag{weather.temperature}},
            nbt::CompoundTag::CompoundElement{"temperature_modifier", nbt::StringTag{toLower(std::string(magic_enum::enum_name<BiomeTemperatureModifier>(weather.temperatureModifier)))}},
            nbt::CompoundTag::CompoundElement{"downfall", nbt::FloatTag{weather.downFall}},
            nbt::CompoundTag::CompoundElement{"effects", nbt::CompoundTag{
                nbt::CompoundTag::CompoundElement{"fog_color", nbt::IntTag{effects.fogColor}},
                nbt::CompoundTag::CompoundElement{"water_color", nbt::IntTag{effects.waterColor}},
                nbt::CompoundTag::CompoundElement {"water_fog_color", nbt::IntTag{effects.waterFogColor}},
                nbt::CompoundTag::CompoundElement{"sky_color", nbt::IntTag{effects.skyColor}},
                nbt::CompoundTag::CompoundElement{"music_volume", nbt::FloatTag{effects.musicVolume}}}}};
}
} // namespace stratos::world