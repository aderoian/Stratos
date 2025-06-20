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

#include "Palette.h"

#include "utils/Validate.h"

#include <stdexcept>

namespace stratos {
Palette::Palette(const int bitsPerEntry, const int size) : Palette(bitsPerEntry, size, std::vector<int64_t>(0)) {}
Palette::Palette(const int bitsPerEntry, const int size, std::vector<int64_t>&& data) : bitsPerEntry(bitsPerEntry), size(size), elementsPerLong(64 / bitsPerEntry), maxValue((1LL << bitsPerEntry) - 1LL) {
    if (data.size() == 0) { // No data provided, initialize with zeros
        data.resize((size + elementsPerLong - 1) / elementsPerLong, 0LL);
    } else if (const int length = (size + elementsPerLong - 1) / elementsPerLong; data.size() != length) { // Check if the length matches the expected size
        throw std::invalid_argument("Invalid length given for palette data, expected " + std::to_string(length) + " but got " + std::to_string(data.size()));
    }
    this->data = std::move(data);
}
Palette::Palette(const int bitsPerEntry, const int size, const std::vector<int64_t>& data) : Palette(bitsPerEntry, size, std::vector(data)) {}
Palette::Palette(const int bitsPerEntry, const int size, const std::vector<int>& data) : Palette(bitsPerEntry, size) {
    int j;
    int i = 0;
    for (j = 0; j <= size - elementsPerLong; j += elementsPerLong) {
        int64_t value = 0;
        for (int k = elementsPerLong - 1; k >= 0; k--) {
            value <<= bitsPerEntry;
            value |= static_cast<int64_t>(data[j + k]) & maxValue;
        }
        this->data[i++] = value;
    }
    int l = size - j;
    if (l > 0) {
        int64_t value = 0;
        for (int k = l - 1; k >= 0; --k) {
            value <<= bitsPerEntry;
            value |= static_cast<int64_t>(data[j + k]) & maxValue;
        }
        this->data[i] = value;
    }
}
int Palette::getBitsPerEntry() const {
    return bitsPerEntry;
}
int Palette::getSize() const {
    return size;
}
int Palette::getMaxValue() const {
    return maxValue;
}
const std::vector<int64_t>& Palette::getData() const {
    return data;
}
int Palette::get(const int index) const {
    inclusiveBetween(0LL, size - 1LL, index);
    const int i = index / elementsPerLong;
    return data[i] >> ((index - i * elementsPerLong) * bitsPerEntry) & maxValue;
}
void Palette::set(const int index, const int value) {
    inclusiveBetween(0LL, size - 1LL, index);
    inclusiveBetween(0LL, maxValue, value);
    const int i = index / elementsPerLong;
    const int j = (index - i * elementsPerLong) * bitsPerEntry;
    data[i] = data[i] & (maxValue << j ^ 0xFFFFFFFFFFFFFFFFLL) | (static_cast<int64_t>(value) & maxValue) << j;
}
int Palette::swap(const int index, const int value) {
    inclusiveBetween(0LL, size - 1LL, index);
    inclusiveBetween(0LL, maxValue, value);
    const int     i       = index / elementsPerLong;
    const int64_t oldLong = data[i];
    const int     j       = (index - i * elementsPerLong) * bitsPerEntry;
    data[i]               = oldLong & (maxValue << j ^ 0xFFFFFFFFFFFFFFFFLL) | (static_cast<int64_t>(value) & maxValue) << j;
    return oldLong >> j & maxValue;
}
void Palette::writeIndices(std::vector<int>& data) const {
    data.resize(size);
    int64_t value;
    const int elements = this->data.size();
    int j = 0;
    int k;
    int l;
    for (k = 0; k < elements - 1; ++k) {
        value = this->data[k];
        for (l = 0; l < elementsPerLong; ++l) {
            data[j + l] = static_cast<int>(value & maxValue);
            value >>= bitsPerEntry;
        }
        j += elementsPerLong;
    }
    k = size - j;
    if (k > 0) {
        value = this->data[elements - 1];
        for (l = 0; l < k; ++l) {
            data[j + l] = static_cast<int>(value & maxValue);
            value >>= bitsPerEntry;
        }
    }
}
} // namespace stratos