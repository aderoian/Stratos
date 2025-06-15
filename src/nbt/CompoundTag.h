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
#include "Value.h"

#include <map>

namespace stratos::nbt {
class TagValue;
class TagValueInitializer;
class CompoundTag final : public CRTPTag<CompoundTag> {
    typedef std::map<std::string, TagValue> TagMap;
public:
    typedef TagMap::iterator Iterator;
    typedef TagMap::const_iterator ConstantIterator;
    typedef std::pair<std::string, TagValueInitializer> CompoundElement;

    static constexpr auto type = TagType::Compound;

    CompoundTag() = default;
    CompoundTag(std::initializer_list<std::pair<std::string, TagValueInitializer>> init);

    TagValue& at(const std::string& key);
    [[nodiscard]] const TagValue& at(const std::string& key) const;

    TagValue& operator[](const std::string& key) { return tags[key]; }

    std::pair<Iterator, bool> put(const std::string& key, TagValueInitializer&& val);
    std::pair<Iterator, bool> insert(const std::string& key, TagValueInitializer&& val);
    template<class T, class... Args>
    std::pair<Iterator, bool> emplace(const std::string& key, Args&&... args);
    bool erase(const std::string& key);
    [[nodiscard]] size_t size() const { return tags.size(); }
    void clear() { tags.clear(); }

    [[nodiscard]] bool hasKey(const std::string& key) const;
    [[nodiscard]] bool hasKey(const std::string& key, TagType type) const;

    Iterator begin() { return tags.begin(); }
    Iterator end()   { return tags.end(); }
    [[nodiscard]] ConstantIterator begin() const  { return tags.begin(); }
    [[nodiscard]] ConstantIterator end() const    { return tags.end(); }
    [[nodiscard]] ConstantIterator cbegin() const { return tags.cbegin(); }
    [[nodiscard]] ConstantIterator cend() const   { return tags.cend(); }

    void read(NBTBuffer& buffer) override;
    void write(NBTBuffer& buffer) const override;

    friend bool operator==(const CompoundTag& lhs, const CompoundTag& rhs);
    friend bool operator!=(const CompoundTag& lhs, const CompoundTag& rhs);

private:
    TagMap tags;
};

template<class T, class... Args>
std::pair<CompoundTag::Iterator, bool> CompoundTag::emplace(const std::string& key, Args&&... args) {
    return put(key, TagValueInitializer(internal::makeUnique<T>(std::forward<Args>(args)...)));
}
} // namespace stratos::nbt

#endif //COMPOUNDTAG_H
