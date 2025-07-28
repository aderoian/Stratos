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

namespace stratos::nbt {
class CompoundTag;
}
namespace stratos::world {

class ChunkSection {
public:
    ChunkSection() = default;

    void readNBT(nbt::CompoundTag& nbt);
private:
    int y;
    const PalettedContainer<const block::BlockState*>* blocks;
    const PalettedContainer<const Biome*>* biomes;
    // TODO: Block light
    // TODO: Sky light


};

class Chunk {
public:
    Chunk() = default;
    int getHeight() const;

    void readNBT(nbt::CompoundTag& nbt);
private:
    int x;
    int z;
    int lowY;

    std::vector<ChunkSection*> sections;
};

} // namespace stratos

#endif //CHUNK_H
