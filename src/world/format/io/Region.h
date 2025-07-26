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

#ifndef REGION_H
#define REGION_H
#include "utils/io/FileUtils.h"

namespace stratos::world {
class Chunk;
struct ChunkEntry {
    int offset;
    int size;
    int timestamp;
};

class Region {
public:
    Region(int x, int y, Path regionRoot);

    bool isMemberChunk(int chunkX, int chunkZ) const;
    bool       isChunkGenerated(int chunkX, int chunkZ) const;
    bool       isChunkLoaded(int chunkX, int chunkZ) const;
    static int index(int chunkX, int chunkZ);

    Chunk* loadChunk(int chunkX, int chunkZ);
    Chunk* getChunk(int chunkX, int chunkZ) const;
private:
    int x;
    int z;

    std::fstream file;
    std::vector<ChunkEntry> entries;
    std::vector<Chunk*> chunks;

    void loadHeader();
};
} // namespace stratos

#endif //REGION_H
