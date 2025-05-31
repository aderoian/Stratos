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

#ifndef TYPES_H
#define TYPES_H
#include <optional>
#include <string>

namespace stratos {

struct Identifier {
    std::string namespaceName;
    std::string name;

    Identifier(std::string ns, std::string n) : namespaceName(std::move(ns)), name(std::move(n)) {}

    bool operator==(const Identifier& other) const {
        return namespaceName == other.namespaceName && name == other.name;
    }

    bool operator!=(const Identifier& other) const {
        return !(*this == other);
    }
};

struct LoginProperty {
    std::string name; // String(16)
    std::string value; // String(32767)
    std::optional<std::string> signature; // String(1024), prefixed optional
};

}
#endif //TYPES_H
