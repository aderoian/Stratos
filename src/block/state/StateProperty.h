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

#ifndef STATEPROPERTY_H
#define STATEPROPERTY_H
#include "utils/Hash.h"

#include <stdexcept>
#include <string>
#include <array>
#include <vector>

namespace stratos::block {

template <typename T> class Property {
  public:
    Property(std::string name, std::string type) : name(std::move(name)), type(std::move(type)) {}
    virtual ~Property() = default;

    [[nodiscard]] std::size_t hashCode() const;
    [[nodiscard]] virtual const std::vector<T>& getValues() const = 0;
  protected:
    [[nodiscard]] virtual std::size_t computeHashCode() const;
  private:
    std::string name;
    std::string type;
    int         hashCodeCache = -1;
};

class IntProperty final : public Property<int> {
public:
    [[nodiscard]] const std::vector<int>& getValues() const override;
    static IntProperty* create(std::string name, int min, int max);
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    IntProperty(std::string name, int min, int max);

    int min;
    int max;
    std::vector<int> values;
};

class BooleanProperty final : public Property<bool> {
public:
    [[nodiscard]] const std::vector<bool>& getValues() const override;
    static BooleanProperty* create(std::string name);
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    explicit BooleanProperty(std::string name);
    static std::vector<bool> values;
};

template <typename T>
class EnumProperty final : public Property<T> {
public:
    const std::vector<T>& getValues() const override;
    template <typename... Args>
    static EnumProperty* create(std::string name, Args&&... values);
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    template <typename... Args>
    explicit EnumProperty(std::string name, Args&&... values);
    std::vector<T> values;
};

template <typename T> std::size_t Property<T>::hashCode() const {
    if (hashCodeCache == -1)
        hashCodeCache = computeHashCode();
    return hashCodeCache;
}
template <typename T> std::size_t Property<T>::computeHashCode() const {
    return std::hash<std::string>()(name) ^ std::hash<std::string>()(type) << 1;
}
template <typename T> const std::vector<T>& EnumProperty<T>::getValues() const {
    return values;
}
template <typename T> template <typename... Args> EnumProperty<T>* EnumProperty<T>::create(std::string name, Args&&... values) {
    static_assert((std::is_convertible_v<Args, T> && ...), "All arguments must be convertible to T");
    if constexpr (sizeof...(values) == 0) throw std::invalid_argument("EnumProperty must have at least one value.");
    return new EnumProperty(std::move(name), std::forward<Args>(values)...);
}
template <typename T> std::size_t EnumProperty<T>::computeHashCode() const {
    return Property<T>::computeHashCode() ^ utils::hash(values) << 1;
}
template <typename T> template <typename... Args> EnumProperty<T>::EnumProperty(std::string name, Args&&... values) : Property<T>(std::move(name), typeid(T).name()), values(std::forward<Args>(values)...) {}
} // namespace stratos::block

#endif //STATEPROPERTY_H
