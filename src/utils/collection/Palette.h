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

#ifndef PALETTE_H
#define PALETTE_H
#include <cstdint>
#include <vector>

namespace stratos {

class Palette {
public:
    Palette(int bitsPerEntry, int size);
    Palette(int bitsPerEntry, int size, std::vector<int64_t>&& data);
    Palette(int bitsPerEntry, int size, const std::vector<int64_t>& data);
    Palette(int bitsPerEntry, int size, const std::vector<int>& data);

    [[nodiscard]] int getBitsPerEntry() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] int getMaxValue() const;
    [[nodiscard]] const std::vector<int64_t>& getData() const;

    [[nodiscard]] int get(int index) const;
    void set(int index, int value);
    [[nodiscard]] int swap(int index, int value);

    void writeIndices(std::vector<int>& data) const;

private:
    int bitsPerEntry;
    int size;

    int elementsPerLong;
    int64_t maxValue;
    std::vector<int64_t> data;
};

} // stratos

#endif //PALETTE_H
