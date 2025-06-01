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

inline UUID UUIDFromString(const std::string& uuidStr) {
    UUID uuid = {};
    size_t index = 0;
    for (size_t i = 0; i < uuidStr.size(); ++i) {
        if (uuidStr[i] == '-') continue; // Skip dashes
        if (index >= uuid.size()) break; // Prevent overflow
        uuid[index++] = static_cast<uint8_t>(std::stoi(uuidStr.substr(i, 2), nullptr, 16));
        ++i; // Skip next character as well
    }
    return uuid;
}

inline std::string UUIDToString(const UUID& uuid, const bool dashes = true) {
    std::ostringstream oss;
    for (size_t i = 0; i < uuid.size(); ++i) {
        if (dashes && (i == 4 || i == 6 || i == 8 || i == 10))
            oss << '-';
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(uuid[i]);
    }
    return oss.str();
}
}

#endif //UUID_H
