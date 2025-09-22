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

#include "Region.h"

#include "nbt/CompoundTag.h"
#include "nbt/io/NBTBuffer.h"
#include "Server.h"
#include "utils/io/CompressionUtils.h"
#include "world/format/chunk/Chunk.h"

#include <format>

namespace stratos::world {

constexpr int HEADER_TABLE_BYTES = 1024 * 4;
constexpr int HEADER_SIZE = HEADER_TABLE_BYTES * 2;
constexpr int SECTOR_BYTES = 4096;

Region::Region(int x, int y, Path regionRoot) : x(x), z(y), file(open(regionRoot.resolve(std::format("r.{}.{}.mca", x, z)), std::ios::in | std::ios::out | std::ios::binary)) {
    loadHeader();
}
bool Region::isMemberChunk(const int chunkX, const int chunkZ) const {
    return chunkX >> 5 == x && chunkZ >> 5 == z;
}
bool Region::isChunkGenerated(const int chunkX, const int chunkZ) const {
    const ChunkEntry entry = entries[index(chunkX, chunkZ)];
    return entry.offset != 0 && entry.size != 0;
}
bool Region::isChunkLoaded(const int chunkX, const int chunkZ) const {
    return chunks[index(chunkX, chunkZ)] != nullptr;
}
int Region::index(const int chunkX, const int chunkZ) {
    return (chunkX & 31) + (chunkZ & 31) * 32;
}
void Region::loadHeader() {
    entries = std::vector<ChunkEntry>(1024);
    file.seekg(0, std::ios::beg);
    {
        ByteBuffer locations(readBytes(file, HEADER_TABLE_BYTES));
        for (int i = 0; i < 1024; i++) {
            const int offset = locations.readInt24();
            const int size   = locations.readByte();
            entries[i]       = {offset, size, 0};
        }
    }
    {
        ByteBuffer timestamps(readBytes(file, HEADER_TABLE_BYTES, HEADER_TABLE_BYTES));
        for (int i = 0; i < 1024; i++) entries[i].timestamp = timestamps.readInt();
    }

    chunks = std::vector<Chunk*>(1024, nullptr);
}
Chunk* Region::loadChunk(const int chunkX, const int chunkZ) {
    if (!isMemberChunk(chunkX, chunkZ)) throw std::invalid_argument("Chunk is not part of this region");
    if (isChunkLoaded(chunkX, chunkZ)) return getChunk(chunkX, chunkZ);
    if (!isChunkGenerated(chunkX, chunkZ)) return nullptr;
    const ChunkEntry entry = entries[index(chunkX, chunkZ)];

    ByteVec       buffer = readBytes(file, entry.size * SECTOR_BYTES, entry.offset * SECTOR_BYTES);
    ByteBuffer    byteBuffer(std::move(buffer));
    const int     length          = byteBuffer.readInt();
    const uint8_t compressionType = byteBuffer.readByte();

    nbt::NBTBuffer chunkNBT(compressionType != 3 ? decompress(byteBuffer.readByteArray(length - 1)) : byteBuffer.readByteArray(length - 1));

    auto [name, tag] = chunkNBT.readTag<nbt::CompoundTag>();
    if (!tag) throw std::runtime_error("Failed to read chunk NBT data");
    auto* chunk = new Chunk();
    chunk->readNBT(*tag);
    chunks[index(chunkX, chunkZ)] = chunk;
    return chunk;
}
Chunk* Region::getChunk(const int chunkX, const int chunkZ) const {
    return chunks[index(chunkX, chunkZ)];
}
} // namespace stratos