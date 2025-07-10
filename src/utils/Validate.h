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

#ifndef VALIDATE_H
#define VALIDATE_H
#include <stdexcept>

namespace stratos {

class ValidateException final : public std::runtime_error {
  public:
    explicit ValidateException(const std::string& __arg) : runtime_error(__arg) {}
    explicit ValidateException(const char* string) : runtime_error(string) {}
};

template <typename T, typename U, typename V> void inclusiveBetween(T min, U max, V value) {
    if (!(value >= min && value <= max))
        throw ValidateException("Value is out of range");
}

template <typename T, typename U, typename V> void exclusiveBetween(T min, U max, V value) {
    if (!(value > min && value < max))
        throw ValidateException("Value is out of range");
}

} // namespace stratos

#endif //VALIDATE_H
