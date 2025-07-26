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
#include "block/state/BlockState.h"
#include "nbt/io/NBTBuffer.h"
#include "nbt/ListTag.h"
#include "nbt/PrimitiveTag.h"
#include "utils/collection/Iterable.h"
#include "utils/collection/PalettedStorage.h"
#include "utils/io/ByteBuffer.h"
#include "utils/MathUtils.h"
#include "utils/Predicate.h"
#include "world/format/Biome.h"

#include <format>
#include <optional>
#include <stdexcept>

namespace stratos {
namespace nbt {
class CompoundTag;
}
namespace world {

template <typename T> class Palette {
public:
    virtual ~Palette()                             = default;
    virtual int  index(T value)                    = 0;
    virtual T    get(int index) const              = 0;
    virtual bool has(Predicate<T> predicate) const = 0;
    [[nodiscard]] virtual int  size() const        = 0;

    virtual void read(ByteBuffer& buffer)        = 0;
    virtual void write(ByteBuffer& buffer) const = 0;
    [[nodiscard]] virtual int  writeSize() const = 0;
};

template <typename T> class SingularPalette : public Palette<T> {
public:
    SingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    [[nodiscard]] int size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    [[nodiscard]] int writeSize() const override;

private:
    const utils::IndexedIterable<T>* idList;
    std::optional<T>                 entry;
};

template <typename T> class ArrayPalette : public Palette<T> {
public:
    ArrayPalette(const utils::IndexedIterable<T>* idList, int bits, const std::vector<T>& entries);

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    [[nodiscard]] int  size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    [[nodiscard]] int  writeSize() const override;

private:
    const utils::IndexedIterable<T>* idList;
    std::vector<T>                   entries;
    int                              indexBits;
    int                              _size;
};

template <typename T> class IdListPalette : public Palette<T> {
public:
    explicit IdListPalette(const utils::IndexedIterable<T>* idList) : idList(idList) {};

    int  index(T value) override;
    T    get(int index) const override;
    bool has(Predicate<T> predicate) const override;
    [[nodiscard]] int  size() const override;

    void read(ByteBuffer& buffer) override;
    void write(ByteBuffer& buffer) const override;
    [[nodiscard]] int  writeSize() const override;

private:
    const utils::IndexedIterable<T>* idList;
};

template <typename T> Palette<T>* createSingularPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);
template <typename T> Palette<T>*    createArrayPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);
template <typename T> Palette<T>*   createIdListPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries);

template <typename T> class PalettedContainer {
public:
    /**
     * Tuple container for data storage of a palette and its associated data.
     */
    template <typename U> struct Data {
        Palette<U>* palette;
        PalettedStorage* storage;
        void write(ByteBuffer& buffer) const;
    };

    template <typename U> struct DataProvider {
        Palette<U>* (*paletteFactory)(int, const utils::IndexedIterable<U>*, const std::vector<U>&);
        int bits;

        Data<U> createData(const utils::IndexedIterable<U>* idList, int size) const;
    };

    template <typename U> struct PaletteProvider {
        DataProvider<U> (*dataFactory)(int, const utils::IndexedIterable<U>*);
        int edgeBits; // Number of bits used for each edge of the chunk section (i.e., 4 for 16x16x16 sections)

        [[nodiscard]] int getContainerSize() const;
        [[nodiscard]] int computeIndex(int x, int y, int z) const;
        [[nodiscard]] int getBits(const utils::IndexedIterable<U>* idList, int size) const;
    };

    PalettedContainer(const utils::IndexedIterable<T>* idList, PaletteProvider<T> provider, Data<T> data);
    PalettedContainer(const utils::IndexedIterable<T>* idList, T entry, PaletteProvider<T> provider);

    [[nodiscard]] T get(int x, int y, int z) const;
    [[nodiscard]] bool has(Predicate<T> predicate) const;
    void set(int x, int y, int z, T value);
    T swap(int x, int y, int z, T value);

    void read(ByteBuffer& buffer);
    void write(ByteBuffer& buffer) const;

    ~PalettedContainer();
private:
    const utils::IndexedIterable<T>* idList;
    PaletteProvider<T> provider;
    Data<T> data;

    [[nodiscard]] T get(int index) const;
    void set(int index, T value);
    T swap(int index, T value);
    [[nodiscard]] Data<T> createData(int bits) const;
};

template <typename T> Palette<T>* createSingularPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) {
    return new SingularPalette<T>(idList, entries);
}
template <typename T> Palette<T>* createArrayPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) {
    return new ArrayPalette<T>(idList, bits, entries);
}
template <typename T> Palette<T>* createIdListPalette(int bits, const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) {
    return new IdListPalette<T>(idList);
}

template <typename T> SingularPalette<T>::SingularPalette(const utils::IndexedIterable<T>* idList, const std::vector<T>& entries) : idList(idList) {
    if (!entries.empty()) {
        if (entries.size() != 1) throw std::invalid_argument(std::format("SingularPalette can only have one entry, got {}", entries.size()));
        entry = entries[0];
    } else {
        entry = std::nullopt;
    }
}

PalettedContainer<const block::BlockState*>::DataProvider<const block::BlockState*> BlockStateDataFactory(int bits, const utils::IndexedIterable<const block::BlockState*>* idList);
PalettedContainer<const Biome*>::DataProvider<const Biome*> biomeDataFactory(int bits, const utils::IndexedIterable<const Biome*>* idList);

