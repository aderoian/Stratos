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

#ifndef TAG_H
#define TAG_H
#include <cstdint>
#include <memory>

namespace stratos::nbt {
class NBTBuffer;

enum class TagType : std::int8_t {
    End = 0,
    Byte = 1,
    Short = 2,
    Int = 3,
    Long = 4,
    Float = 5,
    Double = 6,
    ByteArray = 7,
    String = 8,
    List = 9,
    Compound = 10,
    IntArray = 11,
    LongArray = 12,
    Null = -1
};

bool isValidType(int type, bool allowEnd = false);

namespace internal {
template<class T, class... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // namespace stratos::nbt::internal

class Tag {
public:
    virtual ~Tag() = default;
    [[nodiscard]] virtual TagType getType() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Tag> clone() const& = 0;
    virtual std::unique_ptr<Tag> moveClone() && = 0;
    std::unique_ptr<Tag> clone() &&;

    template<class T>
    T& as();
    template<class T>
    const T& as() const;

    virtual Tag& assign(Tag&& rhs) = 0;

    virtual void read(const NBTBuffer& buffer) = 0;
    virtual void write(NBTBuffer& buffer) const = 0;

    static std::unique_ptr<Tag> create(TagType type);

    friend bool operator==(const Tag& lhs, const Tag& rhs);
    friend bool operator!=(const Tag& lhs, const Tag& rhs);

private:
    [[nodiscard]] virtual bool equals(const Tag& other) const = 0;
};

template<class T>
T& Tag::as() {
    static_assert(std::is_base_of_v<Tag, T>, "T must be a subclass of Tag");
    return dynamic_cast<T&>(*this);
}
template<class T>
const T& Tag::as() const {
    static_assert(std::is_base_of_v<Tag, T>, "T must be a subclass of Tag");
    return dynamic_cast<const T&>(*this);
}

template <class Sub>
class CRTPTag : public Tag {
public:
    ~CRTPTag() noexcept override = default; // Ensure CRTPTag is abstract
    [[nodiscard]] TagType getType() const noexcept final { return Sub::type; }

    [[nodiscard]] std::unique_ptr<Tag> clone() const& final { return internal::makeUnique<Sub>(SubThis()); }
    std::unique_ptr<Tag> moveClone() && final { return internal::makeUnique<Sub>(std::move(SubThis())); }

    Tag& assign(Tag&& rhs) final { return SubThis() = dynamic_cast<Sub&&>(rhs); }

private:
    [[nodiscard]] bool equals(const Tag& rhs) const final { return SubThis() == static_cast<const Sub&>(rhs); }

    Sub& SubThis() { return static_cast<Sub&>(*this); }
    const Sub& SubThis() const { return static_cast<const Sub&>(*this); }
};
} // namespace stratos::nbt

#endif //TAG_H
