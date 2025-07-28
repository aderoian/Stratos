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

#ifndef REGISTRIES_H
#define REGISTRIES_H

#include "Registry.h"

namespace stratos {
namespace block {
class Block;
} // namespace block
namespace world {
class Biome;
} // namespace world
namespace registry {

class Registries {
public:
    static Registry<const block::Block*>* BLOCKS();
    static Registry<const world::Biome*>* BIOMES();
};
} // namespace registry
} // namespace stratos

#endif //REGISTRIES_H
