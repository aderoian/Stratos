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

#import "CompoundTag.h"

#include "io/NBTBuffer.h"
#import "NBTValue.h"

namespace stratos {

CompoundTag::CompoundTag(std::initializer_list<std::pair<std::string, TagValueInitializer>> init) {
    for (const auto& [name, value] : init) {
        tags.emplace(std::move(name), std::move(value));
    }
}
TagValue& CompoundTag::at(const std::string& key) { return tags.at(key); }
const TagValue& CompoundTag::at(const std::string& key) const {
    return tags.at(key);
}
std::pair<CompoundTag::iterator, bool> CompoundTag::put(const std::string& key, TagValueInitializer&& val) {
    if (auto it = tags.find(key); it != tags.end()) {
        it->second = std::move(val);
        return {it, false};
    }
    return tags.emplace(key, std::move(val));
}
std::pair<CompoundTag::iterator, bool> CompoundTag::insert(const std::string& key, TagValueInitializer&& val) { return tags.emplace(key, std::move(val)); }
bool CompoundTag::erase(const std::string& key) { return tags.erase(key) != 0;}
bool CompoundTag::hasKey(const std::string& key) const { return tags.contains(key); }
bool                                   CompoundTag::hasKey(const std::string& key, const TagType type) const {
    const auto it = tags.find(key);
    return it != tags.end() && it->second.get().getType() == type;
}
void CompoundTag::read(NBTBuffer& buffer) {
    clear();
    while (true) {
        auto [name, tag] = buffer.readTag();
        if (tag == nullptr || tag->getType() == TagType::End) break; // End tag indicates no further tags
        tags.emplace(std::move(name), std::move(tag));
    }
}
void CompoundTag::write(NBTBuffer& buffer) const {
    for (const auto& [name, value] : tags) {
        buffer.writeTagName(name);
        value.get().write(buffer);
    }
}

} // namespace stratos