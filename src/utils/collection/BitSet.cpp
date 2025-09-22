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

#include "BitSet.h"

namespace stratos::utils {
BitSet::BitSet(const int size) : data(size) {}
BitSet::BitSet(const std::vector<int64_t>& data) : data(data) {}
bool BitSet::get(const int index) const {
    return (data[wordIndex(index)] & 1L << (index & (BITS_PER_LONG - 1))) != 0;
}
void BitSet::set(const int index) {
    data[wordIndex(index)] |= 1L << (index & (BITS_PER_LONG - 1));
}
void BitSet::set(const int index, const bool value) {
    value ? set(index) : clear(index);
}
void BitSet::clear(const int index) {
    data[wordIndex(index)] &= ~(1L << (index & (BITS_PER_LONG - 1)));
}
size_t BitSet::size() const {
    return data.size();
}
std::vector<int64_t> BitSet::toVector() const {
    return data;
}
int BitSet::wordIndex(const int index) {
    return index >> ADDRESS_BITS;
}
} // namespace stratos::utils