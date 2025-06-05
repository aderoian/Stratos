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

#include "Tag.h"

#include "ArrayTag.h"
#include "CompoundTag.h"
#include "ListTag.h"
#include "PrimitiveTag.h"
#include "StringTag.h"

namespace stratos {
bool isValidType(const int type, const bool allowEnd) {
    return (allowEnd ? 0 : 1) <= type && type <= 12;
}
std::unique_ptr<Tag> Tag::clone() && {
    return std::move(*this).moveClone();
}
std::unique_ptr<Tag> Tag::create(const TagType type) {
    switch (type) {
    case TagType::Byte: return nbtinternal::makeUnique<ByteTag>();
    case TagType::Short: return nbtinternal::makeUnique<ShortTag>();
    case TagType::Int: return nbtinternal::makeUnique<IntTag>();
    case TagType::Long: return nbtinternal::makeUnique<LongTag>();
    case TagType::Float: return nbtinternal::makeUnique<FloatTag>();
    case TagType::Double: return nbtinternal::makeUnique<DoubleTag>();
    case TagType::ByteArray: return nbtinternal::makeUnique<ByteArrayTag>();
    case TagType::String: return nbtinternal::makeUnique<StringTag>();
    case TagType::List: return nbtinternal::makeUnique<ListTag>();
    case TagType::Compound: return nbtinternal::makeUnique<CompoundTag>();
    case TagType::IntArray: return nbtinternal::makeUnique<IntArrayTag>();
    case TagType::LongArray: return nbtinternal::makeUnique<LongArrayTag>();
    default: throw std::invalid_argument("Invalid tag type");
    }
}
bool                 operator==(const Tag& lhs, const Tag& rhs) { return typeid(lhs) == typeid(rhs) && lhs.equals(rhs); }
bool                 operator!=(const Tag& lhs, const Tag& rhs) { return !(lhs == rhs); }
} // namespace stratos