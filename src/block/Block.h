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

#ifndef BLOCK_H
#define BLOCK_H
#include "state/StateManager.h"

namespace stratos::block {
class BlockStateManager;
class Block {
public:
    explicit Block();
    explicit Block(const BlockStateManager::Builder& stateBuilder);
    ~Block() = default;

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] const BlockStateManager* getStateManager() const;
private:
    BlockStateManager* stateManager;
};

enum class Orientation {
    Down_East,
    Down_North,
    Down_South,
    Down_West,
    Up_East,
    Up_North,
    Up_South,
    Up_West,
    West_Up,
    East_Up,
    North_Up,
    South_Up
};

enum class BlockFace {
    Floor,
    Wall,
    Ceiling
};

enum class Attachment {
    Floor,
    Ceiling,
    Single_Wall,
    Double_Wall
};

enum class WallConnection {
    None,
    Low,
    Tall
};

enum class WireConnection {
    Up,
    Side,
    None
};

enum class DoubleBlockHalf {
    Upper,
    Lower
};

enum class BlockHalf {
    Top,
    Bottom
};

enum class RailConnection {
    North_South,
    East_West,
    Ascending_East,
    Ascending_West,
    Ascending_North,
    Ascending_South,
    South_East,
    South_West,
    North_West,
    North_East
};

enum class BedPart {
    Head,
    Foot
};

enum class ChestType {
    Single,
    Left,
    Right
};

enum class ComparatorMode {
    Compare,
    Subtract
};

enum class DoorHinge {
    Left,
    Right
};

enum class NoteBlockInstrument {
    Harp,
    BaseDrum,
    Snare,
    Hat,
    Bass,
    Flute,
    Bell,
    Guitar,
    Chime,
    Xylophone,
    Iron_Xylophone,
    Cow_Bell,
    Didgeridoo,
    Bit,
    Banjo,
    Pling,
    Zombie,
    Skeleton,
    Creeper,
    Dragon,
    Wither_Skeleton,
    Piglin,
    Custom_Head
};

enum class PistonType {
    Normal,
    Sticky
};

enum class SlabType {
    Top,
    Bottom,
    Double
};

enum class StairShape {
    Straight,
    Inner_Left,
    Inner_Right,
    Outer_Left,
    Outer_Right
};

enum class StructureBlockMode {
    Save,
    Load,
    Corner,
    Data
};

enum class BambooLeaves {
    None,
    Small,
    Large
};

enum class Tilt {
    None,
    Unstable,
    Partial,
    Full
};

enum class Thickness {
    Tip_Merge,
    Tip,
    Frustum,
    Middle,
    Base
};

enum class SculkSensorPhase {
    Inactive,
    Active,
    Cooldown
};

enum class TrialSpawnerState {
    Inactive,
    Waiting_For_Players,
    Active,
    Waiting_For_Reward_Ejection,
    Ejecting_Reward,
    Cooldown
};

enum class VaultState {
    Inactive,
    Active,
    Unlocking,
    Ejecting
};

enum class CreakingHeartState {
    Uprooted,
    Dormant,
    Awake
};

enum class TestBlockMode {
    Start,
    Log,
    Fail,
    Accept
};
} // namespace stratos::block

#endif //BLOCK_H
