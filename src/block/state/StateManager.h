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

class PropertyMap {
public:
    PropertyMap() = default;

    bool operator==(const PropertyMap& other) const;
    bool operator!=(const PropertyMap& other) const;

    [[nodiscard]] const std::map<const IProperty*, IProperty::IValue*>& getValues() const;
    [[nodiscard]] IProperty::IValue* get(const IProperty& property) const;
    [[nodiscard]] bool contains(const IProperty& property) const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] std::string toString() const;

    [[nodiscard]] size_t hashCode() const;

    void set(const IProperty& property, IProperty::IValue* value);
private:
    std::map<const IProperty*, IProperty::IValue*> values;
};

class BlockStateManager {
public:
    BlockStateManager(const Block* owner, std::map<std::string, const IProperty*>&& properties);

    class Builder {
    public:
        explicit Builder(const Block* owner);
        template <typename... Properties> Builder& add(const Properties*... properties);
        Builder& add(const IProperty* property);
        BlockStateManager* build();

    private:
        const Block* owner;
        std::map<std::string, const IProperty*> properties;
    };

private:
    const Block* owner;
    std::map<std::string, const IProperty*> properties;
    std::vector<const BlockState*> states;
    std::unordered_map<size_t, const BlockState*> stateMap;
};
template <typename... Properties> BlockStateManager::Builder& BlockStateManager::Builder::add(const Properties*... properties) {
    (add(properties), ...);
    return *this;
}

} // namespace stratos::block

#endif //STATEMANAGER_H
