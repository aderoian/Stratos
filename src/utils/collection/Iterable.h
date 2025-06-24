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

#ifndef ITERABLE_H
#define ITERABLE_H
#include <format>
#include <stdexcept>

namespace stratos::utils {

template <typename T> class Iterable<T> {
  public:
    virtual ~Iterable() = default;
    virtual T* begin()  = 0;
    virtual T* end()    = 0;
};

template <typename T> class IndexedIterable<T> : public Iterable<T> {
  public:
    ~IndexedIterable() override            = default;
    virtual int getRawIndex(T value) const = 0;
    virtual T   get(int index) const       = 0;

    T   getOrThrow(int index) const;
    int getRawIndexOrThrow(T value) const;

    virtual int size() const = 0;
};
template <typename T> T IndexedIterable<T>::getOrThrow(int index) const {
    if (index < 0 || index >= size()) throw std::out_of_range(std::format("Index {} out of bounds for size {}", index, size()));
    return get(index);
}
template <typename T> int IndexedIterable<T>::getRawIndexOrThrow(T value) const {
    const int i = getRawIndex(value);
    if (i < 0 || i >= size()) throw std::out_of_range(std::format("Tried to get the raw index of a element not present.", value));
    return i;
}

} // namespace stratos::utils

#endif // ITERABLE_H
