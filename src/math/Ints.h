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

#ifndef INTS_H
#define INTS_H
#include <cstdint>

namespace stratos::math {
typedef int32_t int26_t; // 26-bit signed integer
typedef int16_t int12_t; // 12-bit signed integer

constexpr int26_t INT26_MIN = -(1 << 25);
constexpr int26_t INT26_MAX =  (1 << 25) - 1;
constexpr int12_t INT12_MIN = -(1 << 11);
constexpr int12_t INT12_MAX =  (1 << 11) - 1;

inline explicit operator int26_t(const int v) {
    if (v < INT26_MIN) return INT26_MIN;
    if (v > INT26_MAX) return INT26_MAX;
    return v;
}

inline explicit operator int26_t(const int64_t v) {
    if (v < INT26_MIN) return INT26_MIN;
    if (v > INT26_MAX) return INT26_MAX;
    return static_cast<int26_t>(v);
}

inline explicit operator int12_t(const int v) {
    if (v < INT12_MIN) return INT12_MIN;
    if (v > INT12_MAX) return INT12_MAX;
    return v;
}

inline explicit operator int12_t(const int64_t v) {
    if (v < INT12_MIN) return INT12_MIN;
    if (v > INT12_MAX) return INT12_MAX;
    return static_cast<int12_t>(v);
}
} // namespace stratos::math

#endif //INTS_H
