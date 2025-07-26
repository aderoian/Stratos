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

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "StateProperty.h"

#include <map>
#include <unordered_map>

namespace stratos::block {
class Block;
class BlockState;

class BlockStateManager {
public:
    BlockStateManager(const Block* owner, const std::map<std::string, const IProperty*>& properties);

    [[nodiscard]] const std::vector<const BlockState*>& getStates() const { return states; }
    [[nodiscard]] const std::unordered_map<size_t, const BlockState*>& getStateMap() const { return stateMap; }

    class Builder {
    public:
        Builder() = default;
        template <typename... Properties> Builder& add(const Properties*... properties);
        Builder& add(const IProperty* property);
        BlockStateManager* build(const Block* owner) const;

    private:
        std::map<std::string, const IProperty*> properties;
    };

private:
    const Block* owner;
    std::map<std::string, const IProperty*> properties;
    std::vector<const BlockState*> states;
    std::unordered_map<size_t, const BlockState*> stateMap;
};
template <typename... Properties> BlockStateManager::Builder& BlockStateManager::Builder::add(const Properties*... properties) {
    (add(static_cast<const IProperty*>(properties)), ...);
    return *this;
}

} // namespace stratos::block

#endif //STATEMANAGER_H