constexpr PalettedContainer<const block::BlockState*>::PaletteProvider BLOCK_STATE = { BlockStateDataFactory, 4 };
constexpr PalettedContainer<const Biome*>::PaletteProvider BIOME = { biomeDataFactory, 2 };

std::vector<const block::BlockState*> readBlockStatePalette(nbt::CompoundTag& tag);
template <typename T>
const PalettedContainer<T>* read(const utils::IndexedIterable<T>* idList, typename PalettedContainer<T>::template PaletteProvider<T> provider, const std::vector<T>& entries, const std::vector<int64_t>& longs);

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
    this->entries = std::vector<T>(_size);
    for (int i = 0; i < entries.size(); ++i)
        this->entries[i] = entries[i];
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
    entries.reserve(_size);
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
template <typename T> template <typename U> void PalettedContainer<T>::Data<U>::write(ByteBuffer& buffer) const {
    buffer.writeByte(storage->getBitsPerEntry());
    palette->write(buffer);
    buffer.writeFixedLongArray(storage->getData());
}
template <typename T> template <typename U>
typename PalettedContainer<T>::template Data<U> PalettedContainer<T>::DataProvider<U>::createData(const utils::IndexedIterable<U>* idList, const int size) const {
    return { paletteFactory(bits, idList, std::vector<U>(0)), new PackedIntegerArray(bits, size) };
}
template <typename T> template <typename U> int PalettedContainer<T>::PaletteProvider<U>::getContainerSize() const {
    return 1 << edgeBits * 3;
}
template <typename T> template <typename U> int PalettedContainer<T>::PaletteProvider<U>::computeIndex(const int x, const int y, const int z) const {
    return (y << edgeBits | z) << edgeBits | x;
}
template <typename T> template <typename U> int PalettedContainer<T>::PaletteProvider<U>::getBits(const utils::IndexedIterable<U>* idList, int size) const {
    int bits = utils::ceilLog2(size);
    DataProvider<U> dp = dataFactory(bits, idList);

    using FactoryType = Palette<T>* (*)(int, const utils::IndexedIterable<T>*, const std::vector<T>&);
    FactoryType func = &createIdListPalette<T>;
    return dp.paletteFactory == func ? bits : dp.bits;
}
template <typename T> PalettedContainer<T>::PalettedContainer(const utils::IndexedIterable<T>* idList, PaletteProvider<T> provider, Data<T> data)
    : idList(idList), provider(std::move(provider)), data(data) {}
template <typename T> PalettedContainer<T>::PalettedContainer(const utils::IndexedIterable<T>* idList, T entry, PaletteProvider<T> provider) : idList(idList), provider(std::move(provider)) {
    data = createData(0);
    data.palette->index(entry);
}
template <typename T> T PalettedContainer<T>::get(const int x, const int y, const int z) const {
    return get(provider->computeIndex(x, y, z));
}
template <typename T> bool PalettedContainer<T>::has(Predicate<T> predicate) const {
    return data.palette->has(predicate);
}
template <typename T> void PalettedContainer<T>::set(const int x, const int y, const int z, T value) {
    set(provider->computeIndex(x, y, z), value);
}
template <typename T> T PalettedContainer<T>::swap(const int x, const int y, const int z, T value) {
    return swap(provider->computeIndex(x, y, z), value);
}
template <typename T> void PalettedContainer<T>::read(ByteBuffer& buffer) {
    data = createData(buffer.readByte());
    data.palette->read(buffer);
    buffer.readFixedLongArray(data.storage->getData());
}
template <typename T> void PalettedContainer<T>::write(ByteBuffer& buffer) const {
    data.write(buffer);
}
template <typename T> PalettedContainer<T>::~PalettedContainer() {
    delete data.palette;
    delete data.storage;
}
template <typename T> T PalettedContainer<T>::get(const int index) const {
    return data.palette->get(data.storage->get(index));
}
template <typename T> void PalettedContainer<T>::set(const int index, T value) {
    data.storage->set(index, data.palette->index(value));
}
template <typename T> T PalettedContainer<T>::swap(const int index, T value) {
    int i = data.storage->swap(index, data.palette->index(value));
    return data.palette->get(i);
}
template <typename T> typename PalettedContainer<T>::template Data<T> PalettedContainer<T>::createData(int bits) const {
    DataProvider<T> provider = data.palette->getDataProvider();
    return provider.createData(idList, provider.getContainerSize());
}
template <typename T> const PalettedContainer<T>* read(const utils::IndexedIterable<T>* idList, typename PalettedContainer<T>::template PaletteProvider<T> provider, const std::vector<T>& entries,
                                                       const std::vector<int64_t>& longs) {
    const int bits = provider.getBits(idList, entries.size());
    const int size = provider.getContainerSize();
    auto dp = provider.dataFactory(provider.getBits(idList, entries.size()), idList);

    PalettedStorage* storage;
    if (bits == 0) storage = new EmptyPalettedStorage(size);
    else storage = new PackedIntegerArray(bits, size, longs);

    return new PalettedContainer<T>(idList, provider, { dp.paletteFactory(dp.bits, idList, entries), storage });
}
} // namespace world
} // namespace stratos

#endif // PALETTE_H
