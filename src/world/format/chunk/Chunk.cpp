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

#include "Chunk.h"

#include "block/Blocks.h"
#include "nbt/CompoundTag.h"
#include "nbt/ListTag.h"
#include "nbt/PrimitiveTag.h"
#include "registry/Registries.h"

namespace stratos::world {

void ChunkSection::readNBT(nbt::CompoundTag& nbt) {
    y = nbt["Y"].as<nbt::ByteTag>().get();
    auto& blockStatesTag = nbt["block_states"].as<nbt::CompoundTag>();
    blocks = read(&block::Blocks::STATES,
        BLOCK_STATE,
        readBlockStatePalette(blockStatesTag),
        blockStatesTag.hasKey("data") ? blockStatesTag["data"].as<nbt::LongArrayTag>().get() : std::vector<int64_t>()
        );

    auto& biomesTag = nbt["biomes"].as<nbt::CompoundTag>();
    biomes = read(registry::Registries::BIOMES(),
        BIOME,
        readBiomePalette(biomesTag),
        biomesTag["data"].as<nbt::LongArrayTag>().get()
    );
}
void Chunk::readNBT(nbt::CompoundTag& nbt) {
    x = nbt["xPos"].as<nbt::IntTag>().get();
    z = nbt["zPos"].as<nbt::IntTag>().get();
    lowY = nbt["yPos"].as<nbt::IntTag>().get();

    auto& sectionsTag = nbt["sections"].as<nbt::ListTag>();
    sections.resize(sectionsTag.size());
    for (size_t i = 0; i < sectionsTag.size(); i++) {
        auto& sectionTag = sectionsTag[i].as<nbt::CompoundTag>();
        auto* section = new ChunkSection();
        section->readNBT(sectionTag);
        sections[i] = section;
    }

}
} // namespace stratos