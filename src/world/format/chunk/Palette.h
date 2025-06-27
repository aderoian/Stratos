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
#include "utils/collection/PalettedStorage.h"
#include "utils/io/ByteBuffer.h"
#include "utils/Predicate.h"

#include <format>
#include <optional>
#include <stdexcept>

namespace stratos {
class BlockState;
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

template <typename T> class PalettedContainer {
public:
    PalettedContainer(const utils::IndexedIterable<T>* idList, Palette<T>* palette, PackedIntegerArray* storage, int edgeBits);
    PalettedContainer(const utils::IndexedIterable<T>* idList, Palette<T>* palette, int edgeBits, int bits);

    int getContainerSize() const;
    int computeIndex(int x, int y, int z) const;

    T get(int x, int y, int z) const;
    bool has(Predicate<T> predicate) const;
    void set(int x, int y, int z, T value);
    T swap(int x, int y, int z, T value);

    void read(ByteBuffer& buffer);
    void write(ByteBuffer& buffer) const;

    ~PalettedContainer();
private:
    const utils::IndexedIterable<T>* idList;
    Palette<T>* palette;
    PackedIntegerArray* storage;
    int edgeBits; // Number of bits used for each edge of the chunk section (i.e., 4 for 16x16x16 sections)

    T get(int index) const;
    void set(int index, T value);
    T swap(int index, T value);
};

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
template <typename T> PalettedContainer<T>::PalettedContainer(const utils::IndexedIterable<T>* idList, Palette<T>* palette, PackedIntegerArray* storage, const int edgeBits)
    : idList(idList), palette(palette), storage(storage), edgeBits(edgeBits) {}
template <typename T> PalettedContainer<T>::PalettedContainer(const utils::IndexedIterable<T>* idList, Palette<T>* palette, const int edgeBits, const int bits)
    : idList(idList), palette(palette), edgeBits(edgeBits) {
    storage = new PackedIntegerArray(bits, getContainerSize());
}
template <typename T> int PalettedContainer<T>::getContainerSize() const {
    return 1 << edgeBits * 3;
}
template <typename T> int PalettedContainer<T>::computeIndex(const int x, const int y, const int z) const {
    return (y << edgeBits | z) << edgeBits | x;
}
template <typename T> T PalettedContainer<T>::get(const int x, const int y, const int z) const {
    return get(computeIndex(x, y, z));
}
template <typename T> bool PalettedContainer<T>::has(Predicate<T> predicate) const {
    return palette->has(predicate);
}
template <typename T> void PalettedContainer<T>::set(const int x, const int y, const int z, T value) {
    set(computeIndex(x, y, z), value);
}
template <typename T> T PalettedContainer<T>::swap(const int x, const int y, const int z, T value) {
    return swap(computeIndex(x, y, z), value);
}
template <typename T> void PalettedContainer<T>::read(ByteBuffer& buffer) {
    int bits = buffer.readByte();
    // TODO: Create a provider to choose the correct palette type and initialize palette storage based on the buffer content
    palette->read(buffer);
    buffer.readFixedLongArray(storage->getData());
}
template <typename T> void PalettedContainer<T>::write(ByteBuffer& buffer) const {
    buffer.writeByte(storage->getBitsPerEntry());
    palette->write(buffer);
    buffer.writeFixedLongArray(storage->getData());
}
template <typename T> PalettedContainer<T>::~PalettedContainer() {
    delete palette;
    delete storage;
}
template <typename T> T PalettedContainer<T>::get(const int index) const {
    return palette->get(storage->get(index));
}
template <typename T> void PalettedContainer<T>::set(const int index, T value) {
    storage->set(index, palette->index(value));
}
template <typename T> T PalettedContainer<T>::swap(const int index, T value) {
    int i = storage->swap(index, palette->index(value));
    return palette->get(i);
}
} // namespace stratos

#endif // PALETTE_H
