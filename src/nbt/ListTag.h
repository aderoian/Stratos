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

#ifndef LISTTAG_H
#define LISTTAG_H
#include "ArrayTag.h"
#include "CompoundTag.h"
#include "Tag.h"

#include <vector>

namespace stratos {
class TagValue;
class TagValueInitializer;
class ListTag final : CRTPTag<ListTag> {
public:
    typedef std::vector<TagValue>::iterator iterator;
    typedef std::vector<TagValue>::const_iterator constIterator;

    static constexpr auto type = TagType::List;

    template<class T>
    static ListTag of(std::initializer_list<T> init);

    ListTag(): ListTag(TagType::Null) {}
    explicit ListTag(const TagType type) : tagType(type) {}

    ListTag(std::initializer_list<int8_t> init);
    ListTag(std::initializer_list<int16_t> init);
    ListTag(std::initializer_list<int32_t> init);
    ListTag(std::initializer_list<int64_t> init);
    ListTag(std::initializer_list<float> init);
    ListTag(std::initializer_list<double> init);
    ListTag(std::initializer_list<std::string> init);
    ListTag(std::initializer_list<ByteArrayTag> init);
    ListTag(std::initializer_list<ListTag> init);
    ListTag(std::initializer_list<CompoundTag> init);
    ListTag(std::initializer_list<IntArrayTag> init);
    ListTag(std::initializer_list<LongArrayTag> init);

    ListTag(std::initializer_list<TagValue> init);

    TagValue& at(size_t i);
    const TagValue& at(size_t i) const;

    TagValue& operator[](size_t i) { return tags[i]; }
    const TagValue& operator[](size_t i) const { return tags[i]; }

    void set(size_t i, TagValue&& val);
    void push_back(TagValueInitializer&& val);
    template<class T, class... Args>
    void emplace_back(Args&&... args);
    void pop_back() { tags.pop_back(); }
    size_t size() const { return tags.size(); }
    void clear() { tags.clear(); }
    void reset(TagType type = TagType::Null);

    iterator begin() { return tags.begin(); }
    iterator end()   { return tags.end(); }
    constIterator begin() const  { return tags.begin(); }
    constIterator end() const    { return tags.end(); }
    constIterator cbegin() const { return tags.cbegin(); }
    constIterator cend() const   { return tags.cend(); }

    TagType getListType() const { return tagType; }

    void read(NBTBuffer& buffer) override;
    void write(NBTBuffer& buffer) const override;

    friend bool operator==(const ListTag& lhs, const ListTag& rhs);
    friend bool operator!=(const ListTag& lhs, const ListTag& rhs);
private:
    TagType tagType;
    std::vector<TagValue> tags;

    template<class T, class Arg>
    void init(std::initializer_list<Arg> init);
};

template<class T>
ListTag ListTag::of(std::initializer_list<T> init) {
    ListTag result;
    result.init<T, T>(init);
    return result;
}
template<class T, class... Args>
void ListTag::emplace_back(Args&&... args) {
    if(tagType == TagType::Null) //set content type if undetermined
        tagType = T::type;
    else if(tagType != T::type)
        throw std::invalid_argument("The tag type does not match the list's content type");
    tags.emplace_back(make_unique<T>(std::forward<Args>(args)...));
}
template<class T, class Arg>
void ListTag::init(std::initializer_list<Arg> init) {
    tagType = T::type;
    tags.reserve(init.size());
    for(const Arg& arg: init)
        tags.emplace_back(nbtinternal::makeUnique<T>(arg));
}
} // namespace stratos

#endif //LISTTAG_H
