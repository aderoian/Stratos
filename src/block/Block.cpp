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

#include "Block.h"

#include "registry/Registries.h"

namespace stratos::block {
Block::Block() {
    stateManager = BlockStateManager::Builder().build(this);
}
Block::Block(const BlockStateManager::Builder& stateBuilder) : stateManager(stateBuilder.build(this)) {}
std::string Block::getName() const {
    return registry::Registries::BLOCKS()->getEntry(this).toString();
}
const BlockStateManager* Block::getStateManager() const { return stateManager;}
};