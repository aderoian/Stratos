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

#ifndef STATEPROPERTIES_H
#define STATEPROPERTIES_H
#include "block/Block.h"
#include "math/Direction.h"
#include "StateProperty.h"

namespace stratos::block {

extern const BooleanProperty* ATTACHED;
extern const BooleanProperty* BERRIES;
extern const BooleanProperty* BLOOM;
extern const BooleanProperty* BOTTOM;
extern const BooleanProperty* CAN_SUMMON;
extern const BooleanProperty* CONDITIONAL;
extern const BooleanProperty* DISARMED;
extern const BooleanProperty* DRAG;
extern const BooleanProperty* ENABLED;
extern const BooleanProperty* EXTENDED;
extern const BooleanProperty* EYE;
extern const BooleanProperty* FALLING;
extern const BooleanProperty* HANGING;
extern const BooleanProperty* HAS_BOTTLE_0;
extern const BooleanProperty* HAS_BOTTLE_1;
extern const BooleanProperty* HAS_BOTTLE_2;
extern const BooleanProperty* HAS_RECORD;
extern const BooleanProperty* HAS_BOOK;
extern const BooleanProperty* INVERTED;
extern const BooleanProperty* IN_WALL;
extern const BooleanProperty* LIT;
extern const BooleanProperty* LOCKED;
extern const BooleanProperty* NATURAL;
extern const BooleanProperty* OCCUPIED;
extern const BooleanProperty* OPEN;
extern const BooleanProperty* PERSISTENT;
extern const BooleanProperty* POWERED;
extern const BooleanProperty* SHORT;
extern const BooleanProperty* SHRIEKING;
extern const BooleanProperty* SIGNAL_FIRE;
extern const BooleanProperty* SNOWY;
extern const BooleanProperty* TIP;
extern const BooleanProperty* TRIGGERED;
extern const BooleanProperty* UNSTABLE;
extern const BooleanProperty* WATERLOGGED;
extern const EnumProperty<math::Axis::Type>* HORIZONTAL_AXIS;
extern const EnumProperty<math::Axis>* AXIS;
extern const BooleanProperty* UP;
extern const BooleanProperty* DOWN;
extern const BooleanProperty* NORTH;
extern const BooleanProperty* EAST;
extern const BooleanProperty* SOUTH;
extern const BooleanProperty* WEST;
extern const EnumProperty<math::Direction::Type>* FACING;
extern const EnumProperty<math::Direction::Type>* FACING_HOPPER;
extern const EnumProperty<math::Direction::Type>* FACING_HORIZONTAL;
extern const IntProperty* FLOWER_AMOUNT;
extern const IntProperty* SEGMENT_AMOUNT;
extern const EnumProperty<Orientation>* ORIENTATION;
extern const EnumProperty<BlockFace>* BLOCK_FACE;
extern const EnumProperty<Attachment>* ATTACHMENT;
extern const EnumProperty<WallConnection>* EAST_WALL_SHAPE;
extern const EnumProperty<WallConnection>* NORTH_WALL_SHAPE;
extern const EnumProperty<WallConnection>* SOUTH_WALL_SHAPE;
extern const EnumProperty<WallConnection>* WEST_WALL_SHAPE;
extern const EnumProperty<WireConnection>* EAST_WIRE_CONNECTION;
extern const EnumProperty<WireConnection>* NORTH_WIRE_CONNECTION;
extern const EnumProperty<WireConnection>* SOUTH_WIRE_CONNECTION;
extern const EnumProperty<WireConnection>* WEST_WIRE_CONNECTION;
extern const EnumProperty<DoubleBlockHalf>* DOUBLE_BLOCK_HALF;
extern const EnumProperty<BlockHalf>* BLOCK_HALF;
extern const EnumProperty<RailConnection>* RAIL_SHAPE;
extern const EnumProperty<RailConnection>* STRAIGHT_RAIL_SHAPE;
extern const IntProperty* AGE_1;
extern const IntProperty* AGE_2;
extern const IntProperty* AGE_3;
extern const IntProperty* AGE_4;
extern const IntProperty* AGE_5;
extern const IntProperty* AGE_7;
extern const IntProperty* AGE_15;
extern const IntProperty* AGE_25;
extern const IntProperty* BITES;
extern const IntProperty* CANDLES;
extern const IntProperty* DELAY;
extern const IntProperty* DISTANCE_1_7;
extern const IntProperty* EGGS;
extern const IntProperty* HATCH;
extern const IntProperty* LAYERS;
extern const IntProperty* LEVEL_3;
extern const IntProperty* LEVEL_8;
extern const IntProperty* LEVEL_1_8;
extern const IntProperty* HONEY_LEVEL;
extern const IntProperty* LEVEL_15;
extern const IntProperty* MOISTURE;
extern const IntProperty* NOTE;
extern const IntProperty* PICKLES;
extern const IntProperty* POWER;
extern const IntProperty* STAGE;
extern const IntProperty* DISTANCE_0_7;
extern const IntProperty* CHARGES;
extern const IntProperty* ROTATION;
extern const EnumProperty<BedPart>* BED_PART;
extern const EnumProperty<ChestType>* CHEST_TYPE;
extern const EnumProperty<ComparatorMode>* COMPARATOR_MODE;
extern const EnumProperty<DoorHinge>* DOOR_HINGE;
extern const EnumProperty<NoteBlockInstrument>* INSTRUMENT;
extern const EnumProperty<PistonType>* PISTON_TYPE;
extern const EnumProperty<SlabType>* SLAB_TYPE;
extern const EnumProperty<StairShape>* STAIR_SHAPE;
extern const EnumProperty<StructureBlockMode>* STRUCTURE_BLOCK_MODE;
extern const EnumProperty<BambooLeaves>* BAMBOO_LEAVES;
extern const EnumProperty<Tilt>* TILT;
extern const EnumProperty<math::Direction::Type>* VERTICAL_DIRECTION;
extern const EnumProperty<Thickness>* THICKNESS;
extern const EnumProperty<SculkSensorPhase>* SCULK_SENSOR_PHASE;
extern const BooleanProperty* SLOT_0_OCCUPIED;
extern const BooleanProperty* SLOT_1_OCCUPIED;
extern const BooleanProperty* SLOT_2_OCCUPIED;
extern const BooleanProperty* SLOT_3_OCCUPIED;
extern const BooleanProperty* SLOT_4_OCCUPIED;
extern const BooleanProperty* SLOT_5_OCCUPIED;
extern const IntProperty* DUSTED;
extern const BooleanProperty* CRACKED;
extern const BooleanProperty* CRAFTING;
extern const EnumProperty<TrialSpawnerState>* TRIAL_SPAWNER_STATE;
extern const EnumProperty<VaultState>* VAULT_STATE;
extern const EnumProperty<CreakingHeartState>* CREAKING_HEART_STATE;
extern const BooleanProperty* OMINOUS;
extern const EnumProperty<TestBlockMode>* TEST_BLOCK_MODE;
extern const BooleanProperty* MAP;
} // namespace stratos::block

#endif //STATEPROPERTIES_H
