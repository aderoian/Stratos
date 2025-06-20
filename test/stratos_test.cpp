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

#include "utils/collection/Palette.h"
#include "nbt/CompoundTag.h"
#include "nbt/io/NBTBuffer.h"
#include "nbt/ListTag.h"
#include "nbt/NBT.h"
#include "nbt/PrimitiveTag.h"
#include "nbt/StringTag.h"
#include "network/protocol/PacketSerialization.h"
#include "utils/config/Config.h"
#include "utils/io/ByteBuffer.h"
#include "utils/io/CompressionUtils.h"
#include "utils/io/FileUtils.h"
#include "utils/StringUtils.h"
#include "utils/Validate.h"

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
void networkSerializationTest() {
    std::cout << "Running network serialization test..." << std::endl;
    stratos::ByteBuffer buffer;
    size_t offset = 0;

    // Test writing and reading a boolean
    std::cout << "Testing boolean serialization..." << std::endl;
    buffer.writeBoolean(true);
    buffer.writeBoolean(false);
    assert(buffer.readBoolean() == true);
    assert(buffer.readBoolean() == false);

    // Test writing and reading a byte
    std::cout << "Testing byte serialization..." << std::endl;
    buffer.writeByte(42);
    buffer.writeByte(-42);
    buffer.writeUnsignedByte(230);
    assert(buffer.readByte() == 42);
    assert(buffer.readByte() == -42);
    assert(buffer.readUnsignedByte() == 230);

    // Test writing and reading a short
    std::cout << "Testing short serialization..." << std::endl;
    buffer.writeShort(12345);
    buffer.writeShort(-12345);
    buffer.writeUnsignedShort(54321);
    assert(buffer.readShort() == 12345);
    assert(buffer.readShort() == -12345);
    assert(buffer.readUnsignedShort() == 54321);

    // Test writing and reading an int
    std::cout << "Testing int serialization..." << std::endl;
    buffer.writeInt(123456789);
    buffer.writeInt(-123456789);
    assert(buffer.readInt() == 123456789);
    assert(buffer.readInt() == -123456789);

    // Test writing and reading a long
    std::cout << "Testing long serialization..." << std::endl;
    buffer.writeLong(1234567890123456789LL);
    buffer.writeLong(-1234567890123456789LL);
    assert(buffer.readLong() == 1234567890123456789LL);
    assert(buffer.readLong() == -1234567890123456789LL);

    // Test writing and reading a float
    std::cout << "Testing float serialization..." << std::endl;
    buffer.writeFloat(3.14f);
    buffer.writeFloat(-3.14f);
    assert(buffer.readFloat() == 3.14f);
    assert(buffer.readFloat() == -3.14f);

    // Test writing and reading a double
    std::cout << "Testing double serialization..." << std::endl;
    buffer.writeDouble(3.141592653589793);
    buffer.writeDouble(-3.141592653589793);
    assert(buffer.readDouble() == 3.141592653589793);
    assert(buffer.readDouble() == -3.141592653589793);

    // Test writing and reading a VarInt
    std::cout << "Testing VarInt serialization..." << std::endl;
    buffer.writeVarInt(123456);
    buffer.writeVarInt(-123456);
    assert(buffer.readVarInt() == 123456);
    assert(buffer.readVarInt() == -123456);

    // Test writing and reading a string
    std::cout << "Testing string serialization..." << std::endl;
    const std::string testString = "Hello, world!";
    buffer.writeString(testString, 100);
    const std::string testString2 = "Another test string with special characters: !@#$%^&*()";
    buffer.writeString(testString2, 100);
    std::string testString3 = "A string with a length that exceeds the maximum allowed length.";
    try {
        buffer.writeString(testString, 10);
        assert(false); // Should not reach here
    } catch (const stratos::PacketSerializationException& e) {

    }
    assert(buffer.readString(100) == testString);
    assert(buffer.readString(100) == testString2);

    // Test writing and reading a VarLong
    std::cout << "Testing VarLong serialization..." << std::endl;
    buffer.writeVarLong(1234567890123456789LL);
    buffer.writeVarLong(-1234567890123456789LL);
    assert(buffer.readVarLong() == 1234567890123456789LL);
    assert(buffer.readVarLong() == -1234567890123456789LL);
}

void fileUtilsTest() {
    stratos::Path path("fileUtils");
    if (path.exists()) {
        assert(path.isDirectory());
        assert(path.rmdir());
    }
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

    stratos::Path configDir("config");
    if (configDir.exists()) {
        assert(configDir.isDirectory());
        assert(configDir.rmdir());
    }
    assert(!configDir.exists());
    assert(!configDir.isDirectory());
    assert(configDir.mkdir());
    assert(configDir.exists());
    assert(configDir.isDirectory());

    stratos::Path defaultFile = configDir.resolve("testDefault.properties");
    assert(!defaultFile.exists());
    assert(!defaultFile.isFile());
    {
        stratos::PropertiesConfig config(defaultFile, "key1=value1\nkey2=value2");
        config.close();
    }
    assert(defaultFile.exists());
    assert(defaultFile.isFile());

    {
        stratos::PropertiesConfig config(defaultFile);
        auto prop1 = config.getProperty("key1");
        assert(prop1.has_value() && prop1->get().asString() == "value1");
        auto prop2 = config.getProperty("key2");
        assert(prop2.has_value() && prop2->get().asString() == "value2");

        config.writeProperty({"key3", "value3"});
        config.close();
    }

    {
        stratos::PropertiesConfig config(defaultFile);
        auto prop3 = config.getProperty("key3");
        assert(prop3.has_value() && prop3->get().asString() == "value3");
        config.close();
    }

    stratos::Path testUnder = configDir.resolve("testUnder.properties");
    {
        stratos::PropertiesConfig config(testUnder, "key1=value1\nkey2=value2");
        config.removeProperty("key2");
        config.close();
    }

    {
        stratos::PropertiesConfig config(testUnder);
        auto prop1 = config.getProperty("key1");
        assert(prop1.has_value() && prop1->get().asString() == "value1");
        auto prop2 = config.getProperty("key2");
        assert(!prop2.has_value());
    }

    path.mkdirs();
    stratos::Path testBytes = path.resolve("testBytes.dat");
    {
        stratos::ByteBuffer buffer;
        buffer.writeString("Hello, Stratos!", 100);
        stratos::writeAllBytes(testBytes, buffer.data());
    }
    {
        auto bytes = stratos::readAllBytes(testBytes);
        stratos::ByteBuffer buffer(bytes);
        std::string readStr = buffer.readString(100);
        assert(readStr == "Hello, Stratos!");
    }
}

void stringUtilsTest() {
    std::string trim1 = "   Hello, Stratos!   ";
    std::string trimmed1 = stratos::trim(trim1);
    assert(trimmed1 == "Hello, Stratos!");
    std::string trim2 = "\t\n\r  \tStratos is great!\n\r\t  ";
    std::string trimmed2 = stratos::trim(trim2);
    assert(trimmed2 == "Stratos is great!");
    std::string lower = "Hello, Stratos!";
    std::string lowercased = stratos::toLower(lower);
    assert(lowercased == "hello, stratos!");
    std::string upper = "Hello, Stratos!";
    std::string uppercased = stratos::toUpper(upper);
    assert(uppercased == "HELLO, STRATOS!");
    std::string replaceAllStr = "Hello, Stratos! Hello, Stratos!";
    std::string replacedAll = stratos::replaceAll(replaceAllStr, "Stratos", "World");
    assert(replacedAll == "Hello, World! Hello, World!");
    std::string replaceFirstStr = "Hello, Stratos! Hello, Stratos!";
    std::string replacedFirst = stratos::replaceFirst(replaceFirstStr, "Stratos", "World");
    assert(replacedFirst == "Hello, World! Hello, Stratos!");
    std::vector<std::string> elements = {"Hello", "Stratos", "World"};
    std::string joined = stratos::join(", ", elements);
    assert(joined == "Hello, Stratos, World");
    std::string splitStr = "Hello,Stratos,World";
    std::vector<std::string> splitByComma = stratos::split(splitStr, ',');
    assert(splitByComma.size() == 3 && splitByComma[0] == "Hello" && splitByComma[1] == "Stratos" && splitByComma[2] == "World");
    std::vector<std::string> splitBySpace = stratos::split("Hello Stratos World", " ");
    assert(splitBySpace.size() == 3 && splitBySpace[0] == "Hello" && splitBySpace[1] == "Stratos" && splitBySpace[2] == "World");
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

    // Test data: length (VarInt) + UTF-8 string "Hello"
    // Length = 5, then "Hello" in UTF-8
    ByteVec data = {
        0x05,  // Length: 5
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

namespace nbt = stratos::nbt;

void nbtTest() {
    std::cout << "Running NBT tests" << std::endl;
    stratos::Path nbtPath("nbt_test");
    if (!nbtPath.exists()) {
        throw std::runtime_error("Please create and add test files to the 'nbt_test' directory.");
    }

    {
        std::cout << "Testing hello_world.nbt";
        stratos::Path testFile = nbtPath.resolve("hello_world.nbt");
        nbt::NBTBuffer buffer(stratos::readAllBytes(testFile));
        auto [name, tag] = buffer.readTag<nbt::CompoundTag>();

        assert(name == "hello world");
        assert(tag->hasKey("name"));
        assert((*tag)["name"].getType() == nbt::TagType::String);
        assert((*tag)["name"].as<nbt::StringTag>().get() == "Bananrama");
    }
    {
        std::cout << "Testing bigtest.nbt";
        stratos::Path testFile = nbtPath.resolve("bigtest.nbt");
        std::ifstream file(testFile.getNativePath(), std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        std::cout << "File size: " << size << "\n";
        std::cout << "Buffer size " << stratos::readAllBytes(testFile).size() << "\n";
        stratos::ByteBuffer bytes(stratos::readAllBytes(testFile));
        nbt::NBTBuffer buffer((stratos::decompress(bytes).data()));
        auto [name, tag] = buffer.readTag<nbt::CompoundTag>();

        assert(name == "Level");
        assert(tag->size() == 11);
        assert(tag->hasKey("nested compound test"));
        assert(tag->hasKey("intTest"));
        assert(tag->hasKey("byteTest"));
        assert(tag->hasKey("stringTest"));
        assert(tag->hasKey("listTest (long)"));
        assert(tag->hasKey("doubleTest"));
        assert(tag->hasKey("floatTest"));
        assert(tag->hasKey("longTest"));
        assert(tag->hasKey("listTest (compound)"));
        assert(tag->hasKey("byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"));
        assert(tag->hasKey("shortTest"));

        auto nested = (*tag)["nested compound test"].as<nbt::CompoundTag>();
        assert(nested.hasKey("egg"));
        assert(nested.hasKey("ham"));
        assert(nested["egg"].getType() == nbt::TagType::Compound);
        assert(nested["ham"].getType() == nbt::TagType::Compound);
        auto egg = nested["egg"].as<nbt::CompoundTag>();
        auto ham = nested["ham"].as<nbt::CompoundTag>();
        assert(egg.hasKey("name"));
        assert(egg.hasKey("value"));
        assert(ham.hasKey("name"));
        assert(ham.hasKey("value"));
        assert(egg["name"].getType() == nbt::TagType::String);
        assert(egg["value"].getType() == nbt::TagType::Float);
        assert(egg["name"].as<nbt::StringTag>().get() == "Eggbert");
        assert(egg["value"].as<nbt::FloatTag>().get() == 0.5f);
        assert(ham["name"].getType() == nbt::TagType::String);
        assert(ham["value"].getType() == nbt::TagType::Float);
        assert(ham["name"].as<nbt::StringTag>().get() == "Hampus");
        assert(ham["value"].as<nbt::FloatTag>().get() == 0.75f);

        assert((*tag)["intTest"].getType() == nbt::TagType::Int);
        assert((*tag)["intTest"].as<nbt::IntTag>().get() == 2147483647);
        assert((*tag)["byteTest"].getType() == nbt::TagType::Byte);
        assert((*tag)["byteTest"].as<nbt::ByteTag>().get() == 127);
        assert((*tag)["stringTest"].getType() == nbt::TagType::String);
        assert((*tag)["stringTest"].as<nbt::StringTag>().get() == "HELLO WORLD THIS IS A TEST STRING ÅÄÖ!");

        auto listTag = (*tag)["listTest (long)"].as<nbt::ListTag>();
        assert(listTag.getListType() == nbt::TagType::Long);
        assert(listTag.size() == 5);
        assert(listTag[0].as<nbt::LongTag>().get() == 11LL);
        assert(listTag[1].as<nbt::LongTag>().get() == 12LL);
        assert(listTag.at(2).as<nbt::LongTag>().get() == 13LL);
        assert(listTag[3].as<nbt::LongTag>().get() == 14LL);
        assert(listTag[4].as<nbt::LongTag>().get() == 15LL);

        assert((*tag)["doubleTest"].getType() == nbt::TagType::Double);
        assert((*tag)["doubleTest"].as<nbt::DoubleTag>().get() == 0.49312871321823148);
        assert((*tag)["floatTest"].getType() == nbt::TagType::Float);
        assert((*tag)["floatTest"].as<nbt::FloatTag>().get() == 0.49823147058486938f);
        assert((*tag)["longTest"].getType() == nbt::TagType::Long);
        assert((*tag)["longTest"].as<nbt::LongTag>().get() == 9223372036854775807LL);

        auto compoundList = (*tag)["listTest (compound)"].as<nbt::ListTag>();
        assert(compoundList.getListType() == nbt::TagType::Compound);
        assert(compoundList.size() == 2);
        auto first = compoundList[0].as<nbt::CompoundTag>();
        auto second = compoundList[1].as<nbt::CompoundTag>();
        assert(first.hasKey("created-on"));
        assert(second.hasKey("created-on"));
        assert(first.hasKey("name"));
        assert(second.hasKey("name"));
        assert(first["created-on"].getType() == nbt::TagType::Long);
        assert(first["name"].getType() == nbt::TagType::String);
        assert(second["created-on"].getType() == nbt::TagType::Long);
        assert(second["name"].getType() == nbt::TagType::String);

        assert(first["created-on"].as<nbt::LongTag>().get() == 1264099775885LL);
        assert(first["name"].as<nbt::StringTag>().get() == "Compound tag #0");
        assert(second["created-on"].as<nbt::LongTag>().get() == 1264099775885LL);
        assert(second["name"].as<nbt::StringTag>().get() == "Compound tag #1");

        assert((*tag)["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"].getType() == nbt::TagType::ByteArray);
        assert((*tag)["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"].as<nbt::ByteArrayTag>().size() == 1000);
        auto byteArray = (*tag)["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"].as<nbt::ByteArrayTag>();
        for (int i = 0; i < 1000; i++) {
            byteArray[i] == (i*i*255+i*7)%100;
        }

        assert((*tag)["shortTest"].getType() == nbt::TagType::Short);
        assert((*tag)["shortTest"].as<nbt::ShortTag>().get() == 32767);
    }

    {
        const nbt::CompoundTag plainsBiome{
            nbt::CompoundTag::CompoundElement{"has_precipitation", nbt::ByteTag{true}}, nbt::CompoundTag::CompoundElement{"temperature", nbt::FloatTag{0.8}},
            nbt::CompoundTag::CompoundElement{"downfall", nbt::FloatTag{0.4}},
            nbt::CompoundTag::CompoundElement{
                "effects",
                nbt::CompoundTag{nbt::CompoundTag::CompoundElement{"fog_color", nbt::IntTag{12638463}}, nbt::CompoundTag::CompoundElement{"water_color", nbt::IntTag{4159204}},
                                 nbt::CompoundTag::CompoundElement{"water_fog_color", nbt::IntTag{329011}}, nbt::CompoundTag::CompoundElement{"sky_color", nbt::IntTag{329011}},
                                 nbt::CompoundTag::CompoundElement{"mood_sound", nbt::CompoundTag{nbt::CompoundTag::CompoundElement{"tick_delay", nbt::IntTag{6000}},
                                                                                                  nbt::CompoundTag::CompoundElement{"block_search_extent", nbt::IntTag{8}},
                                                                                                  nbt::CompoundTag::CompoundElement{"sound", nbt::StringTag{"minecraft:ambient.cave"}},
                                                                                                  nbt::CompoundTag::CompoundElement{"offset", nbt::FloatTag{2.0f}}}}}}};


        ByteVec bytes = nbt::writeNetworkNBT(plainsBiome);
        auto tag =  nbt::readNetworkNBT(nbt::NBTBuffer(bytes));
    }
}

void paletteTest() {
    // Empty Palette
    {
        stratos::Palette palette(2, 10); // 2 bits per entry, 10 entries, max value 3 (0, 1, 2, 3)
        assert(palette.getBitsPerEntry() == 2);
        assert(palette.getMaxValue() == 3);
        assert(palette.getSize() == 10);

        // Out of range checks
        try {
            palette.set(0, 4);
        } catch (stratos::ValidateException& e) {
            assert(e.what() == std::string("Value is out of range"));
        } catch (std::exception&) {
            assert(false);
        }

        try {
            palette.set(11, 0);
        } catch (stratos::ValidateException& e) {
            assert(e.what() == std::string("Value is out of range"));
        } catch (std::exception&) {
            assert(false);
        }

        // Populate
        palette.set(0, 0);
        palette.set(1, 1);
        palette.set(2, 2);
        palette.set(3, 3);
        palette.set(4, 0);
        palette.set(5, 1);
        palette.set(6, 2);
        palette.set(7, 3);
        palette.set(8, 0);
        palette.set(9, 1);

        // Test Get
        assert(palette.get(0) == 0);
        assert(palette.get(1) == 1);
        assert(palette.get(2) == 2);
        assert(palette.get(3) == 3);
        assert(palette.get(4) == 0);
        assert(palette.get(5) == 1);
        assert(palette.get(6) == 2);
        assert(palette.get(7) == 3);
        assert(palette.get(8) == 0);
        assert(palette.get(9) == 1);

        // Test Out of Range
        try {
            assert(palette.get(11) == 0);
        } catch (stratos::ValidateException& e) {
            assert(e.what() == std::string("Value is out of range"));
        } catch (std::exception&) {
            assert(false);
        }

        // Test Swap
        assert(palette.swap(0, 1) == 0);
        assert(palette.get(0) == 1);
        assert(palette.get(1) == 1);
        assert(palette.swap(1, 2) == 1);
        assert(palette.get(1) == 2);

        // Test Write Indices
        const std::vector expected = {1, 2, 2, 3, 0, 1, 2, 3, 0, 1};
        std::vector<int> out;
        palette.writeIndices(out);
        assert(out == expected);
    }
}

int main(const int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "--network-serialization") {
            networkSerializationTest();
        } else if (arg == "--file-utils") {
            fileUtilsTest();
        } else if (arg == "--string-utils") {
            stringUtilsTest();
        } else if (arg == "--byte-buffer") {
            bufferTest();
        } else if (arg == "--nbt") {
            nbtTest();
        } else if (arg == "--palette") {
            paletteTest();
        }
    }

    return 0;
}