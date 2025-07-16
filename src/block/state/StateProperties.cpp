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
const BooleanProperty* ATTACHED = BooleanProperty::create("attached");
const BooleanProperty* BERRIES = BooleanProperty::create("berries");
const BooleanProperty* BLOOM = BooleanProperty::create("bloom");
const BooleanProperty* BOTTOM = BooleanProperty::create("bottom");
const BooleanProperty* CAN_SUMMON = BooleanProperty::create("can_summon");
const BooleanProperty* CONDITIONAL = BooleanProperty::create("conditional");
const BooleanProperty* DISARMED = BooleanProperty::create("disarmed");
const BooleanProperty* DRAG = BooleanProperty::create("drag");
const BooleanProperty* ENABLED = BooleanProperty::create("enabled");
const BooleanProperty* EXTENDED = BooleanProperty::create("extended");
const BooleanProperty* EYE = BooleanProperty::create("eye");
const BooleanProperty* FALLING = BooleanProperty::create("falling");
const BooleanProperty* HANGING = BooleanProperty::create("hanging");
const BooleanProperty* HAS_BOTTLE_0 = BooleanProperty::create("has_bottle_0");
const BooleanProperty* HAS_BOTTLE_1 = BooleanProperty::create("has_bottle_1");
const BooleanProperty* HAS_BOTTLE_2 = BooleanProperty::create("has_bottle_2");
const BooleanProperty* HAS_RECORD = BooleanProperty::create("has_record");
const BooleanProperty* HAS_BOOK = BooleanProperty::create("has_book");
const BooleanProperty* INVERTED = BooleanProperty::create("inverted");
const BooleanProperty* IN_WALL = BooleanProperty::create("in_wall");
const BooleanProperty* LIT = BooleanProperty::create("lit");
const BooleanProperty* LOCKED = BooleanProperty::create("locked");
const BooleanProperty* NATURAL = BooleanProperty::create("natural");
const BooleanProperty* OCCUPIED = BooleanProperty::create("occupied");
const BooleanProperty* OPEN = BooleanProperty::create("open");
const BooleanProperty* PERSISTENT = BooleanProperty::create("persistent");
const BooleanProperty* POWERED = BooleanProperty::create("powered");
const BooleanProperty* SHORT = BooleanProperty::create("short");
const BooleanProperty* SHRIEKING = BooleanProperty::create("shrieking");
const BooleanProperty* SIGNAL_FIRE = BooleanProperty::create("signal_fire");
const BooleanProperty* SNOWY = BooleanProperty::create("snowy");
const BooleanProperty* TIP = BooleanProperty::create("tip");
const BooleanProperty* TRIGGERED = BooleanProperty::create("triggered");
const BooleanProperty* UNSTABLE = BooleanProperty::create("unstable");
const BooleanProperty* WATERLOGGED = BooleanProperty::create("waterlogged");
const EnumProperty<math::Axis::Type>* HORIZONTAL_AXIS = EnumProperty<math::Axis::Type>::create("axis", math::Axis::Type::X, math::Axis::Type::Z);
const EnumProperty<math::Axis>* AXIS = EnumProperty<math::Axis>::create("axis", math::Axis::Type::X, math::Axis::Type::Y, math::Axis::Type::Z);
const BooleanProperty* UP = BooleanProperty::create("up");
const BooleanProperty* DOWN = BooleanProperty::create("down");
const BooleanProperty* NORTH = BooleanProperty::create("north");
const BooleanProperty* EAST = BooleanProperty::create("east");
const BooleanProperty* SOUTH = BooleanProperty::create("south");
const BooleanProperty* WEST = BooleanProperty::create("west");
const EnumProperty<math::Direction::Type>* FACING = EnumProperty<math::Direction::Type>::create("facing", math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::Up, math::Direction::Type::Down);
const EnumProperty<math::Direction::Type>* FACING_HOPPER = EnumProperty<math::Direction::Type>::create("facing", math::Direction::Type::Down, math::Direction::Type::North, math::Direction::Type::South, math::Direction::Type::West, math::Direction::Type::East);
const EnumProperty<math::Direction::Type>* FACING_HORIZONTAL = EnumProperty<math::Direction::Type>::create("facing", math::Direction::Type::North, math::Direction::Type::East, math::Direction::Type::South, math::Direction::Type::West);
const IntProperty* FLOWER_AMOUNT = IntProperty::create("flower_amount", 1, 4);
const IntProperty* SEGMENT_AMOUNT = IntProperty::create("flower_amount", 1, 4);
const EnumProperty<Orientation>* ORIENTATION = EnumProperty<Orientation>::create("orientation", Orientation::DownEast, Orientation::DownNorth, Orientation::DownSouth, Orientation::DownWest, Orientation::UpEast, Orientation::UpNorth, Orientation::UpSouth, Orientation::UpWest, Orientation::WestUp, Orientation::EastUp, Orientation::NorthUp, Orientation::SouthUp);
const EnumProperty<BlockFace>* BLOCK_FACE = EnumProperty<BlockFace>::create("block_face", BlockFace::Floor, BlockFace::Wall, BlockFace::Ceiling);
const EnumProperty<Attachment>* ATTACHMENT = EnumProperty<Attachment>::create("attachment", Attachment::Floor, Attachment::Ceiling, Attachment::SingleWall, Attachment::DoubleWall);
const EnumProperty<WallConnection>* EAST_WALL_SHAPE = EnumProperty<WallConnection>::create("east", WallConnection::None, WallConnection::Low, WallConnection::Tall);
const EnumProperty<WallConnection>* NORTH_WALL_SHAPE = EnumProperty<WallConnection>::create("north", WallConnection::None, WallConnection::Low, WallConnection::Tall);
const EnumProperty<WallConnection>* SOUTH_WALL_SHAPE = EnumProperty<WallConnection>::create("south", WallConnection::None, WallConnection::Low, WallConnection::Tall);
const EnumProperty<WallConnection>* WEST_WALL_SHAPE = EnumProperty<WallConnection>::create("west", WallConnection::None, WallConnection::Low, WallConnection::Tall);
const EnumProperty<WireConnection>* EAST_WIRE_CONNECTION = EnumProperty<WireConnection>::create("east", WireConnection::Up, WireConnection::Side, WireConnection::None);
const EnumProperty<WireConnection>* NORTH_WIRE_CONNECTION = EnumProperty<WireConnection>::create("north", WireConnection::Up, WireConnection::Side, WireConnection::None);
const EnumProperty<WireConnection>* SOUTH_WIRE_CONNECTION = EnumProperty<WireConnection>::create("south", WireConnection::Up, WireConnection::Side, WireConnection::None);
const EnumProperty<WireConnection>* WEST_WIRE_CONNECTION = EnumProperty<WireConnection>::create("west", WireConnection::Up, WireConnection::Side, WireConnection::None);
const EnumProperty<DoubleBlockHalf>* DOUBLE_BLOCK_HALF = EnumProperty<DoubleBlockHalf>::create("half", DoubleBlockHalf::Upper, DoubleBlockHalf::Lower);
const EnumProperty<BlockHalf>* BLOCK_HALF = EnumProperty<BlockHalf>::create("half", BlockHalf::Top, BlockHalf::Bottom);
const EnumProperty<RailConnection>* RAIL_SHAPE = EnumProperty<RailConnection>::create("shape", RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest, RailConnection::SouthEast, RailConnection::SouthWest, RailConnection::NorthEast, RailConnection::NorthWest);
const EnumProperty<RailConnection>* STRAIGHT_RAIL_SHAPE = EnumProperty<RailConnection>::create("shape", RailConnection::NorthSouth, RailConnection::EastWest, RailConnection::AscendingNorth, RailConnection::AscendingSouth, RailConnection::AscendingEast, RailConnection::AscendingWest);
const IntProperty* AGE_1 = IntProperty::create("age", 0, 1);
const IntProperty* AGE_2 = IntProperty::create("age", 0, 2);
const IntProperty* AGE_3 = IntProperty::create("age", 0, 3);
const IntProperty* AGE_4 = IntProperty::create("age", 0, 4);
const IntProperty* AGE_5 = IntProperty::create("age", 0, 5);
const IntProperty* AGE_7 = IntProperty::create("age", 0, 7);
const IntProperty* AGE_15 = IntProperty::create("age", 0, 15);
const IntProperty* AGE_25 = IntProperty::create("age", 0, 25);
const IntProperty* BITES = IntProperty::create("bites", 0, 6);
const IntProperty* CANDLES = IntProperty::create("candles", 1, 4);
const IntProperty* DELAY = IntProperty::create("delay", 1, 4);
const IntProperty* DISTANCE_1_7 = IntProperty::create("distance", 1, 7);
const IntProperty* EGGS = IntProperty::create("eggs", 1, 4);
const IntProperty* HATCH = IntProperty::create("hatch", 0, 2);
const IntProperty* LAYERS = IntProperty::create("layers", 1, 8);
const IntProperty* LEVEL_3 = IntProperty::create("level", 1, 3);
const IntProperty* LEVEL_8 = IntProperty::create("level", 0, 8);
const IntProperty* LEVEL_1_8 = IntProperty::create("level", 1, 8);
const IntProperty* HONEY_LEVEL = IntProperty::create("honey_level", 0, 5);
const IntProperty* LEVEL_15 = IntProperty::create("level", 0, 15);
const IntProperty* MOISTURE = IntProperty::create("moisture", 0, 7);
const IntProperty* NOTE = IntProperty::create("note", 0, 24);
const IntProperty* PICKLES = IntProperty::create("pickles", 1, 4);
const IntProperty* POWER = IntProperty::create("power", 0, 15);
const IntProperty* STAGE = IntProperty::create("stage", 0, 1);
const IntProperty* DISTANCE_0_7 = IntProperty::create("distance", 0, 7);
const IntProperty* CHARGES = IntProperty::create("charges", 0, 4);
const IntProperty* ROTATION = IntProperty::create("rotation", 0, 15);
const EnumProperty<BedPart>* BED_PART = EnumProperty<BedPart>::create("part", BedPart::Head, BedPart::Foot);
const EnumProperty<ChestType>* CHEST_TYPE = EnumProperty<ChestType>::create("type", ChestType::Single, ChestType::Left, ChestType::Right);
const EnumProperty<ComparatorMode>* COMPARATOR_MODE = EnumProperty<ComparatorMode>::create("mode", ComparatorMode::Compare, ComparatorMode::Subtract);
const EnumProperty<DoorHinge>* DOOR_HINGE = EnumProperty<DoorHinge>::create("hinge", DoorHinge::Left, DoorHinge::Right);
const EnumProperty<NoteBlockInstrument>* INSTRUMENT = EnumProperty<NoteBlockInstrument>::create("instrument", NoteBlockInstrument::Harp, NoteBlockInstrument::BassDrum, NoteBlockInstrument::Snare, NoteBlockInstrument::Hat, NoteBlockInstrument::Bass, NoteBlockInstrument::Flute, NoteBlockInstrument::Bell, NoteBlockInstrument::Guitar, NoteBlockInstrument::Chime, NoteBlockInstrument::Xylophone, NoteBlockInstrument::IronXylophone, NoteBlockInstrument::CowBell, NoteBlockInstrument::Didgeridoo, NoteBlockInstrument::Bit, NoteBlockInstrument::Banjo, NoteBlockInstrument::Pling, NoteBlockInstrument::Zombie, NoteBlockInstrument::Skeleton, NoteBlockInstrument::Creeper, NoteBlockInstrument::Dragon, NoteBlockInstrument::WitherSkeleton, NoteBlockInstrument::Piglin, NoteBlockInstrument::CustomHead);
const EnumProperty<PistonType>* PISTON_TYPE = EnumProperty<PistonType>::create("type", PistonType::Default, PistonType::Sticky);
const EnumProperty<SlabType>* SLAB_TYPE = EnumProperty<SlabType>::create("type", SlabType::Top, SlabType::Bottom, SlabType::Double);
const EnumProperty<StairShape>* STAIR_SHAPE = EnumProperty<StairShape>::create("shape", StairShape::Straight, StairShape::InnerLeft, StairShape::InnerRight, StairShape::OuterLeft, StairShape::OuterRight);
const EnumProperty<StructureBlockMode>* STRUCTURE_BLOCK_MODE = EnumProperty<StructureBlockMode>::create("mode", StructureBlockMode::Save, StructureBlockMode::Load, StructureBlockMode::Corner, StructureBlockMode::Data);
const EnumProperty<BambooLeaves>* BAMBOO_LEAVES = EnumProperty<BambooLeaves>::create("leaves", BambooLeaves::None, BambooLeaves::Small, BambooLeaves::Large);
const EnumProperty<Tilt>* TILT = EnumProperty<Tilt>::create("tilt", Tilt::None, Tilt::Unstable, Tilt::Partial, Tilt::Full);
const EnumProperty<math::Direction::Type>* VERTICAL_DIRECTION = EnumProperty<math::Direction::Type>::create("vertical_direction", math::Direction::Type::Up, math::Direction::Type::Down);
const EnumProperty<Thickness>* THICKNESS = EnumProperty<Thickness>::create("thickness", Thickness::TipMerge, Thickness::Tip, Thickness::Frustum, Thickness::Middle, Thickness::Base);
const EnumProperty<SculkSensorPhase>* SCULK_SENSOR_PHASE = EnumProperty<SculkSensorPhase>::create("phase", SculkSensorPhase::Inactive, SculkSensorPhase::Active, SculkSensorPhase::Cooldown);
const BooleanProperty* SLOT_0_OCCUPIED = BooleanProperty::create("slot_0_occupied");
const BooleanProperty* SLOT_1_OCCUPIED = BooleanProperty::create("slot_1_occupied");
const BooleanProperty* SLOT_2_OCCUPIED = BooleanProperty::create("slot_2_occupied");
const BooleanProperty* SLOT_3_OCCUPIED = BooleanProperty::create("slot_3_occupied");
const BooleanProperty* SLOT_4_OCCUPIED = BooleanProperty::create("slot_4_occupied");
const BooleanProperty* SLOT_5_OCCUPIED = BooleanProperty::create("slot_5_occupied");
const IntProperty* DUSTED = IntProperty::create("dusted", 0, 3);
const BooleanProperty* CRACKED = BooleanProperty::create("cracked");
const BooleanProperty* CRAFTING = BooleanProperty::create("crafting");
const EnumProperty<TrialSpawnerState>* TRIAL_SPAWNER_STATE = EnumProperty<TrialSpawnerState>::create("trial_spawner_state", TrialSpawnerState::Inactive, TrialSpawnerState::WaitingForPlayers, TrialSpawnerState::Active, TrialSpawnerState::WaitingForRewardEjection, TrialSpawnerState::EjectingReward, TrialSpawnerState::Cooldown);
const EnumProperty<VaultState>* VAULT_STATE = EnumProperty<VaultState>::create("vault_state", VaultState::Inactive, VaultState::Active, VaultState::Unlocking, VaultState::Ejecting);
const EnumProperty<CreakingHeartState>* CREAKING_HEART_STATE = EnumProperty<CreakingHeartState>::create("creaking_heart_state", CreakingHeartState::Uprooted, CreakingHeartState::Dormant, CreakingHeartState::Awake);
const BooleanProperty* OMINOUS = BooleanProperty::create("ominous");
const EnumProperty<TestBlockMode>* TEST_BLOCK_MODE = EnumProperty<TestBlockMode>::create("mode", TestBlockMode::Start, TestBlockMode::Log, TestBlockMode::Fail, TestBlockMode::Accept);
const BooleanProperty* MAP = BooleanProperty::create("map");
} // nnamespace stratos::block;