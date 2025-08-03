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

#ifndef BITSET_H
#define BITSET_H
#include <cstdint>
#include <vector>

namespace stratos::utils {
class BitSet {
public:
    BitSet() = default;
    explicit BitSet(int size);
    explicit BitSet(const std::vector<int64_t>& data);

    [[nodiscard]] bool get(int index) const;
    void set(int index);
    void set(int index, bool value);
    void clear(int index);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::vector<int64_t> toVector() const;
private:
    static constexpr int BITS_PER_LONG = 64;
    static constexpr int ADDRESS_BITS = 6; // log2(BITS_PER_LONG)

    static int wordIndex(int index);

    std::vector<int64_t> data;
};
}

#endif //BITSET_H
