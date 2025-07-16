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

class StateProperties {
public:
    static const BooleanProperty* ATTACHED;
    static const BooleanProperty* BERRIES;
    static const BooleanProperty* BLOOM;
    static const BooleanProperty* BOTTOM;
    static const BooleanProperty* CAN_SUMMON;
    static const BooleanProperty* CONDITIONAL;
    static const BooleanProperty* DISARMED;
    static const BooleanProperty* DRAG;
    static const BooleanProperty* ENABLED;
    static const BooleanProperty* EXTENDED;
    static const BooleanProperty* EYE;
    static const BooleanProperty* FALLING;
    static const BooleanProperty* HANGING;
    static const BooleanProperty* HAS_BOTTLE_0;
    static const BooleanProperty* HAS_BOTTLE_1;
    static const BooleanProperty* HAS_BOTTLE_2;
    static const BooleanProperty* HAS_RECORD;
    static const BooleanProperty* HAS_BOOK;
    static const BooleanProperty* INVERTED;
    static const BooleanProperty* IN_WALL;
    static const BooleanProperty* LIT;
    static const BooleanProperty* LOCKED;
    static const BooleanProperty* NATURAL;
    static const BooleanProperty* OCCUPIED;
    static const BooleanProperty* OPEN;
    static const BooleanProperty* PERSISTENT;
    static const BooleanProperty* POWERED;
    static const BooleanProperty* SHORT;
    static const BooleanProperty* SHRIEKING;
    static const BooleanProperty* SIGNAL_FIRE;
    static const BooleanProperty* SNOWY;
    static const BooleanProperty* TIP;
    static const BooleanProperty* TRIGGERED;
    static const BooleanProperty* UNSTABLE;
    static const BooleanProperty* WATERLOGGED;
    static const EnumProperty<math::Axis::Type>* HORIZONTAL_AXIS;
    static const EnumProperty<math::Axis::Type>* AXIS;
    static const BooleanProperty* UP;
    static const BooleanProperty* DOWN;
    static const BooleanProperty* NORTH;
    static const BooleanProperty* EAST;
    static const BooleanProperty* SOUTH;
    static const BooleanProperty* WEST;
    static const EnumProperty<math::Direction::Type>* FACING;
    static const EnumProperty<math::Direction::Type>* FACING_HOPPER;
    static const EnumProperty<math::Direction::Type>* FACING_HORIZONTAL;
    static const IntProperty* FLOWER_AMOUNT;
    static const IntProperty* SEGMENT_AMOUNT;
    static const EnumProperty<Orientation>* ORIENTATION;
    static const EnumProperty<BlockFace>* BLOCK_FACE;
    static const EnumProperty<Attachment>* ATTACHMENT;
    static const EnumProperty<WallConnection>* EAST_WALL_SHAPE;
    static const EnumProperty<WallConnection>* NORTH_WALL_SHAPE;
    static const EnumProperty<WallConnection>* SOUTH_WALL_SHAPE;
    static const EnumProperty<WallConnection>* WEST_WALL_SHAPE;
    static const EnumProperty<WireConnection>* EAST_WIRE_CONNECTION;
    static const EnumProperty<WireConnection>* NORTH_WIRE_CONNECTION;
    static const EnumProperty<WireConnection>* SOUTH_WIRE_CONNECTION;
    static const EnumProperty<WireConnection>* WEST_WIRE_CONNECTION;
    static const EnumProperty<DoubleBlockHalf>* DOUBLE_BLOCK_HALF;
    static const EnumProperty<BlockHalf>* BLOCK_HALF;
    static const EnumProperty<RailConnection>* RAIL_SHAPE;
    static const EnumProperty<RailConnection>* STRAIGHT_RAIL_SHAPE;
    static const IntProperty* AGE_1;
    static const IntProperty* AGE_2;
    static const IntProperty* AGE_3;
    static const IntProperty* AGE_4;
    static const IntProperty* AGE_5;
    static const IntProperty* AGE_7;
    static const IntProperty* AGE_15;
    static const IntProperty* AGE_25;
    static const IntProperty* BITES;
    static const IntProperty* CANDLES;
    static const IntProperty* DELAY;
    static const IntProperty* DISTANCE_1_7;
    static const IntProperty* EGGS;
    static const IntProperty* HATCH;
    static const IntProperty* LAYERS;
    static const IntProperty* LEVEL_3;
    static const IntProperty* LEVEL_8;
    static const IntProperty* LEVEL_1_8;
    static const IntProperty* HONEY_LEVEL;
    static const IntProperty* LEVEL_15;
    static const IntProperty* MOISTURE;
    static const IntProperty* NOTE;
    static const IntProperty* PICKLES;
    static const IntProperty* POWER;
    static const IntProperty* STAGE;
    static const IntProperty* DISTANCE_0_7;
    static const IntProperty* CHARGES;
    static const IntProperty* ROTATION;
    static const EnumProperty<BedPart>* BED_PART;
    static const EnumProperty<ChestType>* CHEST_TYPE;
    static const EnumProperty<ComparatorMode>* COMPARATOR_MODE;
    static const EnumProperty<DoorHinge>* DOOR_HINGE;
    static const EnumProperty<NoteBlockInstrument>* INSTRUMENT;
    static const EnumProperty<PistonType>* PISTON_TYPE;
    static const EnumProperty<SlabType>* SLAB_TYPE;
    static const EnumProperty<StairShape>* STAIR_SHAPE;
    static const EnumProperty<StructureBlockMode>* STRUCTURE_BLOCK_MODE;
    static const EnumProperty<BambooLeaves>* BAMBOO_LEAVES;
    static const EnumProperty<Tilt>* TILT;
    static const EnumProperty<math::Direction::Type>* VERTICAL_DIRECTION;
    static const EnumProperty<Thickness>* THICKNESS;
    static const EnumProperty<SculkSensorPhase>* SCULK_SENSOR_PHASE;
    static const BooleanProperty* SLOT_0_OCCUPIED;
    static const BooleanProperty* SLOT_1_OCCUPIED;
    static const BooleanProperty* SLOT_2_OCCUPIED;
    static const BooleanProperty* SLOT_3_OCCUPIED;
    static const BooleanProperty* SLOT_4_OCCUPIED;
    static const BooleanProperty* SLOT_5_OCCUPIED;
    static const IntProperty* DUSTED;
    static const BooleanProperty* CRACKED;
    static const BooleanProperty* CRAFTING;
    static const EnumProperty<TrialSpawnerState>* TRIAL_SPAWNER_STATE;
    static const EnumProperty<VaultState>* VAULT_STATE;
    static const EnumProperty<CreakingHeartState>* CREAKING_HEART_STATE;
    static const BooleanProperty* OMINOUS;
    static const EnumProperty<TestBlockMode>* TEST_BLOCK_MODE;
    static const BooleanProperty* MAP;
};
} // namespace stratos::block

#endif //STATEPROPERTIES_H
