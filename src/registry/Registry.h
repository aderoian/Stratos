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
#include "nbt/ArrayTag.h"
#include "nbt/CompoundTag.h"
#include "nbt/NBT.h"
#include "network/protocol/definition/PacketConfiguration.h"
#include "utils/collection/Iterable.h"
#include "utils/Identifier.h"
#include "utils/Types.h"

#include <unordered_map>
#include <utility>

namespace stratos::network {
class RegistryDataPacket;
}
namespace stratos::registry {
struct RegistryKey {
    utils::Identifier registry;
    utils::Identifier value;

    bool operator==(const RegistryKey& other) const;
    bool operator!=(const RegistryKey& other) const;

    [[nodiscard]] std::string toString() const;
};

template <typename T> class Registry : public utils::IndexedIterable<T> {
  public:
    explicit Registry(RegistryKey key) : key(std::move(key)) {}
    [[nodiscard]] const RegistryKey& getKey() const;

    int getRawIndex(T value) const override;
    T   get(int index) const override;
    T   get(const utils::Identifier& key) const;
    T   get(const RegistryKey& key) const;
    utils::Identifier getEntry(T value) const;
    [[nodiscard]] int size() const override;

    virtual void registerEntry(const RegistryKey& key, T value);

    typename utils::IndexedIterable<T>::iterator       begin() override;
    typename utils::IndexedIterable<T>::const_iterator begin() const override;
    typename utils::IndexedIterable<T>::iterator       end() override;
    typename utils::IndexedIterable<T>::const_iterator end() const override;

  protected:
    RegistryKey key;
    std::vector<T>                     rawIdToValue;
    std::unordered_map<utils::Identifier, T>  idToValue;
    std::unordered_map<RegistryKey, T> keyToValue;
    std::unordered_map<T, int>        valueToRawId;
    std::unordered_map<T, utils::Identifier> valueToEntry;
private:
    int nextId = 0;
};

class DynamicRegistryElement {
public:
    virtual ~DynamicRegistryElement() = default;
    virtual nbt::CompoundTag toNetworkNBT() const = 0;
};

template <typename T>
class DynamicRegistry final : public Registry<T> {
public:
    explicit DynamicRegistry(RegistryKey key) : Registry<T>(key) {
        static_assert(std::is_base_of_v<DynamicRegistryElement, std::remove_pointer_t<T>>);
    }
    ~DynamicRegistry() override {}

    const network::RegistryDataPacket* createDynamicEntryPacket(utils::Identifier key) const;
};

template <typename T> const RegistryKey& Registry<T>::getKey() const {
    return key;
}
template <typename T> int Registry<T>::getRawIndex(T value) const {
    auto el = valueToRawId.find(value);
    return el != valueToRawId.end() ? el->second : -1;
}
template <typename T> T Registry<T>::get(int index) const {
    return rawIdToValue.at(index);
}
template <typename T> T Registry<T>::get(const utils::Identifier& key) const {
    return idToValue.at(key);
}
template <typename T> T Registry<T>::get(const RegistryKey& key) const {
    return keyToValue.at(key);
}
template <typename T> utils::Identifier Registry<T>::getEntry(T value) const {
    return valueToEntry.at(value);
}
template <typename T> int Registry<T>::size() const {
    return rawIdToValue.size();
}
template <typename T> void Registry<T>::registerEntry(const RegistryKey& key, T value) {
    if (key.registry != this->key.value)
        throw std::invalid_argument("Registry key mismatch: expected " + this->key.value.toString() + ", got " + key.registry.toString());
    int id = nextId++;
    rawIdToValue.push_back(value);
    idToValue[key.value] = value;
    keyToValue[key] = value;
    valueToRawId[rawIdToValue[id]] = id;
    valueToEntry[value] = key.value;
}
template <typename T> typename utils::IndexedIterable<T>::iterator Registry<T>::begin() {
    return rawIdToValue.begin();
}
template <typename T> typename utils::IndexedIterable<T>::const_iterator Registry<T>::begin() const {
    return rawIdToValue.cbegin();
}
template <typename T> typename utils::IndexedIterable<T>::iterator Registry<T>::end() {
    return rawIdToValue.end();
}
template <typename T> typename utils::IndexedIterable<T>::const_iterator Registry<T>::end() const {
    return rawIdToValue.cend();
}
template <typename T> const network::RegistryDataPacket* DynamicRegistry<T>::createDynamicEntryPacket(utils::Identifier key) const {
    std::vector<RegistryEntry> entries;
    for (const auto& [regKey, value] : this->idToValue) {
        const DynamicRegistryElement* e;
        if constexpr (std::is_pointer_v<T>)
            e = dynamic_cast<const DynamicRegistryElement*>(value);
        else
            e = dynamic_cast<const DynamicRegistryElement*>(&value);
        entries.emplace_back(regKey, std::make_optional(nbt::writeNetworkNBT(e->toNetworkNBT())));
    }
    return new network::RegistryDataPacket(std::move(key), std::move(entries));
}
} // namespace stratos::registry

template <> struct std::hash<stratos::registry::RegistryKey> {
    std::size_t operator()(const stratos::registry::RegistryKey& key) const noexcept {
        return std::hash<std::string>()(key.registry.toString()) ^ std::hash<std::string>()(key.value.toString()) << 1;
    }
};

#endif //REGISTRY_H
