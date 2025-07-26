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

#include "StateManager.h"

#include "BlockState.h"

#include <iostream>
#include <numeric>
#include <ranges>

namespace stratos::block {

BlockStateManager::BlockStateManager(const Block* owner, const std::map<std::string, const IProperty*>& properties) : owner(owner), properties(properties) {
    using PropertyPair = std::pair<const IProperty*, std::any>;
    using PropertyCombination = std::vector<PropertyPair>;

    std::vector<PropertyCombination> combinations;
    combinations.emplace_back();
    for (const IProperty* property : this->properties | std::views::values) {
        std::vector<PropertyCombination> newCombinations;
        for (const PropertyCombination& combination : combinations) {
            for (auto values = property->getValuesAsAny(); const std::any& value : values) {
                PropertyPair pair(property, value);
                PropertyCombination newCombination = combination;
                newCombination.push_back(pair);
                newCombinations.push_back(std::move(newCombination));
            }
        }
        combinations = std::move(newCombinations);
    }

    for (const auto& combination : combinations) {
        size_t hash = 0;
        std::unordered_map<const IProperty*, std::any> propertyMap;
        for (const auto& [prop, val] : combination) {
            propertyMap[prop] = val;
            hash ^= prop->hashCode() ^ prop->hashValue(val) << 1;
        }
        const auto state = new BlockState(owner, &this->properties, std::move(propertyMap));
        states.push_back(state);
        stateMap[hash] = state;
    }
}
BlockStateManager::Builder& BlockStateManager::Builder::add(const IProperty* property) {
    properties[property->getName()] = property;
    return *this;
}
BlockStateManager* BlockStateManager::Builder::build(const Block* owner) const {
    return new BlockStateManager(owner, properties);
}
} // namespace stratos::block