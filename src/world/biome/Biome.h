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

#ifndef BIOME_H
#define BIOME_H
#include "registry/Registry.h"

#include <algorithm>

namespace stratos::nbt {
class CompoundTag;
}
namespace stratos::world {
enum class BiomeTemperatureModifier {
    None,
    Frozen
};

struct BiomeWeather {
    bool hasPrecipitation;
    float temperature;
    BiomeTemperatureModifier temperatureModifier = BiomeTemperatureModifier::None;
    float downFall;

    BiomeWeather(const bool precipitation = true, const float temperature = 0.5f, const BiomeTemperatureModifier modifier = BiomeTemperatureModifier::None, const float fall = 0.4f)
        : hasPrecipitation(precipitation), temperature(temperature), temperatureModifier(modifier), downFall(fall) {}

    class Builder {
    public:
        Builder() = default;
        Builder& setPrecipitation(bool hasPrecipitation);
        Builder& setTemperature(float temperature);
        Builder& setTemperatureModifier(BiomeTemperatureModifier temperatureModifier);
        Builder& setDownFall(float downFall);
        BiomeWeather build() const;
    private:
        bool hasPrecipitation = true;
        float temperature = 0.5f;
        BiomeTemperatureModifier temperatureModifier = BiomeTemperatureModifier::None;
        float downFall = 0.4f;
    };
};

struct BiomeEffects {
    int fogColor;
    int waterColor;
    int waterFogColor;
    int skyColor;
    float musicVolume = 1.0f;
    // TODO: add optional fields

    BiomeEffects(const int fog, const int water, const int waterFog, const int sky, const float musicVol = 1.0f)
        : fogColor(fog), waterColor(water), waterFogColor(waterFog), skyColor(sky), musicVolume(musicVol) {}

    class Builder {
    public:
        Builder() = default;
        Builder& setFogColor(int fogColor);
        Builder& setWaterColor(int waterColor);
        Builder& setWaterFogColor(int waterFogColor);
        Builder& setSkyColor(int skyColor);
        Builder& setMusicVolume(float musicVolume);
        BiomeEffects build() const;
    private:
        int fogColor = 0;
        int waterColor = 0;
        int waterFogColor = 0;
        int skyColor = 0;
        float musicVolume = 1.0f;
    };
};

class Biome final : public registry::DynamicRegistryElement {
public:
    Biome(BiomeWeather weather, BiomeEffects effects) : weather(std::move(weather)), effects(std::move(effects)) {}

    [[nodiscard]] const BiomeWeather& getWeather() const { return weather; }
    [[nodiscard]] const BiomeEffects& getEffects() const { return effects; }

    [[nodiscard]] nbt::CompoundTag toNetworkNBT() const override;
private:
    BiomeWeather weather;
    BiomeEffects effects;
};

} // namespace stratos::world

#endif //BIOME_H
