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

#ifndef CHUNK_H
#define CHUNK_H
#include "Palette.h"
#include "utils/collection/BitSet.h"
#include "network/protocol/serialization/WorldSerialization.h"

namespace stratos::nbt {
class CompoundTag;
}
namespace stratos::world {
class ChunkSection;
class Heightmap;

class Chunk {
public:
    Chunk() = default;
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getZ() const;
    [[nodiscard]] int getLowY() const;
    [[nodiscard]] const std::vector<ChunkSection*>& getSections() const;
    [[nodiscard]] const Heightmap* getMotionBlocking() const;
    [[nodiscard]] const Heightmap* getMotionBlockingNoLeaves() const;
    [[nodiscard]] const Heightmap* getOceanFloor() const;
    [[nodiscard]] const Heightmap* getWorldSurface() const;

    void readNBT(nbt::CompoundTag& nbt);
private:
    int x;
    int z;
    int lowY;

    std::vector<ChunkSection*> sections;
    Heightmap* motionBlocking;
    Heightmap* motionBlockingNoLeaves;
    Heightmap* oceanFloor;
    Heightmap* worldSurface;
};

class ChunkSection {
public:
    ChunkSection(const Chunk* chunk);
    [[nodiscard]] int getY() const;
    [[nodiscard]] const PalettedContainer<const block::BlockState*>* getBlocks() const;
    [[nodiscard]] const PalettedContainer<const Biome*>* getBiomes() const;
    [[nodiscard]] const std::vector<int8_t>* getBlockLight() const;
    [[nodiscard]] const std::vector<int8_t>* getSkyLight() const;

    void readNBT(nbt::CompoundTag& nbt);
private:
    const Chunk* chunk;
    int y;
    const PalettedContainer<const block::BlockState*>* blocks;
    const PalettedContainer<const Biome*>* biomes;
    std::vector<int8_t>* blockLight;
    std::vector<int8_t>* skyLight;
};

} // namespace stratos

#endif //CHUNK_H
