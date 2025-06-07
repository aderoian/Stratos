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

#ifndef NBTCOMPRESSION_H
#define NBTCOMPRESSION_H

namespace stratos {
class ByteBuffer;
}
namespace stratos {

bool isGzip(const ByteBuffer& buffer);
bool isZlib(const ByteBuffer& buffer);

ByteBuffer decompress(ByteBuffer& buffer);
ByteBuffer compress(const ByteBuffer& buffer, bool gzip = false);

} // namespace stratos

#endif //NBTCOMPRESSION_H
