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

#ifndef NBTBUFFER_H
#define NBTBUFFER_H
#include "utils/io/ByteBuffer.h"

#include <memory>

namespace stratos {
enum class TagType : std::int8_t;
class Tag;
class CompoundTag;
class ListTag;
class StringTag;

class NBTBuffer : public ByteBuffer {
public:
    std::string readTagName();
    std::pair<std::string, std::unique_ptr<Tag>> readTag();
    std::string readModifiedUTF8String();
    void writeTagName(const std::string& tagName);
    void writeTag(const std::string& name, const std::unique_ptr<Tag>& tag);
    void writeModifiedUTF8String(const std::string& str);
};

} // stratos

#endif //NBTBUFFER_H
