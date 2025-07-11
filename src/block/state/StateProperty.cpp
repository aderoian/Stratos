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

#include "StateProperty.h"

namespace stratos::block {
std::size_t Property::hashCode() const {
    return computeHashCode();
}
Property::Value::Value(const Property* property) : property(property) {}
std::string Property::Value::toString() const { return "Property=Value"; }
std::size_t Property::computeHashCode() const {
    return std::hash<std::string>()(name) ^ std::hash<std::string>()(type) << 1;
}
bool IntProperty::testValue(const std::any& value) const {
    const int intValue = std::any_cast<int>(value);
    return intValue >= min && intValue < max;
}
IntProperty* IntProperty::create(std::string name, const int min, const int max) {
    if (min < 0) throw std::invalid_argument("Minimum value must be non-negative.");
    if (min >= max) throw std::invalid_argument("Minimum value must be less than maximum value.");
    return new IntProperty(std::move(name), min, max);
}
IntProperty::Value::Value(const IntProperty* property, const int value) : Property::Value(property), value(value) {
    if (!property->testValue(value)) throw std::out_of_range("Value is out of range for this IntProperty.");
}
std::size_t IntProperty::Value::hashCode() const {
    return std::hash<int>()(value);
}
int IntProperty::Value::getValue() const {
    return value;
}
std::string IntProperty::Value::toString() const {
    return property->getName() + "=" + std::to_string(value);
}
std::size_t IntProperty::computeHashCode() const {
    return Property::computeHashCode() ^ utils::hash(values) << 1;
}
IntProperty::IntProperty(std::string name, const int min, const int max) : Property(std::move(name), typeid(int).name()), min(min), max(max) {
    values = std::vector<int>(max - min);
    for (int i = min; i < max; ++i) values[i - min] = i;
}
std::vector<bool> BooleanProperty::values = {false, true};
bool BooleanProperty::testValue(const std::any& value) const {
    const bool boolValue = std::any_cast<bool>(value);
    return std::ranges::find(values, boolValue) != values.end();
}
BooleanProperty* BooleanProperty::create(std::string name) {
    return new BooleanProperty(std::move(name));
}
BooleanProperty::Value::Value(const BooleanProperty* property, bool value) : Property::Value(property), value(value) {
    if (!property->testValue(value)) throw std::invalid_argument("Value is not valid for this BooleanProperty.");
}
std::size_t BooleanProperty::Value::hashCode() const {
    return std::hash<bool>()(value);
}
bool BooleanProperty::Value::getValue() const {
    return value;
}
std::string BooleanProperty::Value::toString() const {
    return property->getName() + "=" + std::to_string(value);
}
std::size_t BooleanProperty::computeHashCode() const {
    return Property::computeHashCode() ^ utils::hash(values) << 1;
}
BooleanProperty::BooleanProperty(std::string name) : Property(std::move(name), typeid(bool).name()) {}
}// namespace stratos::block