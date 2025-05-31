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

#include "MD5.h"

#include <cstring>
#include <vector>

uint32_t md5internal::leftRotate(const uint32_t value, const uint32_t shift) {
    return (value << shift) | (value >> (32 - shift));
}
void md5internal::processBlock(const uint8_t block[64], uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D) {
    uint32_t a = A, b = B, c = C, d = D;

    uint32_t M[16];
    for (int i = 0; i < 16; ++i)
        M[i] = static_cast<uint32_t>(block[i * 4]) | (static_cast<uint32_t>(block[i * 4 + 1]) << 8) | (static_cast<uint32_t>(block[i * 4 + 2]) << 16) |
               (static_cast<uint32_t>(block[i * 4 + 3]) << 24);

    for (int i = 0; i < 64; ++i) {
        constexpr uint32_t s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
        constexpr uint32_t K[64] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122,
            0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6,
            0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
            0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
        };
        uint32_t F, g;
        if (i < 16) {
            F = b & c | ~b & d;
            g = i;
        } else if (i < 32) {
            F = d & b | ~d & c;
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            F = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        } else {
            F = c ^ (b | ~d);
            g = 7 * i % 16;
        }
        F = F + a + K[i] + M[g];
        a = d;
        d = c;
        c = b;
        b = b + leftRotate(F, s[i]);
    }

    A += a;
    B += b;
    C += c;
    D += d;
}

std::array<uint8_t, 16> stratos::md5(const void* input, const size_t length) {
    using namespace md5internal;
    const auto           data      = static_cast<const uint8_t*>(input);
    const uint64_t       totalBits = length * 8;

    const size_t paddedLength = ((length + 8) / 64 + 1) * 64;
    std::vector<uint8_t> buffer(paddedLength, 0);
    std::memcpy(buffer.data(), data, length);
    buffer[length] = 0x80;
    for (int i = 0; i < 8; ++i)
        buffer[paddedLength - 8 + i] = static_cast<uint8_t>((totalBits >> (i * 8)) & 0xFF);

    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;
    for (size_t i = 0; i < paddedLength; i += 64)
        processBlock(buffer.data() + i, A, B, C, D);

    std::array<uint8_t, 16> result;
    for (int i = 0; i < 4; ++i) {
        result[i]      = (A >> (i * 8)) & 0xFF;
        result[i + 4]  = (B >> (i * 8)) & 0xFF;
        result[i + 8]  = (C >> (i * 8)) & 0xFF;
        result[i + 12] = (D >> (i * 8)) & 0xFF;
    }

    return result;
}