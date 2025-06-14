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

#ifndef STRATOS_BUFFER_H
#define STRATOS_BUFFER_H

#include <utility>
#include <vector>
#include <cstdint>
#include <stdexcept>

typedef unsigned char byte;
typedef std::vector<unsigned char> ByteVec;

namespace stratos {

class BufferUnderflowException : public std::logic_error {
  public:
    explicit BufferUnderflowException(const std::string& message)
        : std::logic_error(message) {}
    explicit BufferUnderflowException(const char* message)
        : std::logic_error(message) {}
};

class BufferOverflowException : public std::logic_error {
  public:
    explicit BufferOverflowException(const std::string& message)
        : std::logic_error(message) {}
    explicit BufferOverflowException(const char* message)
        : std::logic_error(message) {}
};

class ByteBuffer {
  public:
    ByteBuffer() : offset(0) {}
    explicit ByteBuffer(const ByteVec& data) : offset(0), buffer(data) {}
    explicit ByteBuffer(ByteVec&& data) : offset(0), buffer(std::move(data)) {}
    ByteBuffer(const ByteVec& data, const size_t offset) : offset(offset), buffer(data) {
        if (offset > data.size())
            throw BufferOverflowException("Offset exceeds buffer size");
    }
    ByteBuffer(ByteVec&& data, const size_t offset) : offset(offset), buffer(std::move(data)) {
        if (offset > data.size())
            throw BufferOverflowException("Offset exceeds buffer size");
    }
    ByteBuffer(const ByteBuffer&) = delete;
    ByteBuffer& operator=(const ByteBuffer&) = delete;
    ByteBuffer(ByteBuffer&&) = default;
    ByteBuffer& operator=(ByteBuffer&&) = default;
    virtual ~ByteBuffer() = default;
    
    bool                  readBoolean();
    int8_t                readByte();
    uint8_t               readUnsignedByte();
    short                 readShort();
    uint16_t              readUnsignedShort();
    int                   readInt();
    int64_t               readLong();
    float                 readFloat();
    double                readDouble();
    std::string           readString(int maxChars);
    int                   readVarInt();
    int64_t               readVarLong();
    std::vector<uint64_t> readBitSet();
    std::vector<bool>     readFixedBitSet(size_t length);
    ByteVec               readByteArray(size_t length);

    void writeBoolean(bool value);
    void writeByte(int8_t value);
    void writeUnsignedByte(uint8_t value);
    void writeShort(short value);
    void writeUnsignedShort(uint16_t value);
    void writeInt(int value);
    void writeLong(int64_t value);
    void writeFloat(float value);
    void writeDouble(double value);
    void writeString(const std::string& value, int maxChars);
    void writeVarInt(int value);
    void writeVarLong(int64_t value);
    void writeBitSet(const std::vector<uint64_t>& longs);
    void writeFixedBitSet(const std::vector<bool>& bits, size_t length);
    void writeByteArray(const ByteVec& values);

    /**
     * @brief Clears the buffer & resets the offset.
     */
    void clear() {
        offset = 0;
        buffer.clear();
    }
    
    void resize(const size_t size) { buffer.resize(size); }
    void reserve(const size_t size) { buffer.reserve(size); }
    void append(const ByteVec& data) { buffer.insert(buffer.end(), data.begin(), data.end()); }
    void append(const ByteVec&& data) { buffer.insert(buffer.end(), std::make_move_iterator(data.begin()), std::make_move_iterator(data.end())); }
    auto begin() { return buffer.begin(); }
    auto end() { return buffer.end(); }
    ByteVec& data() { return buffer; }
    [[nodiscard]] const ByteVec& data() const { return buffer; }
    [[nodiscard]] auto cbegin() const { return buffer.cbegin(); }
    [[nodiscard]] auto cend() const { return buffer.cend(); }
    [[nodiscard]] size_t size() const { return buffer.size(); }
    [[nodiscard]] bool empty() const { return buffer.empty(); }
    [[nodiscard]] size_t getOffset() const { return offset; }
    void setOffset(size_t newOffset);

    uint8_t operator[] (size_t index) const;
    uint8_t& operator[] (size_t index);

  protected:
    size_t offset;
    std::vector<byte> buffer;

    /**
     * @brief Checks if the buffer is readable.
     */
    void checkRead(const uint64_t size) const {
        if (offset + size > buffer.size()) {
            throw BufferUnderflowException("Buffer underflow: not enough data to read");
        }
    }
};

} // namespace stratos

#endif // STRATOS_BUFFER_H
