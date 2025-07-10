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

#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include <string>

namespace stratos::utils {
struct Identifier {
    std::string namespaceName;
    std::string name;

    Identifier(std::string ns, std::string n) : namespaceName(std::move(ns)), name(std::move(n)) {}

    [[nodiscard]] std::string toString() const;

    bool operator==(const Identifier& other) const;
    bool operator!=(const Identifier& other) const;
};
} // namespace stratos::utils

template <> struct std::hash<stratos::utils::Identifier> {
    std::size_t operator()(const stratos::utils::Identifier& id) const noexcept { return std::hash<std::string>()(id.namespaceName) ^ std::hash<std::string>()(id.name) << 1; }
};
#endif //IDENTIFIER_H
