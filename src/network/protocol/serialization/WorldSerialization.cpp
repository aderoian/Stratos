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

#include "WorldSerialization.h"

#include "PacketBuffer.h"
#include "world/format/chunk/Chunk.h"
#include "world/format/chunk/Heightmap.h"

namespace stratos::network {
ChunkSectionEntry ChunkSectionEntry::fromChunkSection(const world::ChunkSection* section) {
    return {1, section->getBlocks(), section->getBiomes()};
}
void ChunkData::write(PacketBuffer& buffer) const {
    buffer.writeVarInt(3);
    for (auto [id, data] : heightmaps) {
        buffer.writeVarInt(id);
        buffer.writePrefixedLongArray(*data);
    }

    int dataSize = 0;
    int i = 0;
    for (const auto& section : sections) {
        std::cout << "Section (" << i << "): " << static_cast<int>(sizeof(short)) << " + ";
        int inc = static_cast<int>(sizeof(short)) + section.blocks->writeSize() + section.biomes->writeSize();
        i++;
        std::cout << std::endl;

        PacketBuffer pb;
        pb.writeShort(section.blockCount);
        section.blocks->write(pb);
        section.biomes->write(pb);
        assert(pb.size() == inc);
        dataSize += inc;
    }

    PacketBuffer testBuf;
    for (const auto& [blockCount, blocks, biomes] : sections) {
        testBuf.writeShort(blockCount);
        blocks->write(testBuf);
        biomes->write(testBuf);
    }

    std::cout << dataSize << "vs" << testBuf.size() << std::endl;
    assert(dataSize == testBuf.size());

    buffer.writeVarInt(dataSize);
    for (const auto& [blockCount, blocks, biomes] : sections) {
        buffer.writeShort(blockCount);
        blocks->write(buffer);
        biomes->write(buffer);
    }
    buffer.writeVarInt(0); // TODO: block entities
}
ChunkData ChunkData::fromChunk(const world::Chunk* chunk) {
    auto&                          sections = chunk->getSections();
    std::vector<ChunkSectionEntry> sectionEntries;
    sectionEntries.reserve(sections.size());
    for (const auto* section : sections) sectionEntries.emplace_back(ChunkSectionEntry::fromChunkSection(section));

    return {{{0, &chunk->getWorldSurface()->getData()}, {1, &chunk->getOceanFloor()->getData()}, {2, &chunk->getMotionBlocking()->getData()}}, std::move(sectionEntries)};
}
void LightData::write(PacketBuffer& buffer) const {
    buffer.writePrefixedLongArray(skyLightMask.toVector());
    buffer.writePrefixedLongArray(blockLightMask.toVector());
    buffer.writePrefixedLongArray(emptySkyLightMask.toVector());
    buffer.writePrefixedLongArray(emptyBlockLightMask.toVector());
    buffer.writeVarInt(static_cast<int>(skyLightData.size()));
    for (const auto& data : skyLightData)
        buffer.writePrefixedSignedByteArray(data);
    buffer.writeVarInt(static_cast<int>(blockLightData.size()));
    for (const auto& data : blockLightData)
        buffer.writePrefixedSignedByteArray(data);
}
LightData LightData::fromChunk(const world::Chunk* chunk) {
    auto&     sections    = chunk->getSections();
    const int numSections = static_cast<int>(sections.size());

    utils::BitSet skyLightMask(1);
    utils::BitSet blockLightMask(1);
    utils::BitSet emptySkyLightMask(1);
    utils::BitSet emptyBlockLightMask(1);
    std::vector<std::vector<int8_t>> skyLightData;
    std::vector<std::vector<int8_t>> blockLightData;

    emptySkyLightMask.set(numSections+1);
    emptyBlockLightMask.set(numSections+1);
    int i;
    for (i = numSections; i >= 1; --i) {
        const auto* section = sections[i-1];
        if (section->getSkyLight()) {
            skyLightMask.set(numSections - i + 1);
            skyLightData.push_back(*section->getSkyLight());
        } else emptySkyLightMask.set(numSections - i + 1);
        if (section->getBlockLight()) {
            blockLightMask.set(numSections - i + 1);
            blockLightData.push_back(*section->getBlockLight());
        } else emptyBlockLightMask.set(numSections - i + 1);
    }
    emptySkyLightMask.set(0);
    emptyBlockLightMask.set(0);

    return {std::move(skyLightMask), std::move(blockLightMask), std::move(emptySkyLightMask), std::move(emptyBlockLightMask),
            std::move(skyLightData), std::move(blockLightData)};
}
} // namespace stratos::network