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

#include "Palette.h"

#include "block/Block.h"
#include "nbt/CompoundTag.h"
#include "nbt/ListTag.h"
#include "nbt/StringTag.h"
#include "registry/Registries.h"
#include "utils/MathUtils.h"

namespace stratos::world {
PalettedContainer<const block::BlockState*>::DataProvider<const block::BlockState*> BlockStateDataFactory(const int bits, const utils::IndexedIterable<const block::BlockState*>* idList) {
    if (bits == 0) return PalettedContainer<const block::BlockState*>::DataProvider{createSingularPalette<const block::BlockState*>, bits};
    if (bits <= 8) return PalettedContainer<const block::BlockState*>::DataProvider{createArrayPalette<const block::BlockState*>, bits > 4 ? bits : 4};
    return PalettedContainer<const block::BlockState*>::DataProvider{createIdListPalette<const block::BlockState*>, utils::ceilLog2(idList->size())};
}
PalettedContainer<const Biome*>::DataProvider<const Biome*> biomeDataFactory(const int bits, const utils::IndexedIterable<const Biome*>* idList) {
    if (bits == 0) return PalettedContainer<const Biome*>::DataProvider{createSingularPalette<const Biome*>, bits};
    if (bits < 4) return PalettedContainer<const Biome*>::DataProvider{createArrayPalette<const Biome*>, bits};
    return PalettedContainer<const Biome*>::DataProvider{createIdListPalette<const Biome*>, utils::ceilLog2(idList->size())};
}
std::vector<const block::BlockState*> readBlockStatePalette(nbt::CompoundTag& tag) {
    std::vector<const block::BlockState*> result;
    for (auto& palette = tag["palette"].as<nbt::ListTag>(); auto& entry : palette) {
        if (entry.getType() != nbt::TagType::Compound) throw std::runtime_error("Invalid palette entry type, expected CompoundTag");

        auto&               compound = entry.as<nbt::CompoundTag>();
        const block::Block* block    = registry::Registries::BLOCKS()->get(utils::Identifier::of(compound["Name"].as<nbt::StringTag>().get()));

        if (compound.hasKey("Properties", nbt::TagType::Compound)) {
            size_t index = 0;
            for (const auto& [name, value] : compound["Properties"].as<nbt::CompoundTag>())
                index ^= std::hash<std::string>()(name) ^ std::hash<std::string>()(value.as<nbt::StringTag>().get()) << 1;
            result.emplace_back(block->getStateManager()->getStateMap().at(index));
        } else {
            result.emplace_back(block->getStateManager()->getStates()[0]);
        }
    }
    return result;
}
std::vector<const Biome*> readBiomePalette(nbt::CompoundTag& tag) {
    auto& palette = tag["palette"].as<nbt::ListTag>();
    std::vector<const Biome*> result(palette.size(), nullptr);
    const registry::Registry<const Biome*>* registry = registry::Registries::BIOMES();
    for (size_t i = 0; i < palette.size(); ++i) {
        nbt::TagValue& entry = palette[i];
        auto* biome = registry->get(utils::Identifier::of(entry.as<nbt::StringTag>().get()));
        if (!biome) throw std::runtime_error(std::format("Biome '{}' not found in registry", entry.as<nbt::StringTag>().get()));
        result[i] = biome;
    }
    return result;
}
} // namespace stratos::world