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

#include "ListTag.h"

#include "io/NBTBuffer.h"
#include "PrimitiveTag.h"
#include "StringTag.h"
#include "Value.h"

namespace stratos::nbt {

ListTag::ListTag(const std::initializer_list<int8_t> il) { init<ByteTag>(il); }
ListTag::ListTag(const std::initializer_list<int16_t> il) { init<ShortTag>(il); }
ListTag::ListTag(const std::initializer_list<int32_t> il) { init<IntTag>(il); }
ListTag::ListTag(const std::initializer_list<int64_t> il) { init<LongTag>(il); }
ListTag::ListTag(const std::initializer_list<float> il) { init<FloatTag>(il); }
ListTag::ListTag(const std::initializer_list<double> il) { init<DoubleTag>(il); }
ListTag::ListTag(const std::initializer_list<std::string> il) { init<StringTag>(il); }
ListTag::ListTag(const std::initializer_list<ByteArrayTag> il) { init<ByteArrayTag>(il); }
ListTag::ListTag(const std::initializer_list<ListTag> il) { init<ListTag>(il); }
ListTag::ListTag(const std::initializer_list<CompoundTag> il) { init<CompoundTag>(il); }
ListTag::ListTag(const std::initializer_list<IntArrayTag> il) { init<IntArrayTag>(il); }
ListTag::ListTag(const std::initializer_list<LongArrayTag> il) { init<LongArrayTag>(il); }
ListTag::ListTag(const std::initializer_list<TagValue> il) {
    if (il.size() == 0) {
        tagType = TagType::Null; // empty list
    } else {
        tagType = il.begin()->getType(); // set content type from first element
        tags.reserve(il.size());
        for (const auto& val : il) {
            if (tagType != val.getType()) throw std::invalid_argument("The tag type does not match the list's content type");
        }
        tags.assign(il.begin(), il.end());
    }
}
TagValue&       ListTag::at(size_t i) { return tags.at(i); }
const TagValue& ListTag::at(size_t i) const {
    return tags.at(i);
}
void ListTag::set(const size_t i, TagValue&& val) {
    if (val.getType() != tagType) throw std::invalid_argument("The tag type does not match the list's content type");
    tags.at(i) = std::move(val);
}
void ListTag::push_back(TagValueInitializer&& val) {
    if (!val) throw std::invalid_argument("The value cannot be null");
    if (tagType == TagType::Null) {
        tagType = val.getType();
    } else if (tagType != val.getType()) {
        throw std::invalid_argument("The tag type does not match the list's content type");
    }
    tags.push_back(std::move(val));
}
void ListTag::reset(const TagType type) {
    clear();
    tagType = type;
}
void ListTag::read(NBTBuffer& buffer) {
    clear();
    tagType = static_cast<TagType>(buffer.readByte());
    if (tagType == TagType::End) return;
    int length = buffer.readInt();
    while (length--) {
        auto tag = Tag::create(tagType);
        tag->read(buffer);
        push_back(TagValueInitializer(std::move(tag)));
    }
}
void ListTag::write(NBTBuffer& buffer) const {
    if (tags.empty()) {
        buffer.writeByte(0);
        buffer.writeInt(0);
    } else {
        buffer.writeByte(static_cast<uint8_t>(tagType));
        buffer.writeInt(static_cast<int>(tags.size()));
        for (const auto& tag : tags) {
            buffer.writeByte(static_cast<uint8_t>(tag.getType()));
            tag.get().write(buffer);
        }
    }
}

bool operator==(const ListTag& lhs, const ListTag& rhs) {
    return lhs.tagType == rhs.tagType && lhs.tags == rhs.tags;
}
bool operator!=(const ListTag& lhs, const ListTag& rhs) {
    return !(lhs == rhs);
}
} // namespace stratos::nbt