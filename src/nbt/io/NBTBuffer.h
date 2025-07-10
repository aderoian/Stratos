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
#include "nbt/Tag.h"
#include "network/Network.h"
#include "utils/io/ByteBuffer.h"

#include <memory>

namespace stratos::nbt {
enum class TagType : std::int8_t;
class Tag;
class CompoundTag;
class ListTag;
class StringTag;

class NBTBuffer : public ByteBuffer {
  public:
    NBTBuffer() = default;
    explicit NBTBuffer(const ByteVec& data) : ByteBuffer(data, 0) {}
    explicit NBTBuffer(ByteVec&& data) : ByteBuffer(std::move(data), 0) {}
    NBTBuffer(const ByteVec& data, const size_t offset) : ByteBuffer(data, offset) {}
    NBTBuffer(ByteVec&& data, const size_t offset) : ByteBuffer(std::move(data), offset) {}
    NBTBuffer(const NBTBuffer&) = delete;
    NBTBuffer& operator=(const NBTBuffer&) = delete;
    NBTBuffer(NBTBuffer&&) = default;
    NBTBuffer& operator=(NBTBuffer&&) = default;

    std::string readTagName();
    std::pair<std::string, std::unique_ptr<Tag>> readTag();
    template <typename T> std::pair<std::string, std::unique_ptr<T>> readTag();
    std::string readModifiedUTF8String();
    void writeTagName(const std::string& tagName);
    void writeTag(const std::string& name, const std::unique_ptr<Tag>& tag);
    void                                                             writeModifiedUTF8String(const std::string& str);
};

template <typename T> std::pair<std::string, std::unique_ptr<T>> NBTBuffer::readTag() {
    static_assert(std::is_base_of_v<Tag, T>, "T must be derived from Tag");
    auto const type = static_cast<TagType>(readByte());
    if (type != T::type)
        throw std::runtime_error("NBTBuffer::readTag: invalid tag type");

    std::string name = readModifiedUTF8String();
    auto tag = internal::makeUnique<T>();
    tag->read(*this);
    return {std::move(name), std::unique_ptr<T>(tag.release())};
}
} // namespace stratos::nbt

#endif //NBTBUFFER_H
