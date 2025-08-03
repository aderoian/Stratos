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

#ifndef WORLDSERIALIZATION_H
#define WORLDSERIALIZATION_H

#include "utils/collection/BitSet.h"
#include "world/format/chunk/Palette.h"

#include <vector>

namespace stratos {
class PackedIntegerArray;

namespace world {
class ChunkSection;
class Chunk;
}

namespace network {
struct HeightMapEntry {
    int id;
    const std::vector<int64_t>* data;
};

struct ChunkSectionEntry {
    short blockCount;
    const world::PalettedContainer<const block::BlockState*>* blocks;
    const world::PalettedContainer<const world::Biome*>* biomes;

    static ChunkSectionEntry fromChunkSection(const world::ChunkSection* section);
};

struct ChunkData {
    HeightMapEntry heightmaps[3]; // 0: world surface, 1: ocean floor, 2: motion blocking
    std::vector<ChunkSectionEntry> sections;

    void write(PacketBuffer& buffer) const;
    static ChunkData fromChunk(const world::Chunk* chunk);
};

struct LightData {
    utils::BitSet skyLightMask;
    utils::BitSet blockLightMask;
    utils::BitSet emptySkyLightMask;
    utils::BitSet emptyBlockLightMask;
    std::vector<std::vector<int8_t>> skyLightData;
    std::vector<std::vector<int8_t>> blockLightData;

    void write(PacketBuffer& buffer) const;
    static LightData fromChunk(const world::Chunk* chunk);
};

}
}

#endif //WORLDSERIALIZATION_H
