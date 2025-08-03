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

#include "Registries.h"

#include "block/Block.h"

namespace stratos::registry {
Registry<const block::Block*>* Registries::BLOCKS() {
    static auto* registry = new Registry<const block::Block*>({utils::Identifier("minecraft", "root"), utils::Identifier("minecraft", "block")});
    return registry;
}
DynamicRegistry<const world::Biome*>* Registries::BIOMES() {
    static auto* registry = new DynamicRegistry<const world::Biome*>({utils::Identifier("minecraft", "worldgen"), utils::Identifier("minecraft", "biome")});
    return registry;
}
} // namespace stratos::registry