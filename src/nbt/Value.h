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

#ifndef NBTVALUE_H
#define NBTVALUE_H
#include "Tag.h"

namespace stratos {

class TagValue {
public:
    TagValue() noexcept = default;
    explicit TagValue(std::unique_ptr<Tag>&& t) noexcept: tag(std::move(t)) {}
    explicit TagValue(Tag&& t);

    TagValue(TagValue&&) noexcept = default;
    TagValue& operator=(TagValue&&) noexcept = default;

    TagValue(const TagValue& rhs);
    TagValue& operator=(const TagValue& rhs);

    TagValue& operator=(Tag&& t);
    void      set(Tag&& t);

    explicit operator Tag&() { return get(); }
    explicit operator const Tag&() const { return get(); }
    Tag& get() { return *tag; }
    [[nodiscard]] const Tag& get() const { return *tag; }

    template<class T>
    T& as();
    template<class T>
    const T& as() const;

    TagValue& operator=(int8_t val);
    TagValue& operator=(int16_t val);
    TagValue& operator=(int32_t val);
    TagValue& operator=(int64_t val);
    TagValue& operator=(float val);
    TagValue& operator=(double val);

    TagValue& operator=(const std::string& str);
    TagValue& operator=(std::string&& str);

    explicit operator int8_t() const;
    explicit operator int16_t() const;
    explicit operator int32_t() const;
    explicit operator int64_t() const;
    explicit operator float() const;
    explicit operator double() const;

    explicit operator const std::string&() const;

    explicit operator bool() const { return tag != nullptr; }

    TagValue& at(const std::string& key);
    [[nodiscard]] const TagValue& at(const std::string& key) const;

    TagValue& operator[](const std::string& key);
    TagValue& operator[](const char* key); //need this overload because of conflict with built-in operator[]

    TagValue& at(size_t i);
    [[nodiscard]] const TagValue& at(size_t i) const;

    TagValue& operator[](size_t i);
    const TagValue& operator[](size_t i) const;

    std::unique_ptr<Tag>& get_ptr() { return tag; }
    [[nodiscard]] const std::unique_ptr<Tag>& get_ptr() const { return tag; }
    void set_ptr(std::unique_ptr<Tag>&& t) { tag = std::move(t); }

    [[nodiscard]] TagType getType() const;

    friend bool operator==(const TagValue& lhs, const TagValue& rhs);
    friend bool operator!=(const TagValue& lhs, const TagValue& rhs);

private:
    std::unique_ptr<Tag> tag;
};

template<class T>
T& TagValue::as() { return tag->as<T>(); }

template<class T>
const T& TagValue::as() const { return tag->as<T>(); }

class TagValueInitializer : public TagValue {
public:
    explicit TagValueInitializer(std::unique_ptr<Tag>&& t) noexcept: TagValue(std::move(t)) {}
    explicit TagValueInitializer(std::nullptr_t) noexcept : TagValue(nullptr) {}
    explicit TagValueInitializer(TagValue&& val) noexcept : TagValue(std::move(val)) {}
    explicit TagValueInitializer(Tag&& t) : TagValue(std::move(t)) {}

    explicit TagValueInitializer(int8_t val);
    explicit TagValueInitializer(int16_t val);
    explicit TagValueInitializer(int32_t val);
    explicit TagValueInitializer(int64_t val);
    explicit TagValueInitializer(float val);
    explicit TagValueInitializer(double val);
    explicit TagValueInitializer(const std::string& str);
    explicit TagValueInitializer(std::string&& str);
    explicit TagValueInitializer(const char* str);
};
} // namespace stratos

#endif //NBTVALUE_H
