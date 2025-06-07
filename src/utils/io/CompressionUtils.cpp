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

#include "ByteBuffer.h"
#include "CompressionUtils.h"
#include "zlib.h"

namespace stratos {

bool isGzip(const ByteBuffer& buffer) {
    return buffer.size() >= 2 && buffer[0] == 0x1F && buffer[1] == 0x8B;
}
bool isZlib(const ByteBuffer& buffer) {
    return buffer.size() >= 2 && buffer[0] == 0x78;
}
ByteBuffer decompress(const ByteBuffer& buffer) {
    // z_stream strm = {};
    // strm.next_in  = buffer.data().data();
    // strm.avail_in = static_cast<uInt>(buffer.size());
    //
    // if (inflateInit2(&strm, 15 + 16) != Z_OK) {
    //     throw std::runtime_error("Failed to initialize zlib inflater");
    // }
    //
    // ByteBuffer output;
    // output.resize(1024 * 16);
    // while (true) {
    //     strm.next_out  = output.data().data() + strm.total_out;
    //     strm.avail_out = static_cast<uInt>(output.size() - strm.total_out);
    //
    //     const int ret = inflate(&strm, Z_NO_FLUSH);
    //     if (ret == Z_STREAM_END) break;
    //     if (ret != Z_OK) {
    //         inflateEnd(&strm);
    //         throw std::runtime_error("Error while inflating NBT data");
    //     }
    //     if (strm.avail_out == 0) output.resize(output.size() * 2);
    // }
    //
    // output.resize(strm.total_out);
    // inflateEnd(&strm);
    // return output;
    z_stream strm{};
    strm.next_in = const_cast<Bytef*>(buffer.data().data());
    strm.avail_in = static_cast<uInt>(buffer.size());

    if (inflateInit2(&strm, 15 + 32) != Z_OK)
        throw std::runtime_error("inflateInit2 failed");

    ByteVec output(16 * 1024);
    while (true) {
        strm.next_out = output.data() + strm.total_out;
        strm.avail_out = static_cast<uInt>(output.size() - strm.total_out);

        int ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_STREAM_END) break;
        if (ret != Z_OK) {
            std::string err = strm.msg ? strm.msg : "unknown";
            inflateEnd(&strm);
            throw std::runtime_error("inflate failed: " + std::to_string(ret) + " (" + err + ")");
        }

        if (strm.avail_out == 0) {
            output.resize(output.size() * 2);
        }
    }

    output.resize(strm.total_out);
    inflateEnd(&strm);
    return ByteBuffer(output);
}
ByteBuffer compress(const ByteBuffer& buffer, const bool gzip) {
    z_stream strm = {};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque   = Z_NULL;
    constexpr int level = Z_DEFAULT_COMPRESSION;
    if (const int windowBits = gzip ? (15 + 16) : 15; deflateInit2(&strm, level, Z_DEFLATED, windowBits, 8, Z_DEFAULT_STRATEGY) != Z_OK)
        throw std::runtime_error("Failed to initialize zlib compressor");

    strm.next_in = const_cast<Bytef*>(buffer.data().data());
    strm.avail_in = static_cast<uInt>(buffer.size());
    ByteBuffer output;
    output.resize(1024);
    do {
        if (strm.total_out >= output.size())
            output.resize(output.size() * 2);
        strm.next_out = output.data().data() + strm.total_out;
        strm.avail_out = static_cast<uInt>(output.size() - strm.total_out);
        const int ret = deflate(&strm, Z_FINISH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            deflateEnd(&strm);
            throw std::runtime_error("Error during zlib compression");
        }

        if (ret == Z_STREAM_END) break;
    } while (strm.avail_out == 0);

    output.resize(strm.total_out);
    deflateEnd(&strm);
    return output;
}
} // namespace stratos