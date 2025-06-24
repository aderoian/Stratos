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
#include "utils/collection/Iterable.h"
#include "utils/io/ByteBuffer.h"
#include "utils/Predicate.h"

#include <format>
#include <optional>
#include <stdexcept>

namespace stratos {
class ByteBuffer;

template <typename T> class Palette<T> {
  public:
    virtual ~Palette()                             = default;
    virtual int  index(T value)                    = 0;
    virtual T    get(int index) const              = 0;
    virtual bool has(Predicate<T> predicate) const = 0;
    virtual int  size() const                      = 0;

    virtual void read(ByteBuffer& buffer)        = 0;
    virtual void write(ByteBuffer& buffer) const = 0;
    virtual int  writeSize() const               = 0;
};

template <typename T> class SingularPalette<T> : public Palette<T> {
  public:
    SingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    int  size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    int  writeSize() const override;

  private:
    const utils::IndexedIterable<T>* idList;
    std::optional<T>                 entry;
};

template <typename T> class ArrayPalette<T> : public Palette<T> {
  public:
    ArrayPalette(const utils::IndexedIterable<T>* idList, int bits, const std::vector<T>& entries);

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    int  size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    int  writeSize() const override;

  private:
    const utils::IndexedIterable<T>* idList;
    std::vector<T>                   entries;
    int                              indexBits;
    int                              _size;
};

template <typename T> class IdListPalette<T> : public Palette<T> {
  public:
    explicit IdListPalette(const utils::IndexedIterable<T>* idList) : idList(idList) {};

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    int  size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    int  writeSize() const override;

  private:
    const utils::IndexedIterable<T>* idList;
};

template <typename T> SingularPalette<T>* createSingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);
template <typename T> ArrayPalette<T>*    createArrayPalette(const utils::IndexedIterable<T>* idList, int bits, const std::vector<T>& entries);
template <typename T> IdListPalette<T>*   createIdListPalette(const utils::IndexedIterable<T>* idList);

template <typename T> SingularPalette<T>* createSingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) {
    return new SingularPalette<T>(idList, entries);
}
template <typename T> ArrayPalette<T>* createArrayPalette(const utils::IndexedIterable<T>* idList, int bits, const std::vector<T>& entries) {
    return new ArrayPalette<T>(idList, bits, entries);
}
template <typename T> IdListPalette<T>* createIdListPalette(const utils::IndexedIterable<T>* idList) {
    return new IdListPalette<T>(idList);
}

template <typename T> SingularPalette<T>::SingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) : idList(idList) {
    if (entries.size() > 0) {
        if (entries.size() != 1) throw std::invalid_argument(std::format("SingularPalette can only have one entry, got {}", entries.size()));
        entry = entries[0];
    } else {
        entry = std::nullopt;
    }
}
template <typename T> int SingularPalette<T>::index(T value) {
    return entry.has_value() && *entry == value ? 0 : -1;
}
template <typename T> T SingularPalette<T>::get(int index) const {
    if (index != 0 || !entry.has_value()) throw std::out_of_range(std::format("Index '{}' out of range for SingularPalette", index));
    return *entry;
}
template <typename T> bool SingularPalette<T>::has(Predicate<T> predicate) const {
    return predicate(get(0));
}
template <typename T> int SingularPalette<T>::size() const {
    return 1;
}
template <typename T> void SingularPalette<T>::read(ByteBuffer& buffer) {
    entry = idList->getOrThrow(buffer.readVarInt());
}
template <typename T> void SingularPalette<T>::write(ByteBuffer& buffer) const {
    if (!entry.has_value()) throw std::runtime_error("Use of a uninitialized palette");
    buffer.writeVarInt(idList->getRawIndexOrThrow(*entry));
}
template <typename T> int SingularPalette<T>::writeSize() const {
    return getEncodedSizeInBytes(idList->getRawIndex(*entry));
}
template <typename T> ArrayPalette<T>::ArrayPalette(const utils::IndexedIterable<T>* idList, int bits, const std::vector<T>& entries) : idList(idList), indexBits(bits) {
    _size = entries.size();
    this.entries.reserve(_size);
    for (int i = 0; i < entries.size(); ++i) {
        this.entries[i] = idList->get(entries[i]);
    }
}
template <typename T> int ArrayPalette<T>::index(T value) {
    for (int i = 0; i < _size; ++i)
        if (entries[i] == value) return i;
    return -1;
}
template <typename T> T ArrayPalette<T>::get(int index) const {
    if (index < 0 || index >= _size) throw std::out_of_range(std::format("Index '{}' out of range for ArrayPalette", index));
    return entries[index];
}
template <typename T> bool ArrayPalette<T>::has(Predicate<T> predicate) const {
    for (const T& entry : entries)
        if (predicate(entry)) return true;
    return false;
}
template <typename T> int ArrayPalette<T>::size() const {
    return _size;
}
template <typename T> void ArrayPalette<T>::read(ByteBuffer& buffer) {
    _size = buffer.readVarInt();
    entries.resize(_size);
    for (int i = 0; i < _size; ++i) {
        entries[i] = idList->getOrThrow(buffer.readVarInt());
    }
}
template <typename T> void ArrayPalette<T>::write(ByteBuffer& buffer) const {
    buffer.writeVarInt(_size);
    for (int i = 0; i < _size; ++i) buffer.writeVarInt(idList->getRawIndex(entries[i]));
}
template <typename T> int ArrayPalette<T>::writeSize() const {
    int size = getEncodedSizeInBytes(_size);
    for (const T& entry : entries) {
        size += getEncodedSizeInBytes(idList->getRawIndex(entry));
    }
    return size;
}
template <typename T> int IdListPalette<T>::index(T value) {
    return idList->getRawIndex(value);
}
template <typename T> T IdListPalette<T>::get(int index) const {
    return idList->getOrThrow(index);
}
template <typename T> bool IdListPalette<T>::has(Predicate<T> predicate) const {
    return true;
}
template <typename T> int IdListPalette<T>::size() const {
    return idList->size();
}
template <typename T> void IdListPalette<T>::read(ByteBuffer& buffer) {
    // No read, uses global registries
}
template <typename T> void IdListPalette<T>::write(ByteBuffer& buffer) const {
    // No write, uses global registries
}
template <typename T> int IdListPalette<T>::writeSize() const {
    return 0;
}
} // namespace stratos

#endif // PALETTE_H
