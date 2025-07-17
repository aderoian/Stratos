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

    [[nodiscard]] const BlockStateManager* getStateManager() const;
private:
    BlockStateManager* stateManager;
};

enum class Orientation {
    DownEast,
    DownNorth,
    DownSouth,
    DownWest,
    UpEast,
    UpNorth,
    UpSouth,
    UpWest,
    WestUp,
    EastUp,
    NorthUp,
    SouthUp
};

enum class BlockFace {
    Floor,
    Wall,
    Ceiling
};

enum class Attachment {
    Floor,
    Ceiling,
    SingleWall,
    DoubleWall
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
    NorthSouth,
    EastWest,
    AscendingEast,
    AscendingWest,
    AscendingNorth,
    AscendingSouth,
    SouthEast,
    SouthWest,
    NorthWest,
    NorthEast
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
    BassDrum,
    Snare,
    Hat,
    Bass,
    Flute,
    Bell,
    Guitar,
    Chime,
    Xylophone,
    IronXylophone,
    CowBell,
    Didgeridoo,
    Bit,
    Banjo,
    Pling,
    Zombie,
    Skeleton,
    Creeper,
    Dragon,
    WitherSkeleton,
    Piglin,
    CustomHead
};

enum class PistonType {
    Default,
    Sticky
};

enum class SlabType {
    Top,
    Bottom,
    Double
};

enum class StairShape {
    Straight,
    InnerLeft,
    InnerRight,
    OuterLeft,
    OuterRight
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
    TipMerge,
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
    WaitingForPlayers,
    Active,
    WaitingForRewardEjection,
    EjectingReward,
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
