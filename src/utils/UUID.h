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

#ifndef UUID_H
#define UUID_H
#include "hash/MD5.h"

#include <array>
#include <cstdint>
#include <string>

namespace stratos {
using UUID = std::array<uint8_t, 16>;
inline UUID generateOfflineUUID(const std::string& username) {
    const std::string data = "OfflinePlayer:" + username;
    auto hash = md5(data.data(), data.size());
    hash[6] = (hash[6] & 0x0F) | 0x30;
    hash[8] = (hash[8] & 0x3F) | 0x80;
    return hash;
}
}

#endif //UUID_H
