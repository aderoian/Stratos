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
#include <any>
#include <map>

namespace stratos::block {
class IProperty;

class Block;
/**
 * Represents the state of a block (dynamic properties) in the world.
 */
class BlockState {
public:
    BlockState(const Block* block, std::map<const IProperty*, std::any>&& properties);
    bool operator==(const BlockState& other) const {
        return true;
    }
private:
    const Block* owner;
    std::map<const IProperty*, std::any> properties;
};
} // namespace stratos::block

#endif //BLOCKSTATE_H
