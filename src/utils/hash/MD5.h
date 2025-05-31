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

#ifndef MD5_H
#define MD5_H
#include <array>
#include <cstdint>

namespace md5internal {
uint32_t leftRotate(uint32_t value, uint32_t shift);
void processBlock(const uint8_t block[64], uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);
}
namespace stratos {
std::array<uint8_t, 16> md5(const void* input, size_t length);
}

#endif //MD5_H
