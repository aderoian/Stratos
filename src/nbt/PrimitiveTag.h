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

#ifndef PRIMITIVETAG_H
#define PRIMITIVETAG_H
#include "Tag.h"
#include <type_traits>

namespace stratos {
namespace nbtinternal {
template<class T> struct getPrimitiveType { static_assert(sizeof(T) != sizeof(T), "Invalid type parameter for tag_primitive, can only use types that NBT uses"); };
template<> struct getPrimitiveType<std::int8_t>  : std::integral_constant<TagType, TagType::Byte> {};
template<> struct getPrimitiveType<int16_t> : std::integral_constant<TagType, TagType::Short> {};
template<> struct getPrimitiveType<int32_t> : std::integral_constant<TagType, TagType::Int> {};
template<> struct getPrimitiveType<int64_t> : std::integral_constant<TagType, TagType::Long> {};
template<> struct getPrimitiveType<float>   : std::integral_constant<TagType, TagType::Float> {};
template<> struct getPrimitiveType<double>  : std::integral_constant<TagType, TagType::Double> {};
}

template<class T>
class PrimitiveTag final : CRTPTag<PrimitiveTag<T>> {
public:
    typedef T ValueType; // The type of the value stored in this tag

    static constexpr TagType type = nbtinternal::getPrimitiveType<T>::value;

    explicit constexpr PrimitiveTag(T val = 0) noexcept : value(val) {}

    explicit operator T&() { return value; }
    explicit constexpr operator T() const { return value; }
    constexpr T get() const { return value; }

    PrimitiveTag& operator=(T val) { value = val; return *this; }
    void set(T val) { value = val; }

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
private:
    T value;
};

template<class T> bool operator==(const PrimitiveTag<T>& lhs, const PrimitiveTag<T>& rhs) { return lhs.get() == rhs.get(); }
template<class T> bool operator!=(const PrimitiveTag<T>& lhs, const PrimitiveTag<T>& rhs) { return !(lhs == rhs); }

typedef PrimitiveTag<int8_t> ByteTag;
typedef PrimitiveTag<int16_t> ShortTag;
typedef PrimitiveTag<int32_t> IntTag;
typedef PrimitiveTag<int64_t> LongTag;
typedef PrimitiveTag<float> FloatTag;
typedef PrimitiveTag<double> DoubleTag;

template <class T>
void PrimitiveTag<T>::read(ByteBuffer& buffer) {
    // TODO: we need overload methods
}
template <class T>
void PrimitiveTag<T>::write(ByteBuffer& buffer) const {
    // TODO: we need overload methods
}
} // namespace stratos

#endif //PRIMITIVETAG_H
