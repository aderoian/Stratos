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

#ifndef ARRAYTAG_H
#define ARRAYTAG_H
#include "Tag.h"

#include <vector>

namespace stratos {
namespace nbtinternal {
template<class T> struct getArrayType { static_assert(sizeof(T) != sizeof(T), "Invalid type parameter for tag_array, can only use byte or int"); };
template<> struct getArrayType<int8_t>  : std::integral_constant<TagType, TagType::ByteArray> {};
template<> struct getArrayType<int32_t> : std::integral_constant<TagType, TagType::IntArray> {};
template<> struct getArrayType<int64_t> : std::integral_constant<TagType, TagType::LongArray> {};
} // namespace nbtinternal

template<class T>
class ArrayTag final : public CRTPTag<ArrayTag<T>> {
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator constIterator;

    typedef T ValueType;
    static constexpr TagType type = nbtinternal::getArrayType<T>::value;

    ArrayTag() {};
    explicit ArrayTag(std::initializer_list<T> init) : data(init) {}
    explicit ArrayTag(std::vector<T>&& vec) noexcept: data(std::move(vec)) {}

    std::vector<T>& get() { return data; }
    const std::vector<T>& get() const { return data; }

    T& at(size_t i) { return data.at(i); }
    T at(size_t i) const { return data.at(i); }

    T& operator[](size_t i) { return data[i]; }
    T operator[](size_t i) const { return data[i]; }

    void push_back(T val) { data.push_back(val); }
    void pop_back() { data.pop_back(); }
    size_t size() const { return data.size(); }
    void clear() { data.clear(); }

    iterator begin() { return data.begin(); }
    iterator end()   { return data.end(); }
    constIterator begin() const  { return data.begin(); }
    constIterator end() const    { return data.end(); }
    constIterator cbegin() const { return data.cbegin(); }
    constIterator cend() const   { return data.cend(); }

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;

private:
    std::vector<T> data;
};

template<class T> bool operator==(const ArrayTag<T>& lhs, const ArrayTag<T>& rhs) { return lhs.get() == rhs.get(); }
template<class T> bool operator!=(const ArrayTag<T>& lhs, const ArrayTag<T>& rhs) { return !(lhs == rhs); }

typedef ArrayTag<int8_t> ByteArrayTag;
typedef ArrayTag<int32_t> IntArrayTag;
typedef ArrayTag<int64_t> LongArrayTag;
} // namespace stratos

#endif //ARRAYTAG_H
