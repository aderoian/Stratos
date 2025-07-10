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

#ifndef NBT_H
#define NBT_H
#include "io/NBTBuffer.h"
#include "utils/io/CompressionUtils.h"
#include "utils/io/FileUtils.h"

#include <memory>
#include <string>
#include <vector>

namespace stratos {
class ByteBuffer;
}
namespace stratos::nbt {
using ByteVec = std::vector<uint8_t>;
class Tag;

std::unique_ptr<Tag> readNBTFromFile(const Path& path, bool compressed = false);
template <typename T>
std::unique_ptr<T> readNBTFromFile(const Path& path, bool compressed = false);
std::unique_ptr<Tag> readNBTFromBytes(const ByteVec& buffer, bool compressed = false);
template <typename T>
std::unique_ptr<T> readNBTFromBytes(const ByteVec& buffer, bool compressed = false);
void writeNBTToFile(const Path& path, const std::string& name, const std::unique_ptr<Tag>& tag, bool compressed = false, bool gzip = false);
ByteVec writeNBTToBytes(const std::string& name, const std::unique_ptr<Tag>& tag, bool compressed = false, bool gzip = false);

/**
 * @brief Network NBT is unique and begins with an un-named tag.
 */
std::unique_ptr<Tag> readNetworkNBT(const ByteBuffer& buffer);
template <typename T>
std::unique_ptr<T> readNetworkNBT(const ByteBuffer& buffer);
ByteVec writeNetworkNBT(const std::unique_ptr<Tag>& tag);
ByteVec writeNetworkNBT(const Tag& tag);
template <typename T>
std::unique_ptr<T> readNBTFromFile(const Path& path, const bool compressed) { return readNBTFromBytes<T>(stratos::readAllBytes(path), compressed); }
template <typename T>
std::unique_ptr<T> readNBTFromBytes(const ByteVec& buffer, const bool compressed) {
    NBTBuffer nbtBuf = compressed ? NBTBuffer(stratos::decompress(buffer)) : NBTBuffer(buffer);

    std::unique_ptr<Tag> tag = nbtBuf.readTag().second;
    if (!tag) throw std::runtime_error("NBT tag is null");

    T* result = dynamic_cast<T*>(tag.get());
    if (!result) throw std::bad_cast();

    tag.release();
    return std::unique_ptr<T>(result);
}
template <typename T>
std::unique_ptr<T> readNetworkNBT(const ByteBuffer& buffer) {
    NBTBuffer nbtBuf((buffer.data()));
    // We must read the first tag manually
    const auto type = static_cast<TagType>(nbtBuf.readByte());
    auto tag = Tag::create(type);
    tag->read(nbtBuf);

    T* result = dynamic_cast<T*>(tag.get());
    if (!result) throw std::bad_cast();

    tag.release();
    return std::unique_ptr<T>(result);
}

} // namespace stratos::nbt

#endif //NBT_H
