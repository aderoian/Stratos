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

#ifndef STRINGTAG_H
#define STRINGTAG_H
#include "Tag.h"

namespace stratos::nbt {
class StringTag final : public CRTPTag<StringTag> {
  public:
    static constexpr auto type = TagType::String;

    StringTag() = default;
    explicit StringTag(const std::string& str) : value(str) {}
    explicit StringTag(std::string&& str) noexcept : value(std::move(str)) {}
    explicit StringTag(const char* str) : value(str) {}

    explicit           operator std::string&() { return value; }
    explicit           operator const std::string&() const { return value; }
    [[nodiscard]] const std::string& get() const { return value; }

    StringTag& operator=(const std::string& str) {
        value = str;
        return *this;
    }
    StringTag& operator=(std::string&& str) {
        value = std::move(str);
        return *this;
    }
    StringTag& operator=(const char* str) {
        value = str;
        return *this;
    }
    void set(const std::string& str) { value = str; }
    void set(std::string&& str) { value = std::move(str); }

    void read(NBTBuffer& buffer) override;
    void write(NBTBuffer& buffer) const override;

  private:
    std::string value;
};

inline bool operator==(const StringTag& lhs, const StringTag& rhs) { return lhs.get() == rhs.get(); }
inline bool operator!=(const StringTag& lhs, const StringTag& rhs) { return !(lhs == rhs); }
} // namespace stratos::nbt

#endif //STRINGTAG_H
