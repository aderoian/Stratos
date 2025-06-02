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
#include "utils/config/Config.h"
#include "utils/io/FileUtils.h"
#include "utils/StringUtils.h"

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

int main(const int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "--network-serialization") {
            networkSerializationTest();
        } else if (arg == "--file-utils") {
            fileUtilsTest();
        } else if (arg == "--string-utils") {
            stringUtilsTest();
        }
    }

    return 0;
}