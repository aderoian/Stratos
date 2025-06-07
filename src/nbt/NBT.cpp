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

#include "NBT.h"
std::unique_ptr<stratos::nbt::Tag> stratos::nbt::readNBTFromFile(const Path& path, const bool compressed) {
    return readNBTFromBytes<Tag>(stratos::readAllBytes(path), compressed);
}
std::unique_ptr<stratos::nbt::Tag> stratos::nbt::readNBTFromBytes(const ByteVec& buffer, const bool compressed) {
    return readNBTFromBytes<Tag>(buffer, compressed);
}
void stratos::nbt::writeNBTToFile(const Path& path, const std::string& name, const std::unique_ptr<Tag>& tag, const bool compressed, const bool gzip) {
    stratos::writeAllBytes(path, writeNBTToBytes(name, tag, compressed, gzip));
}
stratos::nbt::ByteVec stratos::nbt::writeNBTToBytes(const std::string& name, const std::unique_ptr<Tag>& tag, const bool compressed, const bool gzip) {
    NBTBuffer nbtBuf;
    nbtBuf.writeTag(name, tag);
    return compressed ? stratos::compress(nbtBuf, gzip).data() : nbtBuf.data();
}
std::unique_ptr<stratos::nbt::Tag> stratos::nbt::readNetworkNBT(const ByteBuffer& buffer) {
    return readNetworkNBT<Tag>(buffer);
}
ByteVec stratos::nbt::writeNetworkNBT(const std::unique_ptr<Tag>& tag) {
    NBTBuffer nbtBuf;
    nbtBuf.writeByte(static_cast<int8_t>(tag->getType()));
    tag->write(nbtBuf);
    return nbtBuf.data();
}