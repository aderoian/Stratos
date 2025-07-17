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

#ifndef IDLIST_H
#define IDLIST_H
#include "Iterable.h"

#include <unordered_map>

namespace stratos::utils {
template <typename T> class IdList final : public IndexedIterable<T> {
  public:
    explicit IdList(int size = 512);
    ~IdList() override = default;

    int  getRawIndex(T value) const override;
    T    get(int index) const override;
    void set(T value, int id);
    void add(T value);

    [[nodiscard]] int size() const override;

    typename IndexedIterable<T>::iterator       begin() override;
    typename IndexedIterable<T>::const_iterator begin() const override;
    typename IndexedIterable<T>::iterator       end() override;
    typename IndexedIterable<T>::const_iterator end() const override;

  private:
    int                        nextId = 0;
    std::vector<T>             data;
    std::unordered_map<T, int> idMap;
};
template <typename T> IdList<T>::IdList(int size) : data(size), idMap() {}
template <typename T> int IdList<T>::getRawIndex(T value) const {
    auto it = idMap.find(value);
    if (it != idMap.end()) return it->second;
    return -1;
}
template <typename T> T IdList<T>::get(int index) const {
    if (index < 0 || index >= static_cast<int>(data.size())) throw std::out_of_range(std::format("Index {} out of bounds for size {}", index, data.size()));
    return data[index];
}
template <typename T> void IdList<T>::set(T value, int id) {
    if (id < data.capacity()) data.resize(id + 1);
    if (std::is_pointer_v<T>)
        while (data.size() <= id) data.emplace_back(nullptr);
    else
        while (data.size() <= id) data.emplace_back(T(value));
    nextId = id+1;
    data[id] = value;
    idMap[value] = id;
}
template <typename T> void IdList<T>::add(T value) {
    set(value, nextId);
}
template <typename T> int IdList<T>::size() const {
    return static_cast<int>(data.size());
}
template <typename T> typename IndexedIterable<T>::iterator IdList<T>::begin() {
    return data.begin();
}
template <typename T> typename IndexedIterable<T>::const_iterator IdList<T>::begin() const {
    return data.begin();
}
template <typename T> typename IndexedIterable<T>::iterator IdList<T>::end() {
    return data.end();
}
template <typename T> typename IndexedIterable<T>::const_iterator IdList<T>::end() const {
    return data.end();
}
} // namespace stratos::utils

#endif //IDLIST_H
