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

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "utils/collection/PalettedStorage.h"
#include "utils/Predicate.h"

#include <string>

namespace stratos::world {
class BlockState;
class Chunk;

class HeightmapType {
public:
    enum class Purpose {
        WORLD_GEN,
        LIVE_WORLD,
        CLIENT
    };

    HeightmapType(const int id, std::string(name), Purpose purpose, Predicate<BlockState> blockPredicate) :
        id(id), name(std::move(name)), purpose(purpose), blockPredicate(std::move(blockPredicate)) {}

    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] Purpose getPurpose() const { return purpose; }
    [[nodiscard]] const Predicate<BlockState>& getBlockPredicate() const { return blockPredicate; }

private:
    int id;
    std::string name;
    Purpose purpose;
    Predicate<BlockState> blockPredicate;
};

class Heightmap {
public:
    Heightmap(const Chunk* chunk, const HeightmapType* type);
    Heightmap(const Chunk* chunk, const HeightmapType* type, int bits, const std::vector<int64_t>& data);

    [[nodiscard]] const std::vector<int64_t>& getData() const;
    [[nodiscard]] const HeightmapType* getType() const;
    [[nodiscard]] const Predicate<BlockState>& getBlockPredicate() const;
    [[nodiscard]] const Chunk* getChunk() const;
private:
    PackedIntegerArray* data;
    const HeightmapType* type;
    Predicate<BlockState> blockPredicate;
    const Chunk* chunk;
};

extern const HeightmapType* WORLD_SURFACE_WG;
extern const HeightmapType* WORLD_SURFACE;
extern const HeightmapType* OCEAN_FLOOR_WG;
extern const HeightmapType* OCEAN_FLOOR;
extern const HeightmapType* MOTION_BLOCKING;
extern const HeightmapType* MOTION_BLOCKING_NO_LEAVES;

} // namespace stratos::world

#endif //HEIGHTMAP_H
