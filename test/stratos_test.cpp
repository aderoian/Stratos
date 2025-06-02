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

#include "network/protocol/PacketSerialization.h"
#include "utils/io/FileUtils.h"
#include "utils/io/ByteBuffer.h"

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
void networkSerializationTest() {
    std::cout << "Running network serialization test..." << std::endl;
    stratos::ByteVec buffer;
    size_t offset = 0;

    // Test writing and reading a boolean
    std::cout << "Testing boolean serialization..." << std::endl;
    stratos::writeBoolean(buffer, true);
    stratos::writeBoolean(buffer, false);
    assert(stratos::readBoolean(buffer, offset) == true);
    assert(stratos::readBoolean(buffer, offset) == false);

    // Test writing and reading a byte
    std::cout << "Testing byte serialization..." << std::endl;
    stratos::writeByte(buffer, 42);
    stratos::writeByte(buffer, -42);
    stratos::writeUnsignedByte(buffer, 230);
    assert(stratos::readByte(buffer, offset) == 42);
    assert(stratos::readByte(buffer, offset) == -42);
    assert(stratos::readUnsignedByte(buffer, offset) == 230);

    // Test writing and reading a short
    std::cout << "Testing short serialization..." << std::endl;
    stratos::writeShort(buffer, 12345);
    stratos::writeShort(buffer, -12345);
    stratos::writeUnsignedShort(buffer, 54321);
    assert(stratos::readShort(buffer, offset) == 12345);
    assert(stratos::readShort(buffer, offset) == -12345);
    assert(stratos::readUnsignedShort(buffer, offset) == 54321);

    // Test writing and reading an int
    std::cout << "Testing int serialization..." << std::endl;
    stratos::writeInt(buffer, 123456789);
    stratos::writeInt(buffer, -123456789);
    assert(stratos::readInt(buffer, offset) == 123456789);
    assert(stratos::readInt(buffer, offset) == -123456789);

    // Test writing and reading a long
    std::cout << "Testing long serialization..." << std::endl;
    stratos::writeLong(buffer, 1234567890123456789LL);
    stratos::writeLong(buffer, -1234567890123456789LL);
    assert(stratos::readLong(buffer, offset) == 1234567890123456789LL);
    assert(stratos::readLong(buffer, offset) == -1234567890123456789LL);

    // Test writing and reading a float
    std::cout << "Testing float serialization..." << std::endl;
    stratos::writeFloat(buffer, 3.14f);
    stratos::writeFloat(buffer, -3.14f);
    assert(stratos::readFloat(buffer, offset) == 3.14f);
    assert(stratos::readFloat(buffer, offset) == -3.14f);

    // Test writing and reading a double
    std::cout << "Testing double serialization..." << std::endl;
    stratos::writeDouble(buffer, 3.141592653589793);
    stratos::writeDouble(buffer, -3.141592653589793);
    assert(stratos::readDouble(buffer, offset) == 3.141592653589793);
    assert(stratos::readDouble(buffer, offset) == -3.141592653589793);

    // Test writing and reading a VarInt
    std::cout << "Testing VarInt serialization..." << std::endl;
    stratos::writeVarInt(buffer, 123456);
    stratos::writeVarInt(buffer, -123456);
    assert(stratos::readVarInt(buffer, offset) == 123456);
    assert(stratos::readVarInt(buffer, offset) == -123456);

    // Test writing and reading a string
    std::cout << "Testing string serialization..." << std::endl;
    const std::string testString = "Hello, world!";
    stratos::writeString(buffer, testString, 100);
    const std::string testString2 = "Another test string with special characters: !@#$%^&*()";
    stratos::writeString(buffer, testString2, 100);
    std::string testString3 = "A string with a length that exceeds the maximum allowed length.";
    try {
        stratos::writeString(buffer, testString, 10);
        assert(false); // Should not reach here
    } catch (const stratos::PacketSerializationException& e) {

    }
    assert(stratos::readString(buffer, offset, 100) == testString);
    assert(stratos::readString(buffer, offset, 100) == testString2);

    // Test writing and reading a VarLong
    std::cout << "Testing VarLong serialization..." << std::endl;
    stratos::writeVarLong(buffer, 1234567890123456789LL);
    stratos::writeVarLong(buffer, -1234567890123456789LL);
    assert(stratos::readVarLong(buffer, offset) == 1234567890123456789LL);
    assert(stratos::readVarLong(buffer, offset) == -1234567890123456789LL);
}

void fileUtilsTest() {
    stratos::Path path("relativeTest");
    assert(!path.exists());
    assert(!path.isDirectory());
    assert(path.mkdir());
    assert(path.exists());
    assert(!path.isAbsolute());
    assert(path.isRelative());
    assert(!path.isFile());

    stratos::Path file = path.resolve("test.txt");
    assert(!file.exists());
    assert(!file.isFile());
    {
        std::fstream fs = stratos::open(file, std::ios::out);
        fs << "Hello, Stratos!";
        stratos::close(fs);
    }
    assert(file.exists());
    assert(file.isFile());
    {
        std::fstream fs = stratos::open(file, std::ios::in);
        std::string content;
        std::getline(fs, content);
        stratos::close(fs);
        assert(content == "Hello, Stratos!");
    }

    file.remove();
    assert(!file.exists());
    assert(!file.isFile());
    assert(path.exists() && path.isDirectory());
    assert(path.rmdir());
    assert(!path.exists());
    assert(!path.isDirectory());
}

void testReadBoolean() {
    std::cout << "Testing readBoolean()..." << std::endl;

    // Test data: true (0x01), false (0x00), true (0xFF)
    ByteVec data = {0x01, 0x00, 0xFF};
    stratos::ByteBuffer buffer(data);

    assert(buffer.readBoolean() == true);
    assert(buffer.readBoolean() == false);
    assert(buffer.readBoolean() == true); // Non-zero is true

    std::cout << "✓ readBoolean() passed" << std::endl;
}

void testReadByte() {
    std::cout << "Testing readByte()..." << std::endl;

    // Test data: 127, -128, 0, -1
    ByteVec data = {0x7F, 0x80, 0x00, 0xFF};
    stratos::ByteBuffer buffer(data);

    assert(buffer.readByte() == 127);
    assert(buffer.readByte() == -128);
    assert(buffer.readByte() == 0);
    assert(buffer.readByte() == -1);

    std::cout << "✓ readByte() passed" << std::endl;
}

void testReadUnsignedByte() {
    std::cout << "Testing readUnsignedByte()..." << std::endl;

    // Test data: 0, 127, 128, 255
    ByteVec data = {0x00, 0x7F, 0x80, 0xFF};
    stratos::ByteBuffer buffer(data);

    assert(buffer.readUnsignedByte() == 0);
    assert(buffer.readUnsignedByte() == 127);
    assert(buffer.readUnsignedByte() == 128);
    assert(buffer.readUnsignedByte() == 255);

    std::cout << "✓ readUnsignedByte() passed" << std::endl;
}

void testReadShort() {
    std::cout << "Testing readShort()..." << std::endl;

    // Test data (big-endian): 0x1234, 0x8000 (-32768), 0x7FFF (32767), 0x0000
    ByteVec data = {0x12, 0x34, 0x80, 0x00, 0x7F, 0xFF, 0x00, 0x00};
    stratos::ByteBuffer buffer(data);

    assert(buffer.readShort() == 0x1234);
    assert(buffer.readShort() == -32768);
    assert(buffer.readShort() == 32767);
    assert(buffer.readShort() == 0);

    std::cout << "✓ readShort() passed" << std::endl;
}

void testReadUnsignedShort() {
    std::cout << "Testing readUnsignedShort()..." << std::endl;

    // Test data (big-endian): 0x1234, 0x8000, 0xFFFF, 0x0000
    ByteVec data = {0x12, 0x34, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0x00};
    stratos::ByteBuffer buffer(data);

    assert(buffer.readUnsignedShort() == 0x1234);
    assert(buffer.readUnsignedShort() == 0x8000);
    assert(buffer.readUnsignedShort() == 0xFFFF);
    assert(buffer.readUnsignedShort() == 0x0000);

    std::cout << "✓ readUnsignedShort() passed" << std::endl;
}

void testReadInt() {
    std::cout << "Testing readInt()..." << std::endl;

    // Test data (big-endian): 0x12345678, 0x80000000 (-2147483648), 0x7FFFFFFF (2147483647)
    ByteVec data = {
        0x12, 0x34, 0x56, 0x78,
        0x80, 0x00, 0x00, 0x00,
        0x7F, 0xFF, 0xFF, 0xFF
    };
    stratos::ByteBuffer buffer(data);

    assert(buffer.readInt() == 0x12345678);
    assert(buffer.readInt() == -2147483648);
    assert(buffer.readInt() == 2147483647);

    std::cout << "✓ readInt() passed" << std::endl;
}

