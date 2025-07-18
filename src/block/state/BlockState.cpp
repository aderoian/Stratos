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

#include "BlockState.h"

#include "block/Block.h"
#include "registry/Registries.h"

namespace stratos::block {

BlockState::BlockState(const Block* block, const std::map<std::string, const IProperty*>* properties, std::unordered_map<const IProperty*, std::any>&& propertyValues) : owner(block), properties(properties), propertyValues(std::move(propertyValues)) {}
std::string BlockState::toString() const {
    std::string result = "Block{"+owner->getName()+"}";
    if (properties->empty()) return result;
    result += "[";
    for (const auto& [name, property] : *properties) {
        result += name + "=" + property->toString(propertyValues.at(property)) + ",";
    }
    result.pop_back();
    result += "]";
    return result;
}
} // namespace stratos::block