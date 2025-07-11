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

#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

namespace stratos::block {

class Block;
/**
 * Represents the state of a block (dynamic properties) in the world.
 */
class BlockState {
public:
    BlockState() = default;
    bool operator==(const BlockState& other) const {
        return true;
    }
};
} // namespace stratos::block

#endif //BLOCKSTATE_H
