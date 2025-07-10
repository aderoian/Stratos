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

#ifndef HASH_H
#define HASH_H
#include <cstddef>
#include <vector>

namespace stratos::utils {
template<typename T> std::size_t hash(const std::vector<T>& vec) {
    constexpr std::hash<T> hasher;
    std::size_t seed = 0;
    for (const T& value : vec)
        seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}
}

#endif //HASH_H
