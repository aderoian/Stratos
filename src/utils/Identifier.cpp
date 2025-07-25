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

#include "Identifier.h"

namespace stratos::utils {

std::string Identifier::toString() const {
    return namespaceName + ":" + name;
}
bool Identifier::operator==(const Identifier& other) const {
    return namespaceName == other.namespaceName && name == other.name;
}
bool Identifier::operator!=(const Identifier& other) const {
    return !(*this == other);
}
Identifier Identifier::of(const std::string& identifier) {
    const size_t pos = identifier.find(':');
    if (pos == std::string::npos)
        throw std::invalid_argument("Invalid identifier format, expected 'namespace:name'");
    return {identifier.substr(0, pos), identifier.substr(pos + 1)};
}
} // namespace stratos::utils