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

#ifndef REGISTRY_H
#define REGISTRY_H
#include "utils/collection/Iterable.h"
#include "utils/Types.h"

#include <unordered_map>

namespace stratos::registry {
struct RegistryKey {
    Identifier registry;
    Identifier value;

    bool operator==(const RegistryKey& other) const;
    bool operator!=(const RegistryKey& other) const;

    std::string toString() const;
};

template <typename T> class Registry<T> final : public utils::IndexedIterable<T> {
  public:
    explicit Registry(const RegistryKey& key) : key(key) {}
    const RegistryKey& getKey() const;

    int getRawIndex(T value) const override;
    T   get(int index) const override;
    T   get(Identifier key) const;
    T   get(RegistryKey key) const;
    int size() const override;

    void registerEntry(const RegistryKey& key, const T& value);

    typename utils::IndexedIterable<T>::iterator       begin() override;
    typename utils::IndexedIterable<T>::const_iterator begin() const override;
    typename utils::IndexedIterable<T>::iterator       end() override;
    typename utils::IndexedIterable<T>::const_iterator end() const override;

  private:
    int nextId = 0;
    RegistryKey key;

    std::vector<T>                     rawIdToValue;
    std::unordered_map<Identifier, T>  idToValue;
    std::unordered_map<RegistryKey, T> keyToValue;
    std::unordered_map<T*, int>        valueToRawId;
};
template <typename T> const RegistryKey& Registry<T>::getKey() const {
    return key;
}
template <typename T> int Registry<T>::getRawIndex(T value) const {
    auto el = valueToRawId.find(value);
    return el != end() ? el->second : -1;
}
template <typename T> T Registry<T>::get(int index) const {
    return rawIdToValue[index];
}
template <typename T> T Registry<T>::get(Identifier key) const {
    return idToValue[getRawIndex(key)];
}
template <typename T> T Registry<T>::get(RegistryKey key) const {
    return keyToValue[key];
}
template <typename T> int Registry<T>::size() const {
    return rawIdToValue.size();
}
template <typename T> void Registry<T>::registerEntry(const RegistryKey& key, const T& value) {
    if (key != this->key)
        throw std::invalid_argument("Registry key mismatch: expected " + this->key.registry.toString() + ", got " + key.registry.toString());
    int id = nextId++;
    rawIdToValue[id] = value;
    idToValue[key.value] = value;
    keyToValue[key] = value;
    valueToRawId[&rawIdToValue[id]] = id;
}
template <typename T> typename utils::IndexedIterable<T>::iterator Registry<T>::begin() {
    return utils::IndexedIterable<T>::iterator(rawIdToValue.begin());
}
template <typename T> typename utils::IndexedIterable<T>::const_iterator Registry<T>::begin() const {
    return utils::IndexedIterable<T>::const_iterator(rawIdToValue.cbegin());
}
template <typename T> typename utils::IndexedIterable<T>::iterator Registry<T>::end() {
    return utils::IndexedIterable<T>::iterator(rawIdToValue.end());
}
template <typename T> typename utils::IndexedIterable<T>::const_iterator Registry<T>::end() const {
    return utils::IndexedIterable<T>::const_iterator(rawIdToValue.cend());
}
}// namespace stratos::registry

#endif //REGISTRY_H
