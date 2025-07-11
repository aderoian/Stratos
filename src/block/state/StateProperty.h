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

#include <algorithm>
#include <any>
#include <stdexcept>
#include <string>
#include <vector>

namespace stratos::block {

class Property {
   public:
     Property(std::string name, std::string type) : name(std::move(name)), type(std::move(type)) {}
     virtual ~Property() = default;

    [[nodiscard]] const std::string& getName() const { return name; }

     [[nodiscard]] std::size_t hashCode() const;
     [[nodiscard]] virtual bool testValue(const std::any& value) const = 0;

     template <typename T> T& as();
     template <typename T> const T& as() const;

    class Value {
    public:
        explicit Value(const Property* property);
        virtual ~Value() = default;
        [[nodiscard]] const Property* getProperty() const { return property; }
        [[nodiscard]] virtual std::size_t hashCode() const = 0;
        [[nodiscard]] virtual std::string toString() const;
    protected:
        const Property* property;
    };

   protected:
     [[nodiscard]] virtual std::size_t computeHashCode() const;
   private:
     std::string name;
     std::string type;
 };

class IntProperty final : public Property {
public:
    [[nodiscard]] bool testValue(const std::any& value) const override;
    static IntProperty* create(std::string name, int min, int max);

    class Value final : public Property::Value {
    public:
        Value(const IntProperty* property, int value);
        [[nodiscard]] std::size_t hashCode() const override;
        [[nodiscard]] int getValue() const;
        [[nodiscard]] std::string toString() const override;
    private:
        int value;
    };
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    IntProperty(std::string name, int min, int max);

    int min;
    int max;
    std::vector<int> values;
};

class BooleanProperty final : public Property {
public:
    [[nodiscard]] bool testValue(const std::any& value) const override;
    static BooleanProperty* create(std::string name);

    class Value final : public Property::Value {
    public:
        Value(const BooleanProperty* property, bool value);
        [[nodiscard]] std::size_t hashCode() const override;
        [[nodiscard]] bool getValue() const;
        [[nodiscard]] std::string toString() const override;
    private:
        bool value;
    };
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    explicit BooleanProperty(std::string name);
    static std::vector<bool> values;
};

template <typename T>
class EnumProperty final : public Property {
public:
    [[nodiscard]] bool testValue(const std::any& value) const override;
    template <typename... Args>
    static EnumProperty* create(std::string name, Args&&... values);

    class Value final : public Property::Value {
    public:
        Value(const EnumProperty* property, const T& value);
        [[nodiscard]] std::size_t hashCode() const override;
        [[nodiscard]] T getValue() const;
        [[nodiscard]] std::string toString() const override;
    private:
        T value;
    };
protected:
    [[nodiscard]] std::size_t computeHashCode() const override;
private:
    template <typename... Args>
    explicit EnumProperty(std::string name, Args&&... values);
    std::vector<T> values;
};
template <typename T> T& Property::as() {
    static_assert(std::is_base_of_v<Property, T>, "T must be a subclass of Property");
    return dynamic_cast<T&>(*this);
}
template <typename T> const T& Property::as() const {
    static_assert(std::is_base_of_v<Property, T>, "T must be a subclass of Property");
    return dynamic_cast<const T&>(*this);
}
template <typename T> bool EnumProperty<T>::testValue(const std::any& value) const {
    const T& enumValue = std::any_cast<T>(value);
    return std::ranges::find(values, enumValue) != values.end();
}
template <typename T> template <typename... Args> EnumProperty<T>* EnumProperty<T>::create(std::string name, Args&&... values) {
    static_assert((std::is_convertible_v<Args, T> && ...), "All arguments must be convertible to T");
    if constexpr (sizeof...(values) == 0) throw std::invalid_argument("EnumProperty must have at least one value.");
    return new EnumProperty(std::move(name), std::forward<Args>(values)...);
}
template <typename T> EnumProperty<T>::Value::Value(const EnumProperty* property, const T& value) : Value(property) {
    if (!property->testValue(value)) throw std::invalid_argument("Value is not valid for this EnumProperty.");
    this->value = value;
}
template <typename T> std::size_t EnumProperty<T>::Value::hashCode() const {
    return std::hash<T>()(value);
}
template <typename T> T EnumProperty<T>::Value::getValue() const {
    return value;
}
template <typename T> std::string EnumProperty<T>::Value::toString() const {
    return property->getName() + "=" + std::to_string(value);
}
template <typename T> std::size_t EnumProperty<T>::computeHashCode() const {
    return Property::computeHashCode() ^ utils::hash(values) << 1;
}
template <typename T> template <typename... Args> EnumProperty<T>::EnumProperty(std::string name, Args&&... values) : Property(std::move(name), typeid(T).name()), values(std::forward<Args>(values)...) {}
} // namespace stratos::block

#endif //STATEPROPERTY_H
