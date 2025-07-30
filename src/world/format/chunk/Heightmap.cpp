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

#include "Heightmap.h"
#include "Chunk.h"

namespace stratos::world {

Heightmap::Heightmap(const Chunk* chunk, const HeightmapType* type) : data(new PackedIntegerArray(9, 256)), blockPredicate(type->getBlockPredicate()), chunk(chunk) {}
Heightmap::Heightmap(const Chunk* chunk, const HeightmapType* type, const int bits, const std::vector<int64_t>& data) : data(new PackedIntegerArray(bits, 256, data)), blockPredicate(type->getBlockPredicate()), chunk(chunk) {}

// TODO: Define the block predicates for each heightmap type
const HeightmapType* WORLD_SURFACE_WG = new HeightmapType(
    0, "WORLD_SURFACE_WG", HeightmapType::Purpose::WORLD_GEN,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
const HeightmapType* WORLD_SURFACE = new HeightmapType(
    1, "WORLD_SURFACE", HeightmapType::Purpose::CLIENT,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
const HeightmapType* OCEAN_FLOOR_WG = new HeightmapType(
    2, "OCEAN_FLOOR_WG", HeightmapType::Purpose::CLIENT,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
const HeightmapType* OCEAN_FLOOR = new HeightmapType(
    3, "OCEAN_FLOOR", HeightmapType::Purpose::LIVE_WORLD,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
const HeightmapType* MOTION_BLOCKING = new HeightmapType(
    4, "MOTION_BLOCKING", HeightmapType::Purpose::CLIENT,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
const HeightmapType* MOTION_BLOCKING_NO_LEAVES = new HeightmapType(
    5, "MOTION_BLOCKING_NO_LEAVES", HeightmapType::Purpose::CLIENT,
    Predicate<BlockState>([](const BlockState& state) { return true; }) // Placeholder predicate
);
} // namespace stratos::world
