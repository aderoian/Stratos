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

#ifndef PALETTESTORAGE_H
#define PALETTESTORAGE_H
#include <cstdint>
#include <vector>

namespace stratos {

/**
 * A container where each value is a raw ID which is held by some palette.
 */
class                               PalettedStorage {
public:
    virtual ~PalettedStorage() = default;

    /**
     * Each value is stored in a fixed number of bits, which does determine the maximum allowed value.
     * @see getMaxValue()
     * @return the number of bits used to store each value
     */
    [[nodiscard]] virtual int getBitsPerEntry() const = 0;
    /**
     * The number of values that can be stored in this container.
     * @return the size of the container
     */
    [[nodiscard]] virtual int getSize() const = 0;
    /**
     * The maximum value that can be stored in this container. Determined by the number of bits per entry.
     * @see getBitsPerEntry()
     * @return the maximum value
     */
    [[nodiscard]] virtual int getMaxValue() const = 0;
    /**
     * The raw data of the container, which is a vector of longs.
     * @return the data
     */
    [[nodiscard]] virtual const std::vector<int64_t>& getData() const = 0;

    /**
     * Gets the value at @code index@endcode.
     * @param index the index to get
     * @return the value at @code index@endcode
     */
    [[nodiscard]] int virtual get(int index) const = 0;
    /**
     * Sets the value at @code index@endcode to @code value@endcode.
     * @param index the index to set
     * @param value the value to set
     */
    void virtual set(int index, int value) = 0;
    /**
     * Swaps the value at @code index@endcode with @code value@endcode and returns the previous value.
     * @param index the index to swap
     * @param value the value to swap with
     * @return the previous value at @code index@endcode
     */
    [[nodiscard]] virtual int swap(int index, int value) = 0;

    /**
     * Writes all the indices of the container into the provided vector.
     * @param data the vector to write the indices to
     */
    virtual void writeIndices(std::vector<int>& data) const = 0;
};

/**
 * A container that stores integers in a packed format, where an array of integers is packed into an array of longs.
 */
class PackedIntegerArray final : public PalettedStorage {
public:
    PackedIntegerArray(int bitsPerEntry, int size);
    PackedIntegerArray(int bitsPerEntry, int size, std::vector<int64_t>&& data);
    PackedIntegerArray(int bitsPerEntry, int size, const std::vector<int64_t>& data);
    PackedIntegerArray(int bitsPerEntry, int size, const std::vector<int>& data);

    [[nodiscard]] int getBitsPerEntry() const override;
    [[nodiscard]] int getSize() const override;
    [[nodiscard]] int getMaxValue() const override;
    [[nodiscard]] const std::vector<int64_t>& getData() const override;
    [[nodiscard]] std::vector<int64_t>& getData();

    [[nodiscard]] int get(int index) const override;
    void set(int index, int value) override;
    [[nodiscard]] int swap(int index, int value) override;

    void writeIndices(std::vector<int>& data) const override;

private:
    int bitsPerEntry;
    int size;

    int elementsPerLong;
    int64_t maxValue;
    std::vector<int64_t> data;
};

class EmptyPalettedStorage final : public PalettedStorage {
public:
    explicit EmptyPalettedStorage(int size);

    [[nodiscard]] int getBitsPerEntry() const override;
    [[nodiscard]] int getSize() const override;
    [[nodiscard]] int getMaxValue() const override;
    [[nodiscard]] const std::vector<int64_t>& getData() const override;
    [[nodiscard]] std::vector<int64_t>& getData();

    [[nodiscard]] int get(int index) const override;
    void set(int index, int value) override;
    [[nodiscard]] int swap(int index, int value) override;

    void writeIndices(std::vector<int>& data) const override;
private:
    int size;
    std::vector<int64_t> empty;
};

} // namespace stratos

#endif //PALETTESTORAGE_H
