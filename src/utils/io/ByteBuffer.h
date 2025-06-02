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
  private:
    size_t offset;
    std::vector<byte> buffer;

    /**
     * @brief Checks if the buffer is readable.
     */
    void checkRead(unsigned long long size) const {
        if (offset + size > buffer.size()) {
            throw BufferUnderflowException("Buffer underflow: not enough data to read");
        }
    }
    
  public:
    ByteBuffer() : offset(0) {}
    explicit ByteBuffer(ByteVec data) : offset(0), buffer(std::move(data)) {}
    
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
};

} // namespace stratos

#endif // STRATOS_BUFFER_H
