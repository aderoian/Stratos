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

#ifndef COMPOUNDTAG_H
#define COMPOUNDTAG_H
#include "Tag.h"

#include <map>

namespace stratos {
class TagValue;
class TagValueInitializer;
class CompoundTag final : public CRTPTag<CompoundTag> {
    typedef std::map<std::string, TagValue> TagMap;
public:
    typedef TagMap::iterator iterator;
    typedef TagMap::const_iterator constantIterator;

    CompoundTag() {}
    CompoundTag(std::initializer_list<std::pair<std::string, TagValueInitializer>> init);

    TagValue& at(const std::string& key);
    const TagValue& at(const std::string& key) const;

    TagValue& operator[](const std::string& key) { return tags[key]; }

    std::pair<iterator, bool> put(const std::string& key, TagValueInitializer&& val);
    std::pair<iterator, bool> insert(const std::string& key, TagValueInitializer&& val);
    template<class T, class... Args>
    std::pair<iterator, bool> emplace(const std::string& key, Args&&... args);
    bool erase(const std::string& key);
    size_t size() const { return tags.size(); }
    void clear() { tags.clear(); }

    bool hasKey(const std::string& key) const;
    bool hasKey(const std::string& key, TagType type) const;

    iterator begin() { return tags.begin(); }
    iterator end()   { return tags.end(); }
    constantIterator begin() const  { return tags.begin(); }
    constantIterator end() const    { return tags.end(); }
    constantIterator cbegin() const { return tags.cbegin(); }
    constantIterator cend() const   { return tags.cend(); }

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;

    friend bool operator==(const CompoundTag& lhs, const CompoundTag& rhs) { return lhs.tags == rhs.tags; }
    friend bool operator!=(const CompoundTag& lhs, const CompoundTag& rhs) { return !(lhs == rhs); }

private:
    TagMap tags;
};

template<class T, class... Args>
std::pair<CompoundTag::iterator, bool> CompoundTag::emplace(const std::string& key, Args&&... args) {
    return put(key, TagValue(make_unique<T>(std::forward<Args>(args)...)));
}
}

#endif //COMPOUNDTAG_H
