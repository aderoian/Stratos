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

#include "StateProperties.h"

#define BOOLEAN_PROP(codeName, name) \
    const BooleanProperty* StateProperties::codeName() { \
        static const auto* prop = BooleanProperty::create(#name); \
        return prop; \
    }
#define INT_PROP(codeName, name, min, max) \
    const IntProperty* StateProperties::codeName() { \
        static const auto* prop = IntProperty::create(#name, min, max); \
        return prop; \
    }
#define ENUM_PROP(codeName, name, enumType, values...) \
    const EnumProperty<enumType>* StateProperties::codeName() { \
        static const auto* prop = EnumProperty<enumType>::create(#name, {values}); \
        return prop; \
    }

namespace stratos::block {

BOOLEAN_PROP(ATTACHED, attached)
BOOLEAN_PROP(BERRIES, berries)
BOOLEAN_PROP(BLOOM, bloom)
BOOLEAN_PROP(BOTTOM, bottom)
BOOLEAN_PROP(CAN_SUMMON, can_summon)
BOOLEAN_PROP(CONDITIONAL, conditional)
BOOLEAN_PROP(DISARMED, disarmed)
BOOLEAN_PROP(DRAG, drag)
BOOLEAN_PROP(ENABLED, enabled)
BOOLEAN_PROP(EXTENDED, extended)
BOOLEAN_PROP(EYE, eye)
BOOLEAN_PROP(FALLING, falling)
BOOLEAN_PROP(HANGING, hanging)
BOOLEAN_PROP(HAS_BOTTLE_0, has_bottle_0)
BOOLEAN_PROP(HAS_BOTTLE_1, has_bottle_1)
BOOLEAN_PROP(HAS_BOTTLE_2, has_bottle_2)
BOOLEAN_PROP(HAS_RECORD, has_record)
BOOLEAN_PROP(HAS_BOOK, has_book)
BOOLEAN_PROP(INVERTED, inverted)
BOOLEAN_PROP(IN_WALL, in_wall)
BOOLEAN_PROP(LIT, lit)
BOOLEAN_PROP(LOCKED, locked)
BOOLEAN_PROP(NATURAL, natural)
BOOLEAN_PROP(OCCUPIED, occupied)
BOOLEAN_PROP(OPEN, open)
BOOLEAN_PROP(PERSISTENT, persistent)
BOOLEAN_PROP(POWERED, powered)
BOOLEAN_PROP(SHORT, short)
BOOLEAN_PROP(SHRIEKING, shrieking)
BOOLEAN_PROP(SIGNAL_FIRE, signal_fire)
BOOLEAN_PROP(SNOWY, snowy)
BOOLEAN_PROP(TIP, tip)
BOOLEAN_PROP(TRIGGERED, triggered)
BOOLEAN_PROP(UNSTABLE, unstable)
BOOLEAN_PROP(WATERLOGGED, waterlogged)
ENUM_PROP(HORIZONTAL_AXIS, horizontal_axis, math::Axis::Type, math::Axis::Type::X, math::Axis::Type::Z)
ENUM_PROP(AXIS, axis, math::Axis::Type, math::Axis::Type::X, math::Axis::Type::Y, math::Axis::Type::Z)
BOOLEAN_PROP(UP, up)
BOOLEAN_PROP(DOWN, down)
BOOLEAN_PROP(NORTH, north)
BOOLEAN_PROP(EAST, east)
BOOLEAN_PROP(SOUTH, south)
BOOLEAN_PROP(WEST, west)
ENUM_PROP(FACING, facing, math::Direction::Type, math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::Up, math::Direction::Type::Down)
ENUM_PROP(FACING_HOPPER, facing_hopper, math::Direction::Type, math::Direction::Type::Down, math::Direction::Type::North, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::East)
ENUM_PROP(FACING_HORIZONTAL, facing_horizontal, math::Direction::Type, math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West)
INT_PROP(FLOWER_AMOUNT, flower_amount, 1, 4)
INT_PROP(SEGMENT_AMOUNT, segment_amount, 1, 4)
ENUM_PROP(ORIENTATION, orientation, Orientation, Orientation::DownEast, Orientation::DownNorth, Orientation::DownSouth, Orientation::DownWest, Orientation::UpEast, Orientation::UpNorth, Orientation::UpSouth, Orientation::UpWest, Orientation::WestUp, Orientation::EastUp, Orientation::NorthUp, Orientation::SouthUp)
ENUM_PROP(BLOCK_FACE, block_face, BlockFace, BlockFace::Floor, BlockFace::Wall, BlockFace::Ceiling)
ENUM_PROP(ATTACHMENT, attachment, Attachment, Attachment::Floor, Attachment::Ceiling, Attachment::SingleWall, Attachment::DoubleWall)
ENUM_PROP(EAST_WALL_SHAPE, east, WallConnection, WallConnection::None, WallConnection::Low, WallConnection::Tall)
ENUM_PROP(NORTH_WALL_SHAPE, north, WallConnection, WallConnection::None, WallConnection::Low, WallConnection::Tall)
ENUM_PROP(SOUTH_WALL_SHAPE, south, WallConnection, WallConnection::None, WallConnection::Low, WallConnection::Tall)
ENUM_PROP(WEST_WALL_SHAPE, west, WallConnection, WallConnection::None, WallConnection::Low, WallConnection::Tall)
ENUM_PROP(EAST_WIRE_CONNECTION, east, WireConnection, WireConnection::Up, WireConnection::Side, WireConnection::None)
ENUM_PROP(NORTH_WIRE_CONNECTION, north, WireConnection, WireConnection::Up, WireConnection::Side, WireConnection::None)
ENUM_PROP(SOUTH_WIRE_CONNECTION, south, WireConnection, WireConnection::Up, WireConnection::Side, WireConnection::None)
ENUM_PROP(WEST_WIRE_CONNECTION, west, WireConnection, WireConnection::Up, WireConnection::Side, WireConnection::None)
ENUM_PROP(DOUBLE_BLOCK_HALF, half, DoubleBlockHalf, DoubleBlockHalf::Upper, DoubleBlockHalf::Lower)
ENUM_PROP(BLOCK_HALF, half, BlockHalf, BlockHalf::Top, BlockHalf::Bottom)
ENUM_PROP(RAIL_SHAPE, shape, RailConnection, RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest, RailConnection::SouthEast, RailConnection::SouthWest, RailConnection::NorthEast, RailConnection::NorthWest)
ENUM_PROP(STRAIGHT_RAIL_SHAPE, shape, RailConnection, RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest)
INT_PROP(AGE_1, age, 0, 1)
INT_PROP(AGE_2, age, 0, 2)
INT_PROP(AGE_3, age, 0, 3)
INT_PROP(AGE_4, age, 0, 4)
INT_PROP(AGE_5, age, 0, 5)
INT_PROP(AGE_7, age, 0, 7)
INT_PROP(AGE_15, age, 0, 15)
INT_PROP(AGE_25, age, 0, 25)
INT_PROP(BITES, bites, 0, 6)
INT_PROP(CANDLES, candles, 1, 4)
INT_PROP(DELAY, delay, 1, 4)
INT_PROP(DISTANCE_1_7, distance, 1, 7)
INT_PROP(EGGS, eggs, 1, 4)
INT_PROP(HATCH, hatch, 0, 2)
INT_PROP(LAYERS, layers, 1, 8)
INT_PROP(LEVEL_3, level, 1, 3)
INT_PROP(LEVEL_8, level, 0, 8)
INT_PROP(LEVEL_1_8, level, 1, 8)
INT_PROP(HONEY_LEVEL, honey_level, 0, 5)
INT_PROP(LEVEL_15, level, 0, 15)
INT_PROP(MOISTURE, moisture, 0, 7)
INT_PROP(NOTE, note, 0, 24)
INT_PROP(PICKLES, pickles, 1, 4)
INT_PROP(POWER, power, 0, 15)
INT_PROP(STAGE, stage, 0, 1)
INT_PROP(DISTANCE_0_7, distance, 0, 7)
INT_PROP(CHARGES, charges, 0, 4)
INT_PROP(ROTATION, rotation, 0, 15)
ENUM_PROP(BED_PART, part, BedPart, BedPart::Head, BedPart::Foot)
ENUM_PROP(CHEST_TYPE, type, ChestType, ChestType::Single, ChestType::Left, ChestType::Right)
ENUM_PROP(COMPARATOR_MODE, mode, ComparatorMode, ComparatorMode::Compare, ComparatorMode::Subtract)
ENUM_PROP(DOOR_HINGE, hinge, DoorHinge, DoorHinge::Left, DoorHinge::Right)
ENUM_PROP(INSTRUMENT, instrument, NoteBlockInstrument, NoteBlockInstrument::Harp, NoteBlockInstrument::BassDrum, NoteBlockInstrument::Snare, NoteBlockInstrument::Hat, NoteBlockInstrument::Bass, NoteBlockInstrument::Flute, NoteBlockInstrument::Bell, NoteBlockInstrument::Guitar, NoteBlockInstrument::Chime, NoteBlockInstrument::Xylophone, NoteBlockInstrument::IronXylophone, NoteBlockInstrument::CowBell, NoteBlockInstrument::Didgeridoo, NoteBlockInstrument::Bit, NoteBlockInstrument::Banjo, NoteBlockInstrument::Pling, NoteBlockInstrument::Zombie, NoteBlockInstrument::Skeleton, NoteBlockInstrument::Creeper, NoteBlockInstrument::Dragon, NoteBlockInstrument::WitherSkeleton, NoteBlockInstrument::Piglin, NoteBlockInstrument::CustomHead)
ENUM_PROP(PISTON_TYPE, type, PistonType, PistonType::Default, PistonType::Sticky)
ENUM_PROP(SLAB_TYPE, type, SlabType, SlabType::Top, SlabType::Bottom, SlabType::Double)
ENUM_PROP(STAIR_SHAPE, shape, StairShape, StairShape::Straight, StairShape::InnerLeft, StairShape::InnerRight, StairShape::OuterLeft, StairShape::OuterRight)
ENUM_PROP(STRUCTURE_BLOCK_MODE, mode, StructureBlockMode, StructureBlockMode::Save, StructureBlockMode::Load, StructureBlockMode::Corner, StructureBlockMode::Data)
ENUM_PROP(BAMBOO_LEAVES, leaves, BambooLeaves, BambooLeaves::None, BambooLeaves::Small, BambooLeaves::Large)
ENUM_PROP(TILT, tilt, Tilt, Tilt::None, Tilt::Unstable, Tilt::Partial, Tilt::Full)
ENUM_PROP(VERTICAL_DIRECTION, vertical_direction, math::Direction::Type, math::Direction::Type::Up, math::Direction::Type::Down)
ENUM_PROP(THICKNESS, thickness, Thickness, Thickness::TipMerge, Thickness::Tip, Thickness::Frustum, Thickness::Middle, Thickness::Base)
ENUM_PROP(SCULK_SENSOR_PHASE, phase, SculkSensorPhase, SculkSensorPhase::Inactive, SculkSensorPhase::Active, SculkSensorPhase::Cooldown)
BOOLEAN_PROP(SLOT_0_OCCUPIED, slot_0_occupied)
BOOLEAN_PROP(SLOT_1_OCCUPIED, slot_1_occupied)
BOOLEAN_PROP(SLOT_2_OCCUPIED, slot_2_occupied)
BOOLEAN_PROP(SLOT_3_OCCUPIED, slot_3_occupied)
BOOLEAN_PROP(SLOT_4_OCCUPIED, slot_4_occupied)
BOOLEAN_PROP(SLOT_5_OCCUPIED, slot_5_occupied)
INT_PROP(DUSTED, dusted, 0, 3)
BOOLEAN_PROP(CRACKED, cracked)
BOOLEAN_PROP(CRAFTING, crafting)
ENUM_PROP(TRIAL_SPAWNER_STATE, trial_spawner_state, TrialSpawnerState, TrialSpawnerState::Inactive, TrialSpawnerState::WaitingForPlayers, TrialSpawnerState::Active, TrialSpawnerState::WaitingForRewardEjection, TrialSpawnerState::EjectingReward, TrialSpawnerState::Cooldown)
ENUM_PROP(VAULT_STATE, vault_state, VaultState, VaultState::Inactive, VaultState::Active, VaultState::Unlocking, VaultState::Ejecting)
ENUM_PROP(CREAKING_HEART_STATE, creaking_heart_state, CreakingHeartState, CreakingHeartState::Uprooted, CreakingHeartState::Dormant, CreakingHeartState::Awake)
BOOLEAN_PROP(OMINOUS, ominous)
ENUM_PROP(TEST_BLOCK_MODE, test_block_mode, TestBlockMode, TestBlockMode::Start, TestBlockMode::Log, TestBlockMode::Fail, TestBlockMode::Accept)
BOOLEAN_PROP(MAP, map)

} // namespace stratos::block