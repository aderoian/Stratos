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
#include "io/NBTBuffer.h"
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
class PrimitiveTag final : public CRTPTag<PrimitiveTag<T>> {
public:
    typedef T ValueType; // The type of the value stored in this tag

    static constexpr TagType type = nbtinternal::getPrimitiveType<T>::value;

    explicit constexpr PrimitiveTag(T val = 0) noexcept : value(val) {}

    explicit operator T&() { return value; }
    explicit constexpr operator T() const { return value; }
    constexpr T get() const { return value; }

    PrimitiveTag& operator=(T val) { value = val; return *this; }
    void set(T val) { value = val; }

    void read(NBTBuffer& buffer) override;
    void write(NBTBuffer& buffer) const override;
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
void PrimitiveTag<T>::read(NBTBuffer& buffer) {
    if constexpr (std::is_same_v<T, int8_t>) {\
        value = buffer.readByte();
    } else if constexpr (std::is_same_v<T, int16_t>) {
        value = buffer.readShort();
    } else if constexpr (std::is_same_v<T, int32_t>) {
        value = buffer.readInt();
    } else if constexpr (std::is_same_v<T, int64_t>) {
        value = buffer.readLong();
    } else if constexpr (std::is_same_v<T, float>) {
        value = buffer.readFloat();
    } else if constexpr (std::is_same_v<T, double>) {
        value = buffer.readDouble();
    } else {
        static_assert(std::is_same_v<T, void>, "Unsupported primitive type for NBT");
    }
}
template <class T>
void PrimitiveTag<T>::write(NBTBuffer& buffer) const {
    if constexpr (std::is_same_v<T, int8_t>) {
        buffer.writeByte(value);
    } else if constexpr (std::is_same_v<T, int16_t>) {
        buffer.writeShort(value);
    } else if constexpr (std::is_same_v<T, int32_t>) {
        buffer.writeInt(value);
    } else if constexpr (std::is_same_v<T, int64_t>) {
        buffer.writeLong(value);
    } else if constexpr (std::is_same_v<T, float>) {
        buffer.writeFloat(value);
    } else if constexpr (std::is_same_v<T, double>) {
        buffer.writeDouble(value);
    } else {
        static_assert(std::is_same_v<T, void>, "Unsupported primitive type for NBT");
    }
}
} // namespace stratos

#endif //PRIMITIVETAG_H