void testReadLong() {
    std::cout << "Testing readLong()..." << std::endl;

    // Test data (big-endian): 0x123456789ABCDEF0, 0x8000000000000000 (min long), 0x7FFFFFFFFFFFFFFF (max long)
    ByteVec data = {
        0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    stratos::ByteBuffer buffer(data);

    assert(buffer.readLong() == 0x123456789ABCDEF0);
    assert(buffer.readLong() == (int64_t)0x8000000000000000);
    assert(buffer.readLong() == 0x7FFFFFFFFFFFFFFF);

    std::cout << "✓ readLong() passed" << std::endl;
}

void testReadFloat() {
    std::cout << "Testing readFloat()..." << std::endl;

    // Test data (IEEE 754 big-endian): 3.14159f, -1.0f, 0.0f
    // 3.14159f = 0x40490FDB, -1.0f = 0xBF800000, 0.0f = 0x00000000
    ByteVec data = {
        0x40, 0x49, 0x0F, 0xDB,
        0xBF, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    stratos::ByteBuffer buffer(data);

    float pi = buffer.readFloat();
    float negOne = buffer.readFloat();
    float zero = buffer.readFloat();

    assert(abs(pi - 3.14159f) < 0.0001f);
    assert(negOne == -1.0f);
    assert(zero == 0.0f);

    std::cout << "✓ readFloat() passed" << std::endl;
}

void testReadDouble() {
    std::cout << "Testing readDouble()..." << std::endl;

    // Test data (IEEE 754 big-endian): 3.141592653589793, -1.0, 0.0
    // 3.141592653589793 = 0x400921FB54442D18
    // -1.0 = 0xBFF0000000000000
    // 0.0 = 0x0000000000000000
    ByteVec data = {
        0x40, 0x09, 0x21, 0xFB, 0x54, 0x44, 0x2D, 0x18,
        0xBF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    stratos::ByteBuffer buffer(data);

    double pi = buffer.readDouble();
    double negOne = buffer.readDouble();
    double zero = buffer.readDouble();

    assert(abs(pi - 3.141592653589793) < 0.000000000000001);
    assert(negOne == -1.0);
    assert(zero == 0.0);

    std::cout << "✓ readDouble() passed" << std::endl;
}

void testReadString() {
    std::cout << "Testing readString()..." << std::endl;

    // Test data: length (2 bytes big-endian) + UTF-8 string "Hello"
    // Length = 5, then "Hello" in UTF-8
    ByteVec data = {
        0x00, 0x05,  // Length: 5
        'H', 'e', 'l', 'l', 'o'
    };
    stratos::ByteBuffer buffer(data);

    std::string result = buffer.readString(10);  // Max 10 chars
    assert(result == "Hello");

    std::cout << "✓ readString() passed" << std::endl;
}

void testReadVarInt() {
    std::cout << "Testing readVarInt()..." << std::endl;

    // Test data: VarInt encoding
    // 0 = 0x00
    // 127 = 0x7F
    // 128 = 0x80, 0x01
    // 300 = 0xAC, 0x02 (300 = 0x12C, encoded as 0xAC 0x02)
    ByteVec data = {
        0x00,           // 0
        0x7F,           // 127
        0x80, 0x01,     // 128
        0xAC, 0x02      // 300
    };
    stratos::ByteBuffer buffer(data);

    assert(buffer.readVarInt() == 0);
    assert(buffer.readVarInt() == 127);
    assert(buffer.readVarInt() == 128);
    assert(buffer.readVarInt() == 300);

    std::cout << "✓ readVarInt() passed" << std::endl;
}

void testReadVarLong() {
    std::cout << "Testing readVarLong()..." << std::endl;

    // Test data: VarLong encoding
    // 0 = 0x00
    // 127 = 0x7F
    // 128 = 0x80, 0x01
    ByteVec data = {
        0x00,           // 0
        0x7F,           // 127
        0x80, 0x01      // 128
    };
    stratos::ByteBuffer buffer(data);

    assert(buffer.readVarLong() == 0);
    assert(buffer.readVarLong() == 127);
    assert(buffer.readVarLong() == 128);

    std::cout << "✓ readVarLong() passed" << std::endl;
}

void testReadBitSet() {
    std::cout << "Testing readBitSet()..." << std::endl;

    // Test data: VarInt length + bit data
    // Length = 2 (2 longs), then two 64-bit values
    ByteVec data = {
        0x02,           // VarInt: 2 longs
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,  // First long: 15
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0   // Second long: 240
    };
    stratos::ByteBuffer buffer(data);

    std::vector<uint64_t> bitset = buffer.readBitSet();
    assert(bitset.size() == 2);
    assert(bitset[0] == 15);
    assert(bitset[1] == 240);

    std::cout << "✓ readBitSet() passed" << std::endl;
}

void testReadFixedBitSet() {
    std::cout << "Testing readFixedBitSet()..." << std::endl;

    // Test data: 16 bits = 2 bytes
    // 0x3C = 00111100, 0xA5 = 10100101
    ByteVec data = {0x3C, 0xA5};
    stratos::ByteBuffer buffer(data);

    std::vector<bool> bits = buffer.readFixedBitSet(16);
    assert(bits.size() == 16);

    // Check specific bits (remember: bit 0 is LSB of first byte)
    assert(bits[2] == true);   // Bit 2 of 0x3C
    assert(bits[3] == true);   // Bit 3 of 0x3C
    assert(bits[4] == true);   // Bit 4 of 0x3C
    assert(bits[5] == true);   // Bit 5 of 0x3C
    assert(bits[8] == true);   // Bit 0 of 0xA5
    assert(bits[10] == true);  // Bit 2 of 0xA5

    std::cout << "✓ readFixedBitSet() passed" << std::endl;
}

void testReadByteArray() {
    std::cout << "Testing readByteArray()..." << std::endl;

    // Test data: arbitrary bytes
    ByteVec data = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE};
    stratos::ByteBuffer buffer(data);

    ByteVec result = buffer.readByteArray(4);
    assert(result.size() == 4);
    assert(result[0] == 0xDE);
    assert(result[1] == 0xAD);
    assert(result[2] == 0xBE);
    assert(result[3] == 0xEF);

    std::cout << "✓ readByteArray() passed" << std::endl;
}

void testBufferUnderflow() {
    std::cout << "Testing buffer underflow exception..." << std::endl;

    ByteVec data = {0x01, 0x02};
    stratos::ByteBuffer buffer(data);

    // Read the two bytes
    buffer.readByte();
    buffer.readByte();

    // Try to read beyond buffer
    bool exceptionThrown = false;
    try {
        buffer.readByte();
    } catch (const stratos::BufferUnderflowException& e) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    std::cout << "✓ BufferUnderflowException test passed" << std::endl;
}

void testUtilityMethods() {
    std::cout << "Testing utility methods..." << std::endl;

    stratos::ByteBuffer buffer;

    // Test append
    ByteVec data1 = {0x01, 0x02};
    ByteVec data2 = {0x03, 0x04};

    buffer.append(data1);
    buffer.append(std::move(data2));

    assert(buffer.readByte() == 0x01);
    assert(buffer.readByte() == 0x02);
    assert(buffer.readByte() == 0x03);
    assert(buffer.readByte() == 0x04);

    // Test clear
    buffer.clear();

    // Test resize and reserve
    buffer.resize(10);
    buffer.reserve(20);

    std::cout << "✓ Utility methods test passed" << std::endl;
}

void bufferTest() {
    std::cout << "Running ByteBuffer tests...\n" << std::endl;

    try {
        testReadBoolean();
        testReadByte();
        testReadUnsignedByte();
        testReadShort();
        testReadUnsignedShort();
        testReadInt();
        testReadLong();
        testReadFloat();
        testReadDouble();
        testReadString();
        testReadVarInt();
        testReadVarLong();
        testReadBitSet();
        testReadFixedBitSet();
        testReadByteArray();
        testBufferUnderflow();
        testUtilityMethods();

        std::cout << "\n🎉 All tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
    }
}

int main(const int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "--network-serialization") {
            networkSerializationTest();
        } else if (arg == "--file-utils") {
            fileUtilsTest();
        } else if (arg == "--byte-buffer") {
            bufferTest();
        }
    }

    return 0;
}