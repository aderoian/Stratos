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

#include "NBTBuffer.h"

#include "nbt/ListTag.h"
#include "network/protocol/PacketSerialization.h"

namespace stratos {
std::string                                  NBTBuffer::readTagName() {
    return readModifiedUTF8String();
}
std::pair<std::string, std::unique_ptr<Tag>> NBTBuffer::readTag() {
    auto tag = Tag::create(static_cast<TagType>(readByte()));
    if (!tag || tag->getType() == TagType::End) return {"", nullptr}; // End tag indicates no further tags
    std::string name = readModifiedUTF8String();
    tag->read(*this);
    return {std::move(name), std::unique_ptr<Tag>(tag.release())};
}
std::string NBTBuffer::readModifiedUTF8String() {
    const uint16_t length = readUnsignedShort();
    std::string result;
    result.reserve(length); // Approximation
    for (uint16_t i = 0; i < length; ) {
        const uint8_t b = readUnsignedByte();
        ++i;
        if (b == 0xC0 && i < length) {
            const uint8_t next = readUnsignedByte();
            ++i;
            if (next == 0x80) {
                result.push_back('\0');
            } else {
                result.push_back(static_cast<char>(b));
                result.push_back(static_cast<char>(next));
            }
        } else {
            result.push_back(static_cast<char>(b));
        }
    }

    return result;
}
void NBTBuffer::writeTagName(const std::string& tagName) {
    writeModifiedUTF8String(tagName);
}
void NBTBuffer::writeTag(const std::string& name, const std::unique_ptr<Tag>& tag) {
    writeByte(static_cast<uint8_t>(tag->getType()));
    writeString(name, name.size());
    tag->write(*this);
}
void NBTBuffer::writeModifiedUTF8String(const std::string& str) {
    std::vector<uint8_t> encoded;
    for (unsigned char c : str) {
        if (c == 0x00) {
            encoded.push_back(0xC0);
            encoded.push_back(0x80);
        } else {
            encoded.push_back(c);
        }
    }

    if (encoded.size() > 0xFFFF) throw BufferOverflowException("String too long for Modified UTF-8 (max 65535 bytes)");
    writeUnsignedShort(static_cast<uint16_t>(encoded.size()));
    for (const uint8_t b : encoded)
        writeUnsignedByte(b);
}
} // stratos