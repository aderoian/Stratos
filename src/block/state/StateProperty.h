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
#include "magic_enum.hpp"
#include "utils/Hash.h"
#include "utils/StringUtils.h"

#include <algorithm>
#include <any>
#include <stdexcept>
#include <string>
#include <vector>

namespace stratos::block {

class IProperty {
public:
    virtual ~IProperty() = default;
    [[nodiscard]] virtual std::size_t hashCode() const = 0;
    [[nodiscard]] virtual std::string getName() const = 0;
    [[nodiscard]] virtual std::vector<std::any> getValuesAsAny() const = 0;
    [[nodiscard]] virtual size_t hashValue(const std::any& value) const = 0;
    [[nodiscard]] virtual std::string toString(const std::any& value) const = 0;
};

template <typename T>
class Property : public IProperty {
public:
    explicit Property(std::string name, const char* type) : name(std::move(name)), type(type) {}
    ~Property() override = default;

    [[nodiscard]] std::string getName() const override { return name; }

    [[nodiscard]] std::size_t hashCode() const override;
    [[nodiscard]] virtual bool testValue(const T& value) const = 0;
    [[nodiscard]] virtual std::vector<T> getValues() const = 0;
    [[nodiscard]] std::vector<std::any> getValuesAsAny() const override;
protected:
    [[nodiscard]] virtual std::size_t computeHashCode() const;
private:
    std::string name;
    const char* type;
};

class IntProperty final : public Property<int> {
public:
    [[nodiscard]] bool testValue(const int& value) const override;
    [[nodiscard]] std::vector<int> getValues() const override { return values; }
    [[nodiscard]] size_t hashValue(const std::any& value) const override;
    [[nodiscard]] std::string toString(const std::any& value) const override;
    static IntProperty* create(std::string name, int min, int max);
private:
    IntProperty(std::string name, int min, int max);

    int min;
    int max;
    std::vector<int> values;
};

class BooleanProperty final : public Property<bool> {
public:
    [[nodiscard]] bool testValue(const bool& value) const override { return true; }
    [[nodiscard]] std::vector<bool> getValues() const override { return values; }
    [[nodiscard]] size_t hashValue(const std::any& value) const override;
    [[nodiscard]] std::string toString(const std::any& value) const override;
    static BooleanProperty* create(std::string name);
private:
    explicit BooleanProperty(std::string name);
    static std::vector<bool> values;
};

template <typename T>
class EnumProperty final : public Property<T> {
public:
    [[nodiscard]] bool testValue(const T& value) const override;
    [[nodiscard]] std::vector<T> getValues() const override { return values; }
    [[nodiscard]] size_t hashValue(const std::any& value) const override;
    [[nodiscard]] std::string toString(const std::any& value) const override;
    static EnumProperty* create(const std::string& name, const std::initializer_list<T>& values);
private:
    explicit EnumProperty(const std::string& name, const std::initializer_list<T>& values);
    std::vector<T> values;
};
template <typename T> std::size_t Property<T>::hashCode() const {
    return computeHashCode();
}
template <typename T> std::vector<std::any> Property<T>::getValuesAsAny() const {
    std::vector<std::any> values;
    values.reserve(values.size());
    for (T value : getValues())
        values.emplace_back(std::move(value));
    return values;
}
template <typename T> std::size_t Property<T>::computeHashCode() const {
    return std::hash<std::string>()(name);
}
template <typename T> bool EnumProperty<T>::testValue(const T& value) const {
    return std::ranges::find(values, value) != values.end();
}
template <typename T> size_t EnumProperty<T>::hashValue(const std::any& value) const {
    return std::hash<std::string>()(toString(value));
}
template <typename T> std::string      EnumProperty<T>::toString(const std::any& value) const {
    return toLower(std::string(magic_enum::enum_name(std::any_cast<T>(value))));
}
template <typename T> EnumProperty<T>* EnumProperty<T>::create(const std::string& name, const std::initializer_list<T>& values) {
    if constexpr (sizeof(values) == 0) throw std::invalid_argument("EnumProperty must have at least one value.");
    return new EnumProperty(std::move(name), values);
}
template <typename T> EnumProperty<T>::EnumProperty(const std::string& name, const std::initializer_list<T>& values) : Property<T>(name, typeid(T).name()), values(values) {}

size_t hashPropertyValue(const std::any& value);
size_t hashPropertyValue(int value);
size_t hashPropertyValue(bool value);
} // namespace stratos::block

#endif //STATEPROPERTY_H
