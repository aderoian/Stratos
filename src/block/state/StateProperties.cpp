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

namespace stratos::block {
const BooleanProperty* StateProperties::ATTACHED = BooleanProperty::create("attached");
const BooleanProperty* StateProperties::BERRIES = BooleanProperty::create("berries");
const BooleanProperty* StateProperties::BLOOM = BooleanProperty::create("bloom");
const BooleanProperty* StateProperties::BOTTOM = BooleanProperty::create("bottom");
const BooleanProperty* StateProperties::CAN_SUMMON = BooleanProperty::create("can_summon");
const BooleanProperty* StateProperties::CONDITIONAL = BooleanProperty::create("conditional");
const BooleanProperty* StateProperties::DISARMED = BooleanProperty::create("disarmed");
const BooleanProperty* StateProperties::DRAG = BooleanProperty::create("drag");
const BooleanProperty* StateProperties::ENABLED = BooleanProperty::create("enabled");
const BooleanProperty* StateProperties::EXTENDED = BooleanProperty::create("extended");
const BooleanProperty* StateProperties::EYE = BooleanProperty::create("eye");
const BooleanProperty* StateProperties::FALLING = BooleanProperty::create("falling");
const BooleanProperty* StateProperties::HANGING = BooleanProperty::create("hanging");
const BooleanProperty* StateProperties::HAS_BOTTLE_0 = BooleanProperty::create("has_bottle_0");
const BooleanProperty* StateProperties::HAS_BOTTLE_1 = BooleanProperty::create("has_bottle_1");
const BooleanProperty* StateProperties::HAS_BOTTLE_2 = BooleanProperty::create("has_bottle_2");
const BooleanProperty* StateProperties::HAS_RECORD = BooleanProperty::create("has_record");
const BooleanProperty* StateProperties::HAS_BOOK = BooleanProperty::create("has_book");
const BooleanProperty* StateProperties::INVERTED = BooleanProperty::create("inverted");
const BooleanProperty* StateProperties::IN_WALL = BooleanProperty::create("in_wall");
const BooleanProperty* StateProperties::LIT = BooleanProperty::create("lit");
const BooleanProperty* StateProperties::LOCKED = BooleanProperty::create("locked");
const BooleanProperty* StateProperties::NATURAL = BooleanProperty::create("natural");
const BooleanProperty* StateProperties::OCCUPIED = BooleanProperty::create("occupied");
const BooleanProperty* StateProperties::OPEN = BooleanProperty::create("open");
const BooleanProperty* StateProperties::PERSISTENT = BooleanProperty::create("persistent");
const BooleanProperty* StateProperties::POWERED = BooleanProperty::create("powered");
const BooleanProperty* StateProperties::SHORT = BooleanProperty::create("short");
const BooleanProperty* StateProperties::SHRIEKING = BooleanProperty::create("shrieking");
const BooleanProperty* StateProperties::SIGNAL_FIRE = BooleanProperty::create("signal_fire");
const BooleanProperty* StateProperties::SNOWY = BooleanProperty::create("snowy");
const BooleanProperty* StateProperties::TIP = BooleanProperty::create("tip");
const BooleanProperty* StateProperties::TRIGGERED = BooleanProperty::create("triggered");
const BooleanProperty* StateProperties::UNSTABLE = BooleanProperty::create("unstable");
const BooleanProperty* StateProperties::WATERLOGGED = BooleanProperty::create("waterlogged");
const EnumProperty<math::Axis::Type>* StateProperties::HORIZONTAL_AXIS = EnumProperty<math::Axis::Type>::create("axis", {math::Axis::Type::X, math::Axis::Type::Z});
const EnumProperty<math::Axis::Type>* StateProperties::AXIS = EnumProperty<math::Axis::Type>::create("axis", {math::Axis::Type::X, math::Axis::Type::Y, math::Axis::Type::Z});
const BooleanProperty* StateProperties::UP = BooleanProperty::create("up");
const BooleanProperty* StateProperties::DOWN = BooleanProperty::create("down");
const BooleanProperty* StateProperties::NORTH = BooleanProperty::create("north");
const BooleanProperty* StateProperties::EAST = BooleanProperty::create("east");
const BooleanProperty* StateProperties::SOUTH = BooleanProperty::create("south");
const BooleanProperty* StateProperties::WEST = BooleanProperty::create("west");
const EnumProperty<math::Direction::Type>* StateProperties::FACING = EnumProperty<math::Direction::Type>::create("facing", {math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::Up, math::Direction::Type::Down});
const EnumProperty<math::Direction::Type>* StateProperties::FACING_HOPPER = EnumProperty<math::Direction::Type>::create("facing", {math::Direction::Type::Down, math::Direction::Type::North, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::East});
const EnumProperty<math::Direction::Type>* StateProperties::FACING_HORIZONTAL = EnumProperty<math::Direction::Type>::create("facing", {math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West});
const IntProperty* StateProperties::FLOWER_AMOUNT = IntProperty::create("flower_amount", 1, 4);
const IntProperty* StateProperties::SEGMENT_AMOUNT = IntProperty::create("flower_amount", 1, 4);
const EnumProperty<Orientation>* StateProperties::ORIENTATION = EnumProperty<Orientation>::create("orientation", {Orientation::DownEast, Orientation::DownNorth, Orientation::DownSouth, Orientation::DownWest, Orientation::UpEast, Orientation::UpNorth, Orientation::UpSouth, Orientation::UpWest, Orientation::WestUp, Orientation::EastUp, Orientation::NorthUp, Orientation::SouthUp});
const EnumProperty<BlockFace>* StateProperties::BLOCK_FACE = EnumProperty<BlockFace>::create("block_face", {BlockFace::Floor, BlockFace::Wall, BlockFace::Ceiling});
const EnumProperty<Attachment>* StateProperties::ATTACHMENT = EnumProperty<Attachment>::create("attachment", {Attachment::Floor, Attachment::Ceiling, Attachment::SingleWall, Attachment::DoubleWall});
const EnumProperty<WallConnection>* StateProperties::EAST_WALL_SHAPE = EnumProperty<WallConnection>::create("east", {WallConnection::None, WallConnection::Low, WallConnection::Tall});
const EnumProperty<WallConnection>* StateProperties::NORTH_WALL_SHAPE = EnumProperty<WallConnection>::create("north", {WallConnection::None, WallConnection::Low, WallConnection::Tall});
const EnumProperty<WallConnection>* StateProperties::SOUTH_WALL_SHAPE = EnumProperty<WallConnection>::create("south", {WallConnection::None, WallConnection::Low, WallConnection::Tall});
const EnumProperty<WallConnection>* StateProperties::WEST_WALL_SHAPE = EnumProperty<WallConnection>::create("west", {WallConnection::None, WallConnection::Low, WallConnection::Tall});
const EnumProperty<WireConnection>* StateProperties::EAST_WIRE_CONNECTION = EnumProperty<WireConnection>::create("east", {WireConnection::Up, WireConnection::Side, WireConnection::None});
const EnumProperty<WireConnection>* StateProperties::NORTH_WIRE_CONNECTION = EnumProperty<WireConnection>::create("north", {WireConnection::Up, WireConnection::Side, WireConnection::None});
const EnumProperty<WireConnection>* StateProperties::SOUTH_WIRE_CONNECTION = EnumProperty<WireConnection>::create("south", {WireConnection::Up, WireConnection::Side, WireConnection::None});
const EnumProperty<WireConnection>* StateProperties::WEST_WIRE_CONNECTION = EnumProperty<WireConnection>::create("west", {WireConnection::Up, WireConnection::Side, WireConnection::None});
const EnumProperty<DoubleBlockHalf>* StateProperties::DOUBLE_BLOCK_HALF = EnumProperty<DoubleBlockHalf>::create("half", {DoubleBlockHalf::Upper, DoubleBlockHalf::Lower});
const EnumProperty<BlockHalf>* StateProperties::BLOCK_HALF = EnumProperty<BlockHalf>::create("half", {BlockHalf::Top, BlockHalf::Bottom});
const EnumProperty<RailConnection>* StateProperties::RAIL_SHAPE = EnumProperty<RailConnection>::create("shape", {RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest, RailConnection::SouthEast, RailConnection::SouthWest, RailConnection::NorthEast, RailConnection::NorthWest});
const EnumProperty<RailConnection>* StateProperties::STRAIGHT_RAIL_SHAPE = EnumProperty<RailConnection>::create("shape", {RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest});
const IntProperty* StateProperties::AGE_1 = IntProperty::create("age", 0, 1);
const IntProperty* StateProperties::AGE_2 = IntProperty::create("age", 0, 2);
const IntProperty* StateProperties::AGE_3 = IntProperty::create("age", 0, 3);
const IntProperty* StateProperties::AGE_4 = IntProperty::create("age", 0, 4);
const IntProperty* StateProperties::AGE_5 = IntProperty::create("age", 0, 5);
const IntProperty* StateProperties::AGE_7 = IntProperty::create("age", 0, 7);
const IntProperty* StateProperties::AGE_15 = IntProperty::create("age", 0, 15);
const IntProperty* StateProperties::AGE_25 = IntProperty::create("age", 0, 25);
const IntProperty* StateProperties::BITES = IntProperty::create("bites", 0, 6);
const IntProperty* StateProperties::CANDLES = IntProperty::create("candles", 1, 4);
const IntProperty* StateProperties::DELAY = IntProperty::create("delay", 1, 4);
const IntProperty* StateProperties::DISTANCE_1_7 = IntProperty::create("distance", 1, 7);
const IntProperty* StateProperties::EGGS = IntProperty::create("eggs", 1, 4);
const IntProperty* StateProperties::HATCH = IntProperty::create("hatch", 0, 2);
const IntProperty* StateProperties::LAYERS = IntProperty::create("layers", 1, 8);
const IntProperty* StateProperties::LEVEL_3 = IntProperty::create("level", 1, 3);
const IntProperty* StateProperties::LEVEL_8 = IntProperty::create("level", 0, 8);
const IntProperty* StateProperties::LEVEL_1_8 = IntProperty::create("level", 1, 8);
const IntProperty* StateProperties::HONEY_LEVEL = IntProperty::create("honey_level", 0, 5);
const IntProperty* StateProperties::LEVEL_15 = IntProperty::create("level", 0, 15);
const IntProperty* StateProperties::MOISTURE = IntProperty::create("moisture", 0, 7);
const IntProperty* StateProperties::NOTE = IntProperty::create("note", 0, 24);
const IntProperty* StateProperties::PICKLES = IntProperty::create("pickles", 1, 4);
const IntProperty* StateProperties::POWER = IntProperty::create("power", 0, 15);
const IntProperty* StateProperties::STAGE = IntProperty::create("stage", 0, 1);
const IntProperty* StateProperties::DISTANCE_0_7 = IntProperty::create("distance", 0, 7);
const IntProperty* StateProperties::CHARGES = IntProperty::create("charges", 0, 4);
const IntProperty* StateProperties::ROTATION = IntProperty::create("rotation", 0, 15);
const EnumProperty<BedPart>* StateProperties::BED_PART = EnumProperty<BedPart>::create("part", {BedPart::Head, BedPart::Foot});
const EnumProperty<ChestType>* StateProperties::CHEST_TYPE = EnumProperty<ChestType>::create("type", {ChestType::Single, ChestType::Left, ChestType::Right});
const EnumProperty<ComparatorMode>* StateProperties::COMPARATOR_MODE = EnumProperty<ComparatorMode>::create("mode", {ComparatorMode::Compare, ComparatorMode::Subtract});
const EnumProperty<DoorHinge>* StateProperties::DOOR_HINGE = EnumProperty<DoorHinge>::create("hinge", {DoorHinge::Left, DoorHinge::Right});
const EnumProperty<NoteBlockInstrument>* StateProperties::INSTRUMENT = EnumProperty<NoteBlockInstrument>::create("instrument", {NoteBlockInstrument::Harp, NoteBlockInstrument::BassDrum, NoteBlockInstrument::Snare, NoteBlockInstrument::Hat, NoteBlockInstrument::Bass, NoteBlockInstrument::Flute, NoteBlockInstrument::Bell, NoteBlockInstrument::Guitar, NoteBlockInstrument::Chime, NoteBlockInstrument::Xylophone, NoteBlockInstrument::IronXylophone, NoteBlockInstrument::CowBell, NoteBlockInstrument::Didgeridoo, NoteBlockInstrument::Bit, NoteBlockInstrument::Banjo, NoteBlockInstrument::Pling, NoteBlockInstrument::Zombie, NoteBlockInstrument::Skeleton, NoteBlockInstrument::Creeper, NoteBlockInstrument::Dragon, NoteBlockInstrument::WitherSkeleton, NoteBlockInstrument::Piglin, NoteBlockInstrument::CustomHead});
const EnumProperty<PistonType>* StateProperties::PISTON_TYPE = EnumProperty<PistonType>::create("type", {PistonType::Default, PistonType::Sticky});
const EnumProperty<SlabType>* StateProperties::SLAB_TYPE = EnumProperty<SlabType>::create("type", {SlabType::Top, SlabType::Bottom, SlabType::Double});
const EnumProperty<StairShape>* StateProperties::STAIR_SHAPE = EnumProperty<StairShape>::create("shape", {StairShape::Straight, StairShape::InnerLeft, StairShape::InnerRight, StairShape::OuterLeft, StairShape::OuterRight});
const EnumProperty<StructureBlockMode>* StateProperties::STRUCTURE_BLOCK_MODE = EnumProperty<StructureBlockMode>::create("mode", {StructureBlockMode::Save, StructureBlockMode::Load, StructureBlockMode::Corner, StructureBlockMode::Data});
const EnumProperty<BambooLeaves>* StateProperties::BAMBOO_LEAVES = EnumProperty<BambooLeaves>::create("leaves", {BambooLeaves::None, BambooLeaves::Small, BambooLeaves::Large});
const EnumProperty<Tilt>* StateProperties::TILT = EnumProperty<Tilt>::create("tilt", {Tilt::None, Tilt::Unstable, Tilt::Partial, Tilt::Full});
const EnumProperty<math::Direction::Type>* StateProperties::VERTICAL_DIRECTION = EnumProperty<math::Direction::Type>::create("vertical_direction", {math::Direction::Type::Up, math::Direction::Type::Down});
const EnumProperty<Thickness>* StateProperties::THICKNESS = EnumProperty<Thickness>::create("thickness", {Thickness::TipMerge, Thickness::Tip, Thickness::Frustum, Thickness::Middle, Thickness::Base});
const EnumProperty<SculkSensorPhase>* StateProperties::SCULK_SENSOR_PHASE = EnumProperty<SculkSensorPhase>::create("phase", {SculkSensorPhase::Inactive, SculkSensorPhase::Active, SculkSensorPhase::Cooldown});
const BooleanProperty* StateProperties::SLOT_0_OCCUPIED = BooleanProperty::create("slot_0_occupied");
const BooleanProperty* StateProperties::SLOT_1_OCCUPIED = BooleanProperty::create("slot_1_occupied");
const BooleanProperty* StateProperties::SLOT_2_OCCUPIED = BooleanProperty::create("slot_2_occupied");
const BooleanProperty* StateProperties::SLOT_3_OCCUPIED = BooleanProperty::create("slot_3_occupied");
const BooleanProperty* StateProperties::SLOT_4_OCCUPIED = BooleanProperty::create("slot_4_occupied");
const BooleanProperty* StateProperties::SLOT_5_OCCUPIED = BooleanProperty::create("slot_5_occupied");
const IntProperty* StateProperties::DUSTED = IntProperty::create("dusted", 0, 3);
const BooleanProperty* StateProperties::CRACKED = BooleanProperty::create("cracked");
const BooleanProperty* StateProperties::CRAFTING = BooleanProperty::create("crafting");
const EnumProperty<TrialSpawnerState>* StateProperties::TRIAL_SPAWNER_STATE = EnumProperty<TrialSpawnerState>::create("trial_spawner_state", {TrialSpawnerState::Inactive, TrialSpawnerState::WaitingForPlayers, TrialSpawnerState::Active, TrialSpawnerState::WaitingForRewardEjection, TrialSpawnerState::EjectingReward, TrialSpawnerState::Cooldown});
const EnumProperty<VaultState>* StateProperties::VAULT_STATE = EnumProperty<VaultState>::create("vault_state", {VaultState::Inactive, VaultState::Active, VaultState::Unlocking, VaultState::Ejecting});
const EnumProperty<CreakingHeartState>* StateProperties::CREAKING_HEART_STATE = EnumProperty<CreakingHeartState>::create("creaking_heart_state", {CreakingHeartState::Uprooted, CreakingHeartState::Dormant, CreakingHeartState::Awake});
const BooleanProperty* StateProperties::OMINOUS = BooleanProperty::create("ominous");
const EnumProperty<TestBlockMode>* StateProperties::TEST_BLOCK_MODE = EnumProperty<TestBlockMode>::create("mode", {TestBlockMode::Start, TestBlockMode::Log, TestBlockMode::Fail, TestBlockMode::Accept});
const BooleanProperty* StateProperties::MAP = BooleanProperty::create("map");
} // nnamespace stratos::block;