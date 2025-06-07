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

#include "CompoundTag.h"
#include "ListTag.h"
#include "PrimitiveTag.h"
#include "StringTag.h"
#include "Value.h"

namespace stratos::nbt {
TagValue::TagValue(Tag&& t) { tag = std::move(t).moveClone(); }
TagValue::TagValue(const TagValue& rhs) { rhs.tag ? tag = rhs.tag->clone() : tag = nullptr; }
TagValue& TagValue::operator=(const TagValue& rhs) {
    if (this != &rhs)
        tag = rhs.tag ? rhs.tag->clone() :  nullptr;
    return *this;
}
TagValue& TagValue::operator=(Tag&& t) {
    set(std::move(t));
    return *this;
}
void      TagValue::set(Tag&& t) {
    if (tag) {
        tag->assign(std::move(t));
    } else {
        tag = std::move(t).moveClone();
    }
}
TagValue& TagValue::operator=(const int8_t val) {
    if (!tag) {
        set(ByteTag(val));
    } else switch (tag->getType()) {
    case TagType::Byte:
        static_cast<ByteTag&>(*tag).set(val);
        break;
    case TagType::Short:
        static_cast<ShortTag&>(*tag).set(val);
        break;
    case TagType::Int:
        static_cast<IntTag&>(*tag).set(val);
        break;
    case TagType::Long:
        static_cast<LongTag&>(*tag).set(val);
        break;
    case TagType::Float:
        static_cast<FloatTag&>(*tag).set(val);
        break;
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const int16_t val) {
    if (!tag) {
        set(ShortTag(val));
    } else switch (tag->getType()) {
    case TagType::Short:
        static_cast<ShortTag&>(*tag).set(val);
        break;
    case TagType::Int:
        static_cast<IntTag&>(*tag).set(val);
        break;
    case TagType::Long:
        static_cast<LongTag&>(*tag).set(val);
        break;
    case TagType::Float:
        static_cast<FloatTag&>(*tag).set(val);
        break;
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const int32_t val) {
    if (!tag) {
        set(IntTag(val));
    } else switch (tag->getType()) {
    case TagType::Int:
        static_cast<IntTag&>(*tag).set(val);
        break;
    case TagType::Long:
        static_cast<LongTag&>(*tag).set(val);
        break;
    case TagType::Float:
        static_cast<FloatTag&>(*tag).set(val);
        break;
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const int64_t val) {
    if (!tag) {
        set(LongTag(val));
    } else switch (tag->getType()) {
    case TagType::Long:
        static_cast<LongTag&>(*tag).set(val);
        break;
    case TagType::Float:
        static_cast<FloatTag&>(*tag).set(val);
        break;
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const float val) {
    if (!tag) {
        set(FloatTag(val));
    } else switch (tag->getType()) {
    case TagType::Float:
        static_cast<FloatTag&>(*tag).set(val);
        break;
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const double val) {
    if (!tag) {
        set(DoubleTag(val));
    } else switch (tag->getType()) {
    case TagType::Double:
        static_cast<DoubleTag&>(*tag).set(val);
        break;
    default:
        throw std::bad_cast();
    }
    return *this;
}
TagValue& TagValue::operator=(const std::string& str) {
    if (!tag) {
        set(StringTag(str));
    } else {
        dynamic_cast<StringTag&>(*tag).set(str);
    }
    return *this;
}
TagValue& TagValue::operator=(std::string&& str) {
    if (!tag) {
        set(StringTag(str));
    } else {
        dynamic_cast<StringTag&>(*tag).set(std::move(str));
    }
    return *this;
}
TagValue::operator signed char() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator short() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    case TagType::Short:
        return static_cast<ShortTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator int() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    case TagType::Short:
        return static_cast<ShortTag&>(*tag).get();
    case TagType::Int:
        return static_cast<IntTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator long long() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    case TagType::Short:
        return static_cast<ShortTag&>(*tag).get();
    case TagType::Int:
        return static_cast<IntTag&>(*tag).get();
    case TagType::Long:
        return static_cast<LongTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator float() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    case TagType::Short:
        return static_cast<ShortTag&>(*tag).get();
    case TagType::Int:
        return static_cast<IntTag&>(*tag).get();
    case TagType::Long:
        return static_cast<LongTag&>(*tag).get();
    case TagType::Float:
        return static_cast<FloatTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator double() const {
    switch(tag->getType())
    {
    case TagType::Byte:
        return static_cast<ByteTag&>(*tag).get();
    case TagType::Short:
        return static_cast<ShortTag&>(*tag).get();
    case TagType::Int:
        return static_cast<IntTag&>(*tag).get();
    case TagType::Long:
        return static_cast<LongTag&>(*tag).get();
    case TagType::Float:
        return static_cast<FloatTag&>(*tag).get();
    case TagType::Double:
        return static_cast<DoubleTag&>(*tag).get();
    default:
        throw std::bad_cast();
    }
}
TagValue::operator const std::string&() const { return dynamic_cast<std::string&>(*tag); }
TagValue&       TagValue::at(const std::string& key) { return dynamic_cast<CompoundTag&>(*tag).at(key); }
const TagValue& TagValue::at(const std::string& key) const { return dynamic_cast<const CompoundTag&>(*tag).at(key); }
TagValue&       TagValue::operator[](const std::string& key) { return dynamic_cast<CompoundTag&>(*tag)[key]; }
TagValue&       TagValue::operator[](const char* key) { return (*this)[std::string(key)]; }
TagValue&       TagValue::at(size_t i) { return dynamic_cast<ListTag&>(*tag).at(i); }
const TagValue& TagValue::at(size_t i) const { return dynamic_cast<const ListTag&>(*tag).at(i); }
TagValue&       TagValue::operator[](size_t i) { return dynamic_cast<ListTag&>(*tag).at(i); }
const TagValue& TagValue::operator[](size_t i) const { return dynamic_cast<const ListTag&>(*tag).at(i); }
TagType         TagValue::getType() const {
    return tag ? tag->getType() : TagType::Null;
}
TagValueInitializer::TagValueInitializer(const int8_t val) : TagValue(ByteTag(val)) {}
TagValueInitializer::TagValueInitializer(const int16_t val) : TagValue(ShortTag(val)) {}
TagValueInitializer::TagValueInitializer(const int32_t val) : TagValue(IntTag(val)) {}
TagValueInitializer::TagValueInitializer(const int64_t val) : TagValue(LongTag(val)) {}
TagValueInitializer::TagValueInitializer(const float val) : TagValue(FloatTag(val)) {}
TagValueInitializer::TagValueInitializer(const double val) : TagValue(DoubleTag(val)) {}
TagValueInitializer::TagValueInitializer(const std::string& str) : TagValue(StringTag(str)) {}
TagValueInitializer::TagValueInitializer(std::string&& str) : TagValue(StringTag(std::move(str))) {}
TagValueInitializer::TagValueInitializer(const char* str) : TagValue(StringTag(str)) {}
bool            operator==(const TagValue& lhs, const TagValue& rhs) {
    if (lhs.tag != nullptr && rhs.tag != nullptr)
        return *lhs.tag == *rhs.tag;
    return lhs.tag == nullptr && rhs.tag == nullptr;
}
bool            operator!=(const TagValue& lhs, const TagValue& rhs) {
    return !(lhs == rhs);
}
} // namespace stratos ::nbt