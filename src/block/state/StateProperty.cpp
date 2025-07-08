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
const std::vector<int>& IntProperty::getValues() const {
    return values;
}
IntProperty* IntProperty::create(std::string name, const int min, const int max) {
    if (min < 0) throw std::invalid_argument("Minimum value must be non-negative.");
    if (min >= max) throw std::invalid_argument("Minimum value must be less than maximum value.");
    return new IntProperty(std::move(name), min, max);
}
std::size_t IntProperty::computeHashCode() const {
    return Property::computeHashCode() ^ utils::hash(values) << 1;
}
IntProperty::IntProperty(std::string name, const int min, const int max) : Property(std::move(name), typeid(int).name()), min(min), max(max) {
    values = std::vector<int>(max - min);
    for (int i = min; i < max; ++i) values[i - min] = i;
}
std::vector<bool> BooleanProperty::values = { false, true };
const std::vector<bool>& BooleanProperty::getValues() const {
    return values;
}
BooleanProperty* BooleanProperty::create(std::string name) {
    return new BooleanProperty(std::move(name));
}
std::size_t BooleanProperty::computeHashCode() const {
    return Property::computeHashCode() ^ 0x1;
}
BooleanProperty::BooleanProperty(std::string name) : Property(std::move(name), typeid(bool).name()) {}
}// namespace stratos::block