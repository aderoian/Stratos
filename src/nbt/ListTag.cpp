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

#include "NBTValue.h"
#include "PrimitiveTag.h"
#include "StringTag.h"

namespace stratos {

ListTag::ListTag(const std::initializer_list<int8_t> init) { ListTag::init<ByteTag>(init); }
ListTag::ListTag(const std::initializer_list<int16_t> init) { ListTag::init<ShortTag>(init); }
ListTag::ListTag(const std::initializer_list<int32_t> init) { ListTag::init<IntTag>(init); }
ListTag::ListTag(const std::initializer_list<int64_t> init) { ListTag::init<LongTag>(init); }
ListTag::ListTag(const std::initializer_list<float> init) { ListTag::init<FloatTag>(init); }
ListTag::ListTag(const std::initializer_list<double> init) { ListTag::init<DoubleTag>(init); }
ListTag::ListTag(const std::initializer_list<std::string> init) { ListTag::init<StringTag>(init); }
ListTag::ListTag(const std::initializer_list<ByteArrayTag> init) { ListTag::init<ByteArrayTag>(init); }
ListTag::ListTag(const std::initializer_list<ListTag> init) { ListTag::init<ListTag>(init); }
ListTag::ListTag(const std::initializer_list<CompoundTag> init) { ListTag::init<CompoundTag>(init); }
ListTag::ListTag(const std::initializer_list<IntArrayTag> init) { ListTag::init<IntArrayTag>(init); }
ListTag::ListTag(const std::initializer_list<LongArrayTag> init) { ListTag::init<LongArrayTag>(init); }
ListTag::ListTag(const std::initializer_list<TagValue> init) {
    if (init.size() == 0) {
        tagType = TagType::Null; // empty list
    } else {
        tagType = init.begin()->getType(); // set content type from first element
        tags.reserve(init.size());
        for (const auto& val : init) {
            if (tagType != val.getType()) throw std::invalid_argument("The tag type does not match the list's content type");
        }
        tags.assign(init.begin(), init.end());
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

} // namespace stratos