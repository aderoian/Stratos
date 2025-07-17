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

#include "Blocks.h"

#include "Block.h"
#include "registry/Registries.h"
#include "state/StateProperties.h"
#include "utils/Identifier.h"

#define REGISTER_BLOCK(codeName, name)     const Block* Blocks::codeName() {         static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block());         return block;     }
#define REGISTER_BLOCK_BLOCKSTATES(codeName, name, stateBuilder...)     const Block* Blocks::codeName() {         static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block(BlockStateManager::Builder().add(stateBuilder)));         return block;     }

namespace stratos::block {

Block* registerBlock(const utils::Identifier& id, Block* block) {
    registry::Registries::BLOCKS()->registerEntry({{"minecraft", "block"}, id}, block);
    return block;
}

// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

    REGISTER_BLOCK(AIR, "air")
    REGISTER_BLOCK(STONE, "stone")
    REGISTER_BLOCK(GRANITE, "granite")
    REGISTER_BLOCK(POLISHED_GRANITE, "polished_granite")
    REGISTER_BLOCK(DIORITE, "diorite")
    REGISTER_BLOCK(POLISHED_DIORITE, "polished_diorite")
    REGISTER_BLOCK(ANDESITE, "andesite")
    REGISTER_BLOCK(POLISHED_ANDESITE, "polished_andesite")
    REGISTER_BLOCK_BLOCKSTATES(GRASS_BLOCK, "grass_block", StateProperties::SNOWY())
    REGISTER_BLOCK(DIRT, "dirt")
    REGISTER_BLOCK(COARSE_DIRT, "coarse_dirt")
    REGISTER_BLOCK_BLOCKSTATES(PODZOL, "podzol", StateProperties::SNOWY())
    REGISTER_BLOCK(COBBLESTONE, "cobblestone")
    REGISTER_BLOCK(OAK_PLANKS, "oak_planks")
    REGISTER_BLOCK(SPRUCE_PLANKS, "spruce_planks")
    REGISTER_BLOCK(BIRCH_PLANKS, "birch_planks")
    REGISTER_BLOCK(JUNGLE_PLANKS, "jungle_planks")
    REGISTER_BLOCK(ACACIA_PLANKS, "acacia_planks")
    REGISTER_BLOCK(CHERRY_PLANKS, "cherry_planks")
    REGISTER_BLOCK(DARK_OAK_PLANKS, "dark_oak_planks")
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_WOOD, "pale_oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK(PALE_OAK_PLANKS, "pale_oak_planks")
    REGISTER_BLOCK(MANGROVE_PLANKS, "mangrove_planks")
    REGISTER_BLOCK(BAMBOO_PLANKS, "bamboo_planks")
    REGISTER_BLOCK(BAMBOO_MOSAIC, "bamboo_mosaic")
    REGISTER_BLOCK_BLOCKSTATES(OAK_SAPLING, "oak_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_SAPLING, "spruce_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_SAPLING, "birch_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_SAPLING, "jungle_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_SAPLING, "acacia_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_SAPLING, "cherry_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_SAPLING, "dark_oak_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_SAPLING, "pale_oak_sapling", StateProperties::STAGE())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_PROPAGULE, "mangrove_propagule", StateProperties::AGE_4(), StateProperties::HANGING(), StateProperties::STAGE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(BEDROCK, "bedrock")
    REGISTER_BLOCK_BLOCKSTATES(WATER, "water", StateProperties::LEVEL_15())
    REGISTER_BLOCK_BLOCKSTATES(LAVA, "lava", StateProperties::LEVEL_15())
    REGISTER_BLOCK(SAND, "sand")
    REGISTER_BLOCK_BLOCKSTATES(SUSPICIOUS_SAND, "suspicious_sand", StateProperties::DUSTED())
    REGISTER_BLOCK(RED_SAND, "red_sand")
    REGISTER_BLOCK(GRAVEL, "gravel")
    REGISTER_BLOCK_BLOCKSTATES(SUSPICIOUS_GRAVEL, "suspicious_gravel", StateProperties::DUSTED())
    REGISTER_BLOCK(GOLD_ORE, "gold_ore")
    REGISTER_BLOCK(DEEPSLATE_GOLD_ORE, "deepslate_gold_ore")
    REGISTER_BLOCK(IRON_ORE, "iron_ore")
    REGISTER_BLOCK(DEEPSLATE_IRON_ORE, "deepslate_iron_ore")
    REGISTER_BLOCK(COAL_ORE, "coal_ore")
    REGISTER_BLOCK(DEEPSLATE_COAL_ORE, "deepslate_coal_ore")
    REGISTER_BLOCK(NETHER_GOLD_ORE, "nether_gold_ore")
    REGISTER_BLOCK_BLOCKSTATES(OAK_LOG, "oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_LOG, "spruce_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_LOG, "birch_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_LOG, "jungle_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_LOG, "acacia_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_LOG, "cherry_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_LOG, "dark_oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_LOG, "pale_oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_LOG, "mangrove_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_ROOTS, "mangrove_roots", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MUDDY_MANGROVE_ROOTS, "muddy_mangrove_roots", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_BLOCK, "bamboo_block", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_SPRUCE_LOG, "stripped_spruce_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_BIRCH_LOG, "stripped_birch_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_JUNGLE_LOG, "stripped_jungle_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_ACACIA_LOG, "stripped_acacia_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_CHERRY_LOG, "stripped_cherry_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_DARK_OAK_LOG, "stripped_dark_oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_PALE_OAK_LOG, "stripped_pale_oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_OAK_LOG, "stripped_oak_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_MANGROVE_LOG, "stripped_mangrove_log", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_BAMBOO_BLOCK, "stripped_bamboo_block", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(OAK_WOOD, "oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_WOOD, "spruce_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_WOOD, "birch_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_WOOD, "jungle_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_WOOD, "acacia_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_WOOD, "cherry_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_WOOD, "dark_oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_WOOD, "mangrove_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_OAK_WOOD, "stripped_oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_SPRUCE_WOOD, "stripped_spruce_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_BIRCH_WOOD, "stripped_birch_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_JUNGLE_WOOD, "stripped_jungle_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_ACACIA_WOOD, "stripped_acacia_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_CHERRY_WOOD, "stripped_cherry_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_DARK_OAK_WOOD, "stripped_dark_oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_PALE_OAK_WOOD, "stripped_pale_oak_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_MANGROVE_WOOD, "stripped_mangrove_wood", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(OAK_LEAVES, "oak_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_LEAVES, "spruce_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_LEAVES, "birch_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_LEAVES, "jungle_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_LEAVES, "acacia_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_LEAVES, "cherry_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_LEAVES, "dark_oak_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_LEAVES, "pale_oak_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_LEAVES, "mangrove_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(AZALEA_LEAVES, "azalea_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(FLOWERING_AZALEA_LEAVES, "flowering_azalea_leaves", StateProperties::DISTANCE_1_7(), StateProperties::PERSISTENT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(SPONGE, "sponge")
    REGISTER_BLOCK(WET_SPONGE, "wet_sponge")
    REGISTER_BLOCK(GLASS, "glass")
    REGISTER_BLOCK(LAPIS_ORE, "lapis_ore")
    REGISTER_BLOCK(DEEPSLATE_LAPIS_ORE, "deepslate_lapis_ore")
    REGISTER_BLOCK(LAPIS_BLOCK, "lapis_block")
    REGISTER_BLOCK_BLOCKSTATES(DISPENSER, "dispenser", StateProperties::FACING_ANY(), StateProperties::TRIGGERED())
    REGISTER_BLOCK(SANDSTONE, "sandstone")
    REGISTER_BLOCK(CHISELED_SANDSTONE, "chiseled_sandstone")
    REGISTER_BLOCK(CUT_SANDSTONE, "cut_sandstone")
    REGISTER_BLOCK_BLOCKSTATES(NOTE_BLOCK, "note_block", StateProperties::INSTRUMENT(), StateProperties::NOTE(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_BED, "white_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_BED, "orange_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_BED, "magenta_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_BED, "light_blue_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_BED, "yellow_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(LIME_BED, "lime_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(PINK_BED, "pink_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_BED, "gray_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_BED, "light_gray_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_BED, "cyan_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_BED, "purple_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_BED, "blue_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_BED, "brown_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_BED, "green_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(RED_BED, "red_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_BED, "black_bed", StateProperties::FACING_HORIZONTAL(), StateProperties::OCCUPIED(), StateProperties::BED_PART())
    REGISTER_BLOCK_BLOCKSTATES(POWERED_RAIL, "powered_rail", StateProperties::POWERED(), StateProperties::RAIL_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DETECTOR_RAIL, "detector_rail", StateProperties::POWERED(), StateProperties::RAIL_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STICKY_PISTON, "sticky_piston", StateProperties::EXTENDED(), StateProperties::FACING_ANY())
    REGISTER_BLOCK(COBWEB, "cobweb")
    REGISTER_BLOCK(SHORT_GRASS, "short_grass")
    REGISTER_BLOCK(FERN, "fern")
    REGISTER_BLOCK(DEAD_BUSH, "dead_bush")
    REGISTER_BLOCK(BUSH, "bush")
    REGISTER_BLOCK(SHORT_DRY_GRASS, "short_dry_grass")
    REGISTER_BLOCK(TALL_DRY_GRASS, "tall_dry_grass")
    REGISTER_BLOCK(SEAGRASS, "seagrass")
    REGISTER_BLOCK_BLOCKSTATES(TALL_SEAGRASS, "tall_seagrass", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(PISTON, "piston", StateProperties::EXTENDED(), StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(PISTON_HEAD, "piston_head", StateProperties::FACING_ANY(), StateProperties::SHORT(), StateProperties::PISTON_TYPE())
    REGISTER_BLOCK(WHITE_WOOL, "white_wool")
    REGISTER_BLOCK(ORANGE_WOOL, "orange_wool")
    REGISTER_BLOCK(MAGENTA_WOOL, "magenta_wool")
    REGISTER_BLOCK(LIGHT_BLUE_WOOL, "light_blue_wool")
    REGISTER_BLOCK(YELLOW_WOOL, "yellow_wool")
    REGISTER_BLOCK(LIME_WOOL, "lime_wool")
    REGISTER_BLOCK(PINK_WOOL, "pink_wool")
    REGISTER_BLOCK(GRAY_WOOL, "gray_wool")
    REGISTER_BLOCK(LIGHT_GRAY_WOOL, "light_gray_wool")
    REGISTER_BLOCK(CYAN_WOOL, "cyan_wool")
    REGISTER_BLOCK(PURPLE_WOOL, "purple_wool")
    REGISTER_BLOCK(BLUE_WOOL, "blue_wool")
    REGISTER_BLOCK(BROWN_WOOL, "brown_wool")
    REGISTER_BLOCK(GREEN_WOOL, "green_wool")
    REGISTER_BLOCK(RED_WOOL, "red_wool")
    REGISTER_BLOCK(BLACK_WOOL, "black_wool")
    REGISTER_BLOCK_BLOCKSTATES(MOVING_PISTON, "moving_piston", StateProperties::FACING_ANY(), StateProperties::PISTON_TYPE())
    REGISTER_BLOCK(DANDELION, "dandelion")
    REGISTER_BLOCK(TORCHFLOWER, "torchflower")
    REGISTER_BLOCK(POPPY, "poppy")
    REGISTER_BLOCK(BLUE_ORCHID, "blue_orchid")
    REGISTER_BLOCK(ALLIUM, "allium")
    REGISTER_BLOCK(AZURE_BLUET, "azure_bluet")
    REGISTER_BLOCK(RED_TULIP, "red_tulip")
    REGISTER_BLOCK(ORANGE_TULIP, "orange_tulip")
    REGISTER_BLOCK(WHITE_TULIP, "white_tulip")
    REGISTER_BLOCK(PINK_TULIP, "pink_tulip")
    REGISTER_BLOCK(OXEYE_DAISY, "oxeye_daisy")
    REGISTER_BLOCK(CORNFLOWER, "cornflower")
    REGISTER_BLOCK(WITHER_ROSE, "wither_rose")
    REGISTER_BLOCK(LILY_OF_THE_VALLEY, "lily_of_the_valley")
    REGISTER_BLOCK(BROWN_MUSHROOM, "brown_mushroom")
    REGISTER_BLOCK(RED_MUSHROOM, "red_mushroom")
    REGISTER_BLOCK(GOLD_BLOCK, "gold_block")
    REGISTER_BLOCK(IRON_BLOCK, "iron_block")
    REGISTER_BLOCK(BRICKS, "bricks")
    REGISTER_BLOCK_BLOCKSTATES(TNT, "tnt", StateProperties::UNSTABLE())
    REGISTER_BLOCK(BOOKSHELF, "bookshelf")
    REGISTER_BLOCK_BLOCKSTATES(CHISELED_BOOKSHELF, "chiseled_bookshelf", StateProperties::FACING_HORIZONTAL(), StateProperties::SLOT_0_OCCUPIED(), StateProperties::SLOT_1_OCCUPIED(), StateProperties::SLOT_2_OCCUPIED(), StateProperties::SLOT_3_OCCUPIED(), StateProperties::SLOT_4_OCCUPIED(), StateProperties::SLOT_5_OCCUPIED())
    REGISTER_BLOCK(MOSSY_COBBLESTONE, "mossy_cobblestone")
    REGISTER_BLOCK(OBSIDIAN, "obsidian")
    REGISTER_BLOCK(TORCH, "torch")
    REGISTER_BLOCK_BLOCKSTATES(WALL_TORCH, "wall_torch", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(FIRE, "fire", StateProperties::AGE_15(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK(SOUL_FIRE, "soul_fire")
    REGISTER_BLOCK(SPAWNER, "spawner")
    REGISTER_BLOCK_BLOCKSTATES(CREAKING_HEART, "creaking_heart", StateProperties::AXIS(), StateProperties::CREAKING_HEART_STATE(), StateProperties::NATURAL())
    REGISTER_BLOCK_BLOCKSTATES(OAK_STAIRS, "oak_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHEST, "chest", StateProperties::FACING_HORIZONTAL(), StateProperties::CHEST_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(REDSTONE_WIRE, "redstone_wire", StateProperties::EAST_WIRE_CONNECTION(), StateProperties::NORTH_WIRE_CONNECTION(), StateProperties::POWER(), StateProperties::SOUTH_WIRE_CONNECTION(), StateProperties::WEST_WIRE_CONNECTION())
    REGISTER_BLOCK(DIAMOND_ORE, "diamond_ore")
    REGISTER_BLOCK(DEEPSLATE_DIAMOND_ORE, "deepslate_diamond_ore")
    REGISTER_BLOCK(DIAMOND_BLOCK, "diamond_block")
    REGISTER_BLOCK(CRAFTING_TABLE, "crafting_table")
    REGISTER_BLOCK_BLOCKSTATES(WHEAT, "wheat", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(FARMLAND, "farmland", StateProperties::MOISTURE())
    REGISTER_BLOCK_BLOCKSTATES(FURNACE, "furnace", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(OAK_SIGN, "oak_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_SIGN, "spruce_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_SIGN, "birch_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_SIGN, "acacia_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_SIGN, "cherry_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_SIGN, "jungle_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_SIGN, "dark_oak_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_SIGN, "pale_oak_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_SIGN, "mangrove_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_SIGN, "bamboo_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_DOOR, "oak_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(LADDER, "ladder", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RAIL, "rail", StateProperties::RAIL_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COBBLESTONE_STAIRS, "cobblestone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_WALL_SIGN, "oak_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_WALL_SIGN, "spruce_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_WALL_SIGN, "birch_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_WALL_SIGN, "acacia_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_WALL_SIGN, "cherry_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_WALL_SIGN, "jungle_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_WALL_SIGN, "dark_oak_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_WALL_SIGN, "pale_oak_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_WALL_SIGN, "mangrove_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_WALL_SIGN, "bamboo_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_HANGING_SIGN, "oak_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_HANGING_SIGN, "spruce_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_HANGING_SIGN, "birch_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_HANGING_SIGN, "acacia_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_HANGING_SIGN, "cherry_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_HANGING_SIGN, "jungle_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_HANGING_SIGN, "dark_oak_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_HANGING_SIGN, "pale_oak_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_HANGING_SIGN, "crimson_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_HANGING_SIGN, "warped_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_HANGING_SIGN, "mangrove_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_HANGING_SIGN, "bamboo_hanging_sign", StateProperties::ATTACHED(), StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_WALL_HANGING_SIGN, "oak_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_WALL_HANGING_SIGN, "spruce_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_WALL_HANGING_SIGN, "birch_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_WALL_HANGING_SIGN, "acacia_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_WALL_HANGING_SIGN, "cherry_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_WALL_HANGING_SIGN, "jungle_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_WALL_HANGING_SIGN, "dark_oak_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_WALL_HANGING_SIGN, "pale_oak_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_WALL_HANGING_SIGN, "mangrove_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_WALL_HANGING_SIGN, "crimson_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_WALL_HANGING_SIGN, "warped_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_WALL_HANGING_SIGN, "bamboo_wall_hanging_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LEVER, "lever", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(STONE_PRESSURE_PLATE, "stone_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(IRON_DOOR, "iron_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_PRESSURE_PLATE, "oak_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_PRESSURE_PLATE, "spruce_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_PRESSURE_PLATE, "birch_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_PRESSURE_PLATE, "jungle_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_PRESSURE_PLATE, "acacia_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_PRESSURE_PLATE, "cherry_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_PRESSURE_PLATE, "dark_oak_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_PRESSURE_PLATE, "pale_oak_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_PRESSURE_PLATE, "mangrove_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_PRESSURE_PLATE, "bamboo_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(REDSTONE_ORE, "redstone_ore", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_REDSTONE_ORE, "deepslate_redstone_ore", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(REDSTONE_TORCH, "redstone_torch", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(REDSTONE_WALL_TORCH, "redstone_wall_torch", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(STONE_BUTTON, "stone_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SNOW, "snow", StateProperties::LAYERS())
    REGISTER_BLOCK(ICE, "ice")
    REGISTER_BLOCK(SNOW_BLOCK, "snow_block")
    REGISTER_BLOCK_BLOCKSTATES(CACTUS, "cactus", StateProperties::AGE_15())
    REGISTER_BLOCK(CACTUS_FLOWER, "cactus_flower")
    REGISTER_BLOCK(CLAY, "clay")
    REGISTER_BLOCK_BLOCKSTATES(SUGAR_CANE, "sugar_cane", StateProperties::AGE_15())
    REGISTER_BLOCK_BLOCKSTATES(JUKEBOX, "jukebox", StateProperties::HAS_RECORD())
    REGISTER_BLOCK_BLOCKSTATES(OAK_FENCE, "oak_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK(NETHERRACK, "netherrack")
    REGISTER_BLOCK(SOUL_SAND, "soul_sand")
    REGISTER_BLOCK(SOUL_SOIL, "soul_soil")
    REGISTER_BLOCK_BLOCKSTATES(BASALT, "basalt", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BASALT, "polished_basalt", StateProperties::AXIS())
    REGISTER_BLOCK(SOUL_TORCH, "soul_torch")
    REGISTER_BLOCK_BLOCKSTATES(SOUL_WALL_TORCH, "soul_wall_torch", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK(GLOWSTONE, "glowstone")
    REGISTER_BLOCK_BLOCKSTATES(NETHER_PORTAL, "nether_portal", StateProperties::HORIZONTAL_AXIS())
    REGISTER_BLOCK_BLOCKSTATES(CARVED_PUMPKIN, "carved_pumpkin", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(JACK_O_LANTERN, "jack_o_lantern", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(CAKE, "cake", StateProperties::BITES())
    REGISTER_BLOCK_BLOCKSTATES(REPEATER, "repeater", StateProperties::DELAY(), StateProperties::FACING_HORIZONTAL(), StateProperties::LOCKED(), StateProperties::POWERED())
    REGISTER_BLOCK(WHITE_STAINED_GLASS, "white_stained_glass")
    REGISTER_BLOCK(ORANGE_STAINED_GLASS, "orange_stained_glass")
    REGISTER_BLOCK(MAGENTA_STAINED_GLASS, "magenta_stained_glass")
    REGISTER_BLOCK(LIGHT_BLUE_STAINED_GLASS, "light_blue_stained_glass")
    REGISTER_BLOCK(YELLOW_STAINED_GLASS, "yellow_stained_glass")
    REGISTER_BLOCK(LIME_STAINED_GLASS, "lime_stained_glass")
    REGISTER_BLOCK(PINK_STAINED_GLASS, "pink_stained_glass")
    REGISTER_BLOCK(GRAY_STAINED_GLASS, "gray_stained_glass")
    REGISTER_BLOCK(LIGHT_GRAY_STAINED_GLASS, "light_gray_stained_glass")
    REGISTER_BLOCK(CYAN_STAINED_GLASS, "cyan_stained_glass")
    REGISTER_BLOCK(PURPLE_STAINED_GLASS, "purple_stained_glass")
    REGISTER_BLOCK(BLUE_STAINED_GLASS, "blue_stained_glass")
    REGISTER_BLOCK(BROWN_STAINED_GLASS, "brown_stained_glass")
    REGISTER_BLOCK(GREEN_STAINED_GLASS, "green_stained_glass")
    REGISTER_BLOCK(RED_STAINED_GLASS, "red_stained_glass")
    REGISTER_BLOCK(BLACK_STAINED_GLASS, "black_stained_glass")
    REGISTER_BLOCK_BLOCKSTATES(OAK_TRAPDOOR, "oak_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_TRAPDOOR, "spruce_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_TRAPDOOR, "birch_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_TRAPDOOR, "jungle_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_TRAPDOOR, "acacia_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_TRAPDOOR, "cherry_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_TRAPDOOR, "dark_oak_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_TRAPDOOR, "pale_oak_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_TRAPDOOR, "mangrove_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_TRAPDOOR, "bamboo_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(STONE_BRICKS, "stone_bricks")
    REGISTER_BLOCK(MOSSY_STONE_BRICKS, "mossy_stone_bricks")
    REGISTER_BLOCK(CRACKED_STONE_BRICKS, "cracked_stone_bricks")
    REGISTER_BLOCK(CHISELED_STONE_BRICKS, "chiseled_stone_bricks")
    REGISTER_BLOCK(PACKED_MUD, "packed_mud")
    REGISTER_BLOCK(MUD_BRICKS, "mud_bricks")
    REGISTER_BLOCK(INFESTED_STONE, "infested_stone")
    REGISTER_BLOCK(INFESTED_COBBLESTONE, "infested_cobblestone")
    REGISTER_BLOCK(INFESTED_STONE_BRICKS, "infested_stone_bricks")
    REGISTER_BLOCK(INFESTED_MOSSY_STONE_BRICKS, "infested_mossy_stone_bricks")
    REGISTER_BLOCK(INFESTED_CRACKED_STONE_BRICKS, "infested_cracked_stone_bricks")
    REGISTER_BLOCK(INFESTED_CHISELED_STONE_BRICKS, "infested_chiseled_stone_bricks")
    REGISTER_BLOCK_BLOCKSTATES(BROWN_MUSHROOM_BLOCK, "brown_mushroom_block", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(RED_MUSHROOM_BLOCK, "red_mushroom_block", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(MUSHROOM_STEM, "mushroom_stem", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(IRON_BARS, "iron_bars", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(CHAIN, "chain", StateProperties::AXIS(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(GLASS_PANE, "glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK(PUMPKIN, "pumpkin")
    REGISTER_BLOCK(MELON, "melon")
    REGISTER_BLOCK_BLOCKSTATES(ATTACHED_PUMPKIN_STEM, "attached_pumpkin_stem", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(ATTACHED_MELON_STEM, "attached_melon_stem", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(PUMPKIN_STEM, "pumpkin_stem", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(MELON_STEM, "melon_stem", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(VINE, "vine", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(GLOW_LICHEN, "glow_lichen", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(RESIN_CLUMP, "resin_clump", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(OAK_FENCE_GATE, "oak_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BRICK_STAIRS, "brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STONE_BRICK_STAIRS, "stone_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MUD_BRICK_STAIRS, "mud_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MYCELIUM, "mycelium", StateProperties::SNOWY())
    REGISTER_BLOCK(LILY_PAD, "lily_pad")
    REGISTER_BLOCK(RESIN_BLOCK, "resin_block")
    REGISTER_BLOCK(RESIN_BRICKS, "resin_bricks")
    REGISTER_BLOCK_BLOCKSTATES(RESIN_BRICK_STAIRS, "resin_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RESIN_BRICK_SLAB, "resin_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RESIN_BRICK_WALL, "resin_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(CHISELED_RESIN_BRICKS, "chiseled_resin_bricks")
    REGISTER_BLOCK(NETHER_BRICKS, "nether_bricks")
    REGISTER_BLOCK_BLOCKSTATES(NETHER_BRICK_FENCE, "nether_brick_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(NETHER_BRICK_STAIRS, "nether_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(NETHER_WART, "nether_wart", StateProperties::AGE_3())
    REGISTER_BLOCK(ENCHANTING_TABLE, "enchanting_table")
    REGISTER_BLOCK_BLOCKSTATES(BREWING_STAND, "brewing_stand", StateProperties::HAS_BOTTLE_0(), StateProperties::HAS_BOTTLE_1(), StateProperties::HAS_BOTTLE_2())
    REGISTER_BLOCK(CAULDRON, "cauldron")
    REGISTER_BLOCK_BLOCKSTATES(WATER_CAULDRON, "water_cauldron", StateProperties::LEVEL_3())
    REGISTER_BLOCK(LAVA_CAULDRON, "lava_cauldron")
    REGISTER_BLOCK_BLOCKSTATES(POWDER_SNOW_CAULDRON, "powder_snow_cauldron", StateProperties::LEVEL_3())
    REGISTER_BLOCK(END_PORTAL, "end_portal")
    REGISTER_BLOCK_BLOCKSTATES(END_PORTAL_FRAME, "end_portal_frame", StateProperties::EYE(), StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK(END_STONE, "end_stone")
    REGISTER_BLOCK(DRAGON_EGG, "dragon_egg")
    REGISTER_BLOCK_BLOCKSTATES(REDSTONE_LAMP, "redstone_lamp", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(COCOA, "cocoa", StateProperties::AGE_2(), StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(SANDSTONE_STAIRS, "sandstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(EMERALD_ORE, "emerald_ore")
    REGISTER_BLOCK(DEEPSLATE_EMERALD_ORE, "deepslate_emerald_ore")
    REGISTER_BLOCK_BLOCKSTATES(ENDER_CHEST, "ender_chest", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TRIPWIRE_HOOK, "tripwire_hook", StateProperties::ATTACHED(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(TRIPWIRE, "tripwire", StateProperties::ATTACHED(), StateProperties::DISARMED(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::POWERED(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK(EMERALD_BLOCK, "emerald_block")
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_STAIRS, "spruce_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_STAIRS, "birch_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_STAIRS, "jungle_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COMMAND_BLOCK, "command_block", StateProperties::CONDITIONAL(), StateProperties::FACING_ANY())
    REGISTER_BLOCK(BEACON, "beacon")
    REGISTER_BLOCK_BLOCKSTATES(COBBLESTONE_WALL, "cobblestone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_COBBLESTONE_WALL, "mossy_cobblestone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(FLOWER_POT, "flower_pot")
    REGISTER_BLOCK(POTTED_TORCHFLOWER, "potted_torchflower")
    REGISTER_BLOCK(POTTED_OAK_SAPLING, "potted_oak_sapling")
    REGISTER_BLOCK(POTTED_SPRUCE_SAPLING, "potted_spruce_sapling")
    REGISTER_BLOCK(POTTED_BIRCH_SAPLING, "potted_birch_sapling")
    REGISTER_BLOCK(POTTED_JUNGLE_SAPLING, "potted_jungle_sapling")
    REGISTER_BLOCK(POTTED_ACACIA_SAPLING, "potted_acacia_sapling")
    REGISTER_BLOCK(POTTED_CHERRY_SAPLING, "potted_cherry_sapling")
    REGISTER_BLOCK(POTTED_DARK_OAK_SAPLING, "potted_dark_oak_sapling")
    REGISTER_BLOCK(POTTED_PALE_OAK_SAPLING, "potted_pale_oak_sapling")
    REGISTER_BLOCK(POTTED_MANGROVE_PROPAGULE, "potted_mangrove_propagule")
    REGISTER_BLOCK(POTTED_FERN, "potted_fern")
    REGISTER_BLOCK(POTTED_DANDELION, "potted_dandelion")
    REGISTER_BLOCK(POTTED_POPPY, "potted_poppy")
    REGISTER_BLOCK(POTTED_BLUE_ORCHID, "potted_blue_orchid")
    REGISTER_BLOCK(POTTED_ALLIUM, "potted_allium")
    REGISTER_BLOCK(POTTED_AZURE_BLUET, "potted_azure_bluet")
    REGISTER_BLOCK(POTTED_RED_TULIP, "potted_red_tulip")
    REGISTER_BLOCK(POTTED_ORANGE_TULIP, "potted_orange_tulip")
    REGISTER_BLOCK(POTTED_WHITE_TULIP, "potted_white_tulip")
    REGISTER_BLOCK(POTTED_PINK_TULIP, "potted_pink_tulip")
    REGISTER_BLOCK(POTTED_OXEYE_DAISY, "potted_oxeye_daisy")
    REGISTER_BLOCK(POTTED_CORNFLOWER, "potted_cornflower")
    REGISTER_BLOCK(POTTED_LILY_OF_THE_VALLEY, "potted_lily_of_the_valley")
    REGISTER_BLOCK(POTTED_WITHER_ROSE, "potted_wither_rose")
    REGISTER_BLOCK(POTTED_RED_MUSHROOM, "potted_red_mushroom")
    REGISTER_BLOCK(POTTED_BROWN_MUSHROOM, "potted_brown_mushroom")
    REGISTER_BLOCK(POTTED_DEAD_BUSH, "potted_dead_bush")
    REGISTER_BLOCK(POTTED_CACTUS, "potted_cactus")
    REGISTER_BLOCK_BLOCKSTATES(CARROTS, "carrots", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(POTATOES, "potatoes", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(OAK_BUTTON, "oak_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_BUTTON, "spruce_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_BUTTON, "birch_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_BUTTON, "jungle_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_BUTTON, "acacia_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_BUTTON, "cherry_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_BUTTON, "dark_oak_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_BUTTON, "pale_oak_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_BUTTON, "mangrove_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_BUTTON, "bamboo_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SKELETON_SKULL, "skeleton_skull", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(SKELETON_WALL_SKULL, "skeleton_wall_skull", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WITHER_SKELETON_SKULL, "wither_skeleton_skull", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(WITHER_SKELETON_WALL_SKULL, "wither_skeleton_wall_skull", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ZOMBIE_HEAD, "zombie_head", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(ZOMBIE_WALL_HEAD, "zombie_wall_head", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PLAYER_HEAD, "player_head", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(PLAYER_WALL_HEAD, "player_wall_head", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CREEPER_HEAD, "creeper_head", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(CREEPER_WALL_HEAD, "creeper_wall_head", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DRAGON_HEAD, "dragon_head", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(DRAGON_WALL_HEAD, "dragon_wall_head", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PIGLIN_HEAD, "piglin_head", StateProperties::POWERED(), StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(PIGLIN_WALL_HEAD, "piglin_wall_head", StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ANVIL, "anvil", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(CHIPPED_ANVIL, "chipped_anvil", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(DAMAGED_ANVIL, "damaged_anvil", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(TRAPPED_CHEST, "trapped_chest", StateProperties::FACING_HORIZONTAL(), StateProperties::CHEST_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_WEIGHTED_PRESSURE_PLATE, "light_weighted_pressure_plate", StateProperties::POWER())
    REGISTER_BLOCK_BLOCKSTATES(HEAVY_WEIGHTED_PRESSURE_PLATE, "heavy_weighted_pressure_plate", StateProperties::POWER())
    REGISTER_BLOCK_BLOCKSTATES(COMPARATOR, "comparator", StateProperties::FACING_HORIZONTAL(), StateProperties::COMPARATOR_MODE(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DAYLIGHT_DETECTOR, "daylight_detector", StateProperties::INVERTED(), StateProperties::POWER())
    REGISTER_BLOCK(REDSTONE_BLOCK, "redstone_block")
    REGISTER_BLOCK(NETHER_QUARTZ_ORE, "nether_quartz_ore")
    REGISTER_BLOCK_BLOCKSTATES(HOPPER, "hopper", StateProperties::ENABLED(), StateProperties::FACING_HOPPER())
    REGISTER_BLOCK(QUARTZ_BLOCK, "quartz_block")
    REGISTER_BLOCK(CHISELED_QUARTZ_BLOCK, "chiseled_quartz_block")
    REGISTER_BLOCK_BLOCKSTATES(QUARTZ_PILLAR, "quartz_pillar", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(QUARTZ_STAIRS, "quartz_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACTIVATOR_RAIL, "activator_rail", StateProperties::POWERED(), StateProperties::RAIL_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DROPPER, "dropper", StateProperties::FACING_ANY(), StateProperties::TRIGGERED())
    REGISTER_BLOCK(WHITE_TERRACOTTA, "white_terracotta")
    REGISTER_BLOCK(ORANGE_TERRACOTTA, "orange_terracotta")
    REGISTER_BLOCK(MAGENTA_TERRACOTTA, "magenta_terracotta")
    REGISTER_BLOCK(LIGHT_BLUE_TERRACOTTA, "light_blue_terracotta")
    REGISTER_BLOCK(YELLOW_TERRACOTTA, "yellow_terracotta")
    REGISTER_BLOCK(LIME_TERRACOTTA, "lime_terracotta")
    REGISTER_BLOCK(PINK_TERRACOTTA, "pink_terracotta")
    REGISTER_BLOCK(GRAY_TERRACOTTA, "gray_terracotta")
    REGISTER_BLOCK(LIGHT_GRAY_TERRACOTTA, "light_gray_terracotta")
    REGISTER_BLOCK(CYAN_TERRACOTTA, "cyan_terracotta")
    REGISTER_BLOCK(PURPLE_TERRACOTTA, "purple_terracotta")
    REGISTER_BLOCK(BLUE_TERRACOTTA, "blue_terracotta")
    REGISTER_BLOCK(BROWN_TERRACOTTA, "brown_terracotta")
    REGISTER_BLOCK(GREEN_TERRACOTTA, "green_terracotta")
    REGISTER_BLOCK(RED_TERRACOTTA, "red_terracotta")
    REGISTER_BLOCK(BLACK_TERRACOTTA, "black_terracotta")
    REGISTER_BLOCK_BLOCKSTATES(WHITE_STAINED_GLASS_PANE, "white_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_STAINED_GLASS_PANE, "orange_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_STAINED_GLASS_PANE, "magenta_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_STAINED_GLASS_PANE, "light_blue_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_STAINED_GLASS_PANE, "yellow_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(LIME_STAINED_GLASS_PANE, "lime_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(PINK_STAINED_GLASS_PANE, "pink_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_STAINED_GLASS_PANE, "gray_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_STAINED_GLASS_PANE, "light_gray_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_STAINED_GLASS_PANE, "cyan_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_STAINED_GLASS_PANE, "purple_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_STAINED_GLASS_PANE, "blue_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_STAINED_GLASS_PANE, "brown_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_STAINED_GLASS_PANE, "green_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(RED_STAINED_GLASS_PANE, "red_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_STAINED_GLASS_PANE, "black_stained_glass_pane", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_STAIRS, "acacia_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_STAIRS, "cherry_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_STAIRS, "dark_oak_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_STAIRS, "pale_oak_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_STAIRS, "mangrove_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_STAIRS, "bamboo_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_MOSAIC_STAIRS, "bamboo_mosaic_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(SLIME_BLOCK, "slime_block")
    REGISTER_BLOCK_BLOCKSTATES(BARRIER, "barrier", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT, "light", StateProperties::LEVEL_15(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(IRON_TRAPDOOR, "iron_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(PRISMARINE, "prismarine")
    REGISTER_BLOCK(PRISMARINE_BRICKS, "prismarine_bricks")
    REGISTER_BLOCK(DARK_PRISMARINE, "dark_prismarine")
    REGISTER_BLOCK_BLOCKSTATES(PRISMARINE_STAIRS, "prismarine_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PRISMARINE_BRICK_STAIRS, "prismarine_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_PRISMARINE_STAIRS, "dark_prismarine_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PRISMARINE_SLAB, "prismarine_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PRISMARINE_BRICK_SLAB, "prismarine_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_PRISMARINE_SLAB, "dark_prismarine_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(SEA_LANTERN, "sea_lantern")
    REGISTER_BLOCK_BLOCKSTATES(HAY_BLOCK, "hay_block", StateProperties::AXIS())
    REGISTER_BLOCK(WHITE_CARPET, "white_carpet")
    REGISTER_BLOCK(ORANGE_CARPET, "orange_carpet")
    REGISTER_BLOCK(MAGENTA_CARPET, "magenta_carpet")
    REGISTER_BLOCK(LIGHT_BLUE_CARPET, "light_blue_carpet")
    REGISTER_BLOCK(YELLOW_CARPET, "yellow_carpet")
    REGISTER_BLOCK(LIME_CARPET, "lime_carpet")
    REGISTER_BLOCK(PINK_CARPET, "pink_carpet")
    REGISTER_BLOCK(GRAY_CARPET, "gray_carpet")
    REGISTER_BLOCK(LIGHT_GRAY_CARPET, "light_gray_carpet")
    REGISTER_BLOCK(CYAN_CARPET, "cyan_carpet")
    REGISTER_BLOCK(PURPLE_CARPET, "purple_carpet")
    REGISTER_BLOCK(BLUE_CARPET, "blue_carpet")
    REGISTER_BLOCK(BROWN_CARPET, "brown_carpet")
    REGISTER_BLOCK(GREEN_CARPET, "green_carpet")
    REGISTER_BLOCK(RED_CARPET, "red_carpet")
    REGISTER_BLOCK(BLACK_CARPET, "black_carpet")
    REGISTER_BLOCK(TERRACOTTA, "terracotta")
    REGISTER_BLOCK(COAL_BLOCK, "coal_block")
    REGISTER_BLOCK(PACKED_ICE, "packed_ice")
    REGISTER_BLOCK_BLOCKSTATES(SUNFLOWER, "sunflower", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(LILAC, "lilac", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(ROSE_BUSH, "rose_bush", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(PEONY, "peony", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(TALL_GRASS, "tall_grass", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(LARGE_FERN, "large_fern", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_BANNER, "white_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_BANNER, "orange_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_BANNER, "magenta_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_BANNER, "light_blue_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_BANNER, "yellow_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(LIME_BANNER, "lime_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(PINK_BANNER, "pink_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_BANNER, "gray_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_BANNER, "light_gray_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_BANNER, "cyan_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_BANNER, "purple_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_BANNER, "blue_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_BANNER, "brown_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_BANNER, "green_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(RED_BANNER, "red_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_BANNER, "black_banner", StateProperties::ROTATION())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_WALL_BANNER, "white_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_WALL_BANNER, "orange_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_WALL_BANNER, "magenta_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_WALL_BANNER, "light_blue_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_WALL_BANNER, "yellow_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIME_WALL_BANNER, "lime_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(PINK_WALL_BANNER, "pink_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_WALL_BANNER, "gray_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_WALL_BANNER, "light_gray_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_WALL_BANNER, "cyan_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_WALL_BANNER, "purple_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_WALL_BANNER, "blue_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_WALL_BANNER, "brown_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_WALL_BANNER, "green_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(RED_WALL_BANNER, "red_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_WALL_BANNER, "black_wall_banner", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK(RED_SANDSTONE, "red_sandstone")
    REGISTER_BLOCK(CHISELED_RED_SANDSTONE, "chiseled_red_sandstone")
    REGISTER_BLOCK(CUT_RED_SANDSTONE, "cut_red_sandstone")
    REGISTER_BLOCK_BLOCKSTATES(RED_SANDSTONE_STAIRS, "red_sandstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OAK_SLAB, "oak_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_SLAB, "spruce_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_SLAB, "birch_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_SLAB, "jungle_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_SLAB, "acacia_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_SLAB, "cherry_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_SLAB, "dark_oak_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_SLAB, "pale_oak_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_SLAB, "mangrove_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_SLAB, "bamboo_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_MOSAIC_SLAB, "bamboo_mosaic_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STONE_SLAB, "stone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_STONE_SLAB, "smooth_stone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SANDSTONE_SLAB, "sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CUT_SANDSTONE_SLAB, "cut_sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PETRIFIED_OAK_SLAB, "petrified_oak_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COBBLESTONE_SLAB, "cobblestone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BRICK_SLAB, "brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STONE_BRICK_SLAB, "stone_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MUD_BRICK_SLAB, "mud_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(NETHER_BRICK_SLAB, "nether_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(QUARTZ_SLAB, "quartz_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RED_SANDSTONE_SLAB, "red_sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CUT_RED_SANDSTONE_SLAB, "cut_red_sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PURPUR_SLAB, "purpur_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(SMOOTH_STONE, "smooth_stone")
    REGISTER_BLOCK(SMOOTH_SANDSTONE, "smooth_sandstone")
    REGISTER_BLOCK(SMOOTH_QUARTZ, "smooth_quartz")
    REGISTER_BLOCK(SMOOTH_RED_SANDSTONE, "smooth_red_sandstone")
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_FENCE_GATE, "spruce_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_FENCE_GATE, "birch_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_FENCE_GATE, "jungle_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_FENCE_GATE, "acacia_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_FENCE_GATE, "cherry_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_FENCE_GATE, "dark_oak_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_FENCE_GATE, "pale_oak_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_FENCE_GATE, "mangrove_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_FENCE_GATE, "bamboo_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_FENCE, "spruce_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_FENCE, "birch_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_FENCE, "jungle_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_FENCE, "acacia_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_FENCE, "cherry_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_FENCE, "dark_oak_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_FENCE, "pale_oak_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_FENCE, "mangrove_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_FENCE, "bamboo_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(SPRUCE_DOOR, "spruce_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BIRCH_DOOR, "birch_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(JUNGLE_DOOR, "jungle_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(ACACIA_DOOR, "acacia_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CHERRY_DOOR, "cherry_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(DARK_OAK_DOOR, "dark_oak_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(PALE_OAK_DOOR, "pale_oak_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(MANGROVE_DOOR, "mangrove_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO_DOOR, "bamboo_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(END_ROD, "end_rod", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(CHORUS_PLANT, "chorus_plant", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(CHORUS_FLOWER, "chorus_flower", StateProperties::AGE_5())
    REGISTER_BLOCK(PURPUR_BLOCK, "purpur_block")
    REGISTER_BLOCK_BLOCKSTATES(PURPUR_PILLAR, "purpur_pillar", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(PURPUR_STAIRS, "purpur_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(END_STONE_BRICKS, "end_stone_bricks")
    REGISTER_BLOCK_BLOCKSTATES(TORCHFLOWER_CROP, "torchflower_crop", StateProperties::AGE_7())
    REGISTER_BLOCK_BLOCKSTATES(PITCHER_CROP, "pitcher_crop", StateProperties::AGE_4(), StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(PITCHER_PLANT, "pitcher_plant", StateProperties::DOUBLE_BLOCK_HALF())
    REGISTER_BLOCK_BLOCKSTATES(BEETROOTS, "beetroots", StateProperties::AGE_7())
    REGISTER_BLOCK(DIRT_PATH, "dirt_path")
    REGISTER_BLOCK(END_GATEWAY, "end_gateway")
    REGISTER_BLOCK_BLOCKSTATES(REPEATING_COMMAND_BLOCK, "repeating_command_block", StateProperties::CONDITIONAL(), StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(CHAIN_COMMAND_BLOCK, "chain_command_block", StateProperties::CONDITIONAL(), StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(FROSTED_ICE, "frosted_ice", StateProperties::AGE_3())
    REGISTER_BLOCK(MAGMA_BLOCK, "magma_block")
    REGISTER_BLOCK(NETHER_WART_BLOCK, "nether_wart_block")
    REGISTER_BLOCK(RED_NETHER_BRICKS, "red_nether_bricks")
    REGISTER_BLOCK_BLOCKSTATES(BONE_BLOCK, "bone_block", StateProperties::AXIS())
    REGISTER_BLOCK(STRUCTURE_VOID, "structure_void")
    REGISTER_BLOCK_BLOCKSTATES(OBSERVER, "observer", StateProperties::FACING_ANY(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(SHULKER_BOX, "shulker_box", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_SHULKER_BOX, "white_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_SHULKER_BOX, "orange_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_SHULKER_BOX, "magenta_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_SHULKER_BOX, "light_blue_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_SHULKER_BOX, "yellow_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(LIME_SHULKER_BOX, "lime_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(PINK_SHULKER_BOX, "pink_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_SHULKER_BOX, "gray_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_SHULKER_BOX, "light_gray_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_SHULKER_BOX, "cyan_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_SHULKER_BOX, "purple_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_SHULKER_BOX, "blue_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_SHULKER_BOX, "brown_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_SHULKER_BOX, "green_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(RED_SHULKER_BOX, "red_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_SHULKER_BOX, "black_shulker_box", StateProperties::FACING_ANY())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_GLAZED_TERRACOTTA, "white_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_GLAZED_TERRACOTTA, "orange_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_GLAZED_TERRACOTTA, "magenta_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_GLAZED_TERRACOTTA, "light_blue_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_GLAZED_TERRACOTTA, "yellow_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIME_GLAZED_TERRACOTTA, "lime_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(PINK_GLAZED_TERRACOTTA, "pink_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_GLAZED_TERRACOTTA, "gray_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_GLAZED_TERRACOTTA, "light_gray_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_GLAZED_TERRACOTTA, "cyan_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_GLAZED_TERRACOTTA, "purple_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_GLAZED_TERRACOTTA, "blue_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_GLAZED_TERRACOTTA, "brown_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_GLAZED_TERRACOTTA, "green_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(RED_GLAZED_TERRACOTTA, "red_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_GLAZED_TERRACOTTA, "black_glazed_terracotta", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK(WHITE_CONCRETE, "white_concrete")
    REGISTER_BLOCK(ORANGE_CONCRETE, "orange_concrete")
    REGISTER_BLOCK(MAGENTA_CONCRETE, "magenta_concrete")
    REGISTER_BLOCK(LIGHT_BLUE_CONCRETE, "light_blue_concrete")
    REGISTER_BLOCK(YELLOW_CONCRETE, "yellow_concrete")
    REGISTER_BLOCK(LIME_CONCRETE, "lime_concrete")
    REGISTER_BLOCK(PINK_CONCRETE, "pink_concrete")
    REGISTER_BLOCK(GRAY_CONCRETE, "gray_concrete")
    REGISTER_BLOCK(LIGHT_GRAY_CONCRETE, "light_gray_concrete")
    REGISTER_BLOCK(CYAN_CONCRETE, "cyan_concrete")
    REGISTER_BLOCK(PURPLE_CONCRETE, "purple_concrete")
    REGISTER_BLOCK(BLUE_CONCRETE, "blue_concrete")
    REGISTER_BLOCK(BROWN_CONCRETE, "brown_concrete")
    REGISTER_BLOCK(GREEN_CONCRETE, "green_concrete")
    REGISTER_BLOCK(RED_CONCRETE, "red_concrete")
    REGISTER_BLOCK(BLACK_CONCRETE, "black_concrete")
    REGISTER_BLOCK(WHITE_CONCRETE_POWDER, "white_concrete_powder")
    REGISTER_BLOCK(ORANGE_CONCRETE_POWDER, "orange_concrete_powder")
    REGISTER_BLOCK(MAGENTA_CONCRETE_POWDER, "magenta_concrete_powder")
    REGISTER_BLOCK(LIGHT_BLUE_CONCRETE_POWDER, "light_blue_concrete_powder")
    REGISTER_BLOCK(YELLOW_CONCRETE_POWDER, "yellow_concrete_powder")
    REGISTER_BLOCK(LIME_CONCRETE_POWDER, "lime_concrete_powder")
    REGISTER_BLOCK(PINK_CONCRETE_POWDER, "pink_concrete_powder")
    REGISTER_BLOCK(GRAY_CONCRETE_POWDER, "gray_concrete_powder")
    REGISTER_BLOCK(LIGHT_GRAY_CONCRETE_POWDER, "light_gray_concrete_powder")
    REGISTER_BLOCK(CYAN_CONCRETE_POWDER, "cyan_concrete_powder")
    REGISTER_BLOCK(PURPLE_CONCRETE_POWDER, "purple_concrete_powder")
    REGISTER_BLOCK(BLUE_CONCRETE_POWDER, "blue_concrete_powder")
    REGISTER_BLOCK(BROWN_CONCRETE_POWDER, "brown_concrete_powder")
    REGISTER_BLOCK(GREEN_CONCRETE_POWDER, "green_concrete_powder")
    REGISTER_BLOCK(RED_CONCRETE_POWDER, "red_concrete_powder")
    REGISTER_BLOCK(BLACK_CONCRETE_POWDER, "black_concrete_powder")
    REGISTER_BLOCK_BLOCKSTATES(KELP, "kelp", StateProperties::AGE_25())
    REGISTER_BLOCK(KELP_PLANT, "kelp_plant")
    REGISTER_BLOCK(DRIED_KELP_BLOCK, "dried_kelp_block")
    REGISTER_BLOCK_BLOCKSTATES(TURTLE_EGG, "turtle_egg", StateProperties::EGGS(), StateProperties::HATCH())
    REGISTER_BLOCK_BLOCKSTATES(SNIFFER_EGG, "sniffer_egg", StateProperties::HATCH())
    REGISTER_BLOCK(DEAD_TUBE_CORAL_BLOCK, "dead_tube_coral_block")
    REGISTER_BLOCK(DEAD_BRAIN_CORAL_BLOCK, "dead_brain_coral_block")
    REGISTER_BLOCK(DEAD_BUBBLE_CORAL_BLOCK, "dead_bubble_coral_block")
    REGISTER_BLOCK(DEAD_FIRE_CORAL_BLOCK, "dead_fire_coral_block")
    REGISTER_BLOCK(DEAD_HORN_CORAL_BLOCK, "dead_horn_coral_block")
    REGISTER_BLOCK(TUBE_CORAL_BLOCK, "tube_coral_block")
    REGISTER_BLOCK(BRAIN_CORAL_BLOCK, "brain_coral_block")
    REGISTER_BLOCK(BUBBLE_CORAL_BLOCK, "bubble_coral_block")
    REGISTER_BLOCK(FIRE_CORAL_BLOCK, "fire_coral_block")
    REGISTER_BLOCK(HORN_CORAL_BLOCK, "horn_coral_block")
    REGISTER_BLOCK_BLOCKSTATES(DEAD_TUBE_CORAL, "dead_tube_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BRAIN_CORAL, "dead_brain_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BUBBLE_CORAL, "dead_bubble_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_FIRE_CORAL, "dead_fire_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_HORN_CORAL, "dead_horn_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUBE_CORAL, "tube_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BRAIN_CORAL, "brain_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BUBBLE_CORAL, "bubble_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(FIRE_CORAL, "fire_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(HORN_CORAL, "horn_coral", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_TUBE_CORAL_FAN, "dead_tube_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BRAIN_CORAL_FAN, "dead_brain_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BUBBLE_CORAL_FAN, "dead_bubble_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_FIRE_CORAL_FAN, "dead_fire_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_HORN_CORAL_FAN, "dead_horn_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUBE_CORAL_FAN, "tube_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BRAIN_CORAL_FAN, "brain_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BUBBLE_CORAL_FAN, "bubble_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(FIRE_CORAL_FAN, "fire_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(HORN_CORAL_FAN, "horn_coral_fan", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_TUBE_CORAL_WALL_FAN, "dead_tube_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BRAIN_CORAL_WALL_FAN, "dead_brain_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_BUBBLE_CORAL_WALL_FAN, "dead_bubble_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_FIRE_CORAL_WALL_FAN, "dead_fire_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEAD_HORN_CORAL_WALL_FAN, "dead_horn_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUBE_CORAL_WALL_FAN, "tube_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BRAIN_CORAL_WALL_FAN, "brain_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BUBBLE_CORAL_WALL_FAN, "bubble_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(FIRE_CORAL_WALL_FAN, "fire_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(HORN_CORAL_WALL_FAN, "horn_coral_wall_fan", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SEA_PICKLE, "sea_pickle", StateProperties::PICKLES(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(BLUE_ICE, "blue_ice")
    REGISTER_BLOCK_BLOCKSTATES(CONDUIT, "conduit", StateProperties::WATERLOGGED())
    REGISTER_BLOCK(BAMBOO_SAPLING, "bamboo_sapling")
    REGISTER_BLOCK_BLOCKSTATES(BAMBOO, "bamboo", StateProperties::AGE_1(), StateProperties::BAMBOO_LEAVES(), StateProperties::STAGE())
    REGISTER_BLOCK(POTTED_BAMBOO, "potted_bamboo")
    REGISTER_BLOCK(VOID_AIR, "void_air")
    REGISTER_BLOCK(CAVE_AIR, "cave_air")
    REGISTER_BLOCK_BLOCKSTATES(BUBBLE_COLUMN, "bubble_column", StateProperties::DRAG())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_GRANITE_STAIRS, "polished_granite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_RED_SANDSTONE_STAIRS, "smooth_red_sandstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_STONE_BRICK_STAIRS, "mossy_stone_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_DIORITE_STAIRS, "polished_diorite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_COBBLESTONE_STAIRS, "mossy_cobblestone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(END_STONE_BRICK_STAIRS, "end_stone_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STONE_STAIRS, "stone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_SANDSTONE_STAIRS, "smooth_sandstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_QUARTZ_STAIRS, "smooth_quartz_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(GRANITE_STAIRS, "granite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ANDESITE_STAIRS, "andesite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RED_NETHER_BRICK_STAIRS, "red_nether_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_ANDESITE_STAIRS, "polished_andesite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DIORITE_STAIRS, "diorite_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_GRANITE_SLAB, "polished_granite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_RED_SANDSTONE_SLAB, "smooth_red_sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_STONE_BRICK_SLAB, "mossy_stone_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_DIORITE_SLAB, "polished_diorite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_COBBLESTONE_SLAB, "mossy_cobblestone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(END_STONE_BRICK_SLAB, "end_stone_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_SANDSTONE_SLAB, "smooth_sandstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMOOTH_QUARTZ_SLAB, "smooth_quartz_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(GRANITE_SLAB, "granite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ANDESITE_SLAB, "andesite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RED_NETHER_BRICK_SLAB, "red_nether_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_ANDESITE_SLAB, "polished_andesite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DIORITE_SLAB, "diorite_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BRICK_WALL, "brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(PRISMARINE_WALL, "prismarine_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(RED_SANDSTONE_WALL, "red_sandstone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(MOSSY_STONE_BRICK_WALL, "mossy_stone_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(GRANITE_WALL, "granite_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(STONE_BRICK_WALL, "stone_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(MUD_BRICK_WALL, "mud_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(NETHER_BRICK_WALL, "nether_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(ANDESITE_WALL, "andesite_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(RED_NETHER_BRICK_WALL, "red_nether_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(SANDSTONE_WALL, "sandstone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(END_STONE_BRICK_WALL, "end_stone_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(DIORITE_WALL, "diorite_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(SCAFFOLDING, "scaffolding", StateProperties::BOTTOM(), StateProperties::DISTANCE_0_7(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LOOM, "loom", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BARREL, "barrel", StateProperties::FACING_ANY(), StateProperties::OPEN())
    REGISTER_BLOCK_BLOCKSTATES(SMOKER, "smoker", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(BLAST_FURNACE, "blast_furnace", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT())
    REGISTER_BLOCK(CARTOGRAPHY_TABLE, "cartography_table")
    REGISTER_BLOCK(FLETCHING_TABLE, "fletching_table")
    REGISTER_BLOCK_BLOCKSTATES(GRINDSTONE, "grindstone", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(LECTERN, "lectern", StateProperties::FACING_HORIZONTAL(), StateProperties::HAS_BOOK(), StateProperties::POWERED())
    REGISTER_BLOCK(SMITHING_TABLE, "smithing_table")
    REGISTER_BLOCK_BLOCKSTATES(STONECUTTER, "stonecutter", StateProperties::FACING_HORIZONTAL())
    REGISTER_BLOCK_BLOCKSTATES(BELL, "bell", StateProperties::ATTACHMENT(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(LANTERN, "lantern", StateProperties::HANGING(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SOUL_LANTERN, "soul_lantern", StateProperties::HANGING(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CAMPFIRE, "campfire", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT(), StateProperties::SIGNAL_FIRE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SOUL_CAMPFIRE, "soul_campfire", StateProperties::FACING_HORIZONTAL(), StateProperties::LIT(), StateProperties::SIGNAL_FIRE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SWEET_BERRY_BUSH, "sweet_berry_bush", StateProperties::AGE_3())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_STEM, "warped_stem", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_WARPED_STEM, "stripped_warped_stem", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_HYPHAE, "warped_hyphae", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_WARPED_HYPHAE, "stripped_warped_hyphae", StateProperties::AXIS())
    REGISTER_BLOCK(WARPED_NYLIUM, "warped_nylium")
    REGISTER_BLOCK(WARPED_FUNGUS, "warped_fungus")
    REGISTER_BLOCK(WARPED_WART_BLOCK, "warped_wart_block")
    REGISTER_BLOCK(WARPED_ROOTS, "warped_roots")
    REGISTER_BLOCK(NETHER_SPROUTS, "nether_sprouts")
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_STEM, "crimson_stem", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_CRIMSON_STEM, "stripped_crimson_stem", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_HYPHAE, "crimson_hyphae", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(STRIPPED_CRIMSON_HYPHAE, "stripped_crimson_hyphae", StateProperties::AXIS())
    REGISTER_BLOCK(CRIMSON_NYLIUM, "crimson_nylium")
    REGISTER_BLOCK(CRIMSON_FUNGUS, "crimson_fungus")
    REGISTER_BLOCK(SHROOMLIGHT, "shroomlight")
    REGISTER_BLOCK_BLOCKSTATES(WEEPING_VINES, "weeping_vines", StateProperties::AGE_25())
    REGISTER_BLOCK(WEEPING_VINES_PLANT, "weeping_vines_plant")
    REGISTER_BLOCK_BLOCKSTATES(TWISTING_VINES, "twisting_vines", StateProperties::AGE_25())
    REGISTER_BLOCK(TWISTING_VINES_PLANT, "twisting_vines_plant")
    REGISTER_BLOCK(CRIMSON_ROOTS, "crimson_roots")
    REGISTER_BLOCK(CRIMSON_PLANKS, "crimson_planks")
    REGISTER_BLOCK(WARPED_PLANKS, "warped_planks")
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_SLAB, "crimson_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_SLAB, "warped_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_PRESSURE_PLATE, "crimson_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_PRESSURE_PLATE, "warped_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_FENCE, "crimson_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_FENCE, "warped_fence", StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_TRAPDOOR, "crimson_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_TRAPDOOR, "warped_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_FENCE_GATE, "crimson_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_FENCE_GATE, "warped_fence_gate", StateProperties::FACING_HORIZONTAL(), StateProperties::IN_WALL(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_STAIRS, "crimson_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_STAIRS, "warped_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_BUTTON, "crimson_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_BUTTON, "warped_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_DOOR, "crimson_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_DOOR, "warped_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_SIGN, "crimson_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_SIGN, "warped_sign", StateProperties::ROTATION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRIMSON_WALL_SIGN, "crimson_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WARPED_WALL_SIGN, "warped_wall_sign", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(STRUCTURE_BLOCK, "structure_block", StateProperties::STRUCTURE_BLOCK_MODE())
    REGISTER_BLOCK_BLOCKSTATES(JIGSAW, "jigsaw", StateProperties::ORIENTATION())
    REGISTER_BLOCK_BLOCKSTATES(TEST_BLOCK, "test_block", StateProperties::TEST_BLOCK_MODE())
    REGISTER_BLOCK(TEST_INSTANCE_BLOCK, "test_instance_block")
    REGISTER_BLOCK_BLOCKSTATES(COMPOSTER, "composter", StateProperties::LEVEL_8())
    REGISTER_BLOCK_BLOCKSTATES(TARGET, "target", StateProperties::POWER())
    REGISTER_BLOCK_BLOCKSTATES(BEE_NEST, "bee_nest", StateProperties::FACING_HORIZONTAL(), StateProperties::HONEY_LEVEL())
    REGISTER_BLOCK_BLOCKSTATES(BEEHIVE, "beehive", StateProperties::FACING_HORIZONTAL(), StateProperties::HONEY_LEVEL())
    REGISTER_BLOCK(HONEY_BLOCK, "honey_block")
    REGISTER_BLOCK(HONEYCOMB_BLOCK, "honeycomb_block")
    REGISTER_BLOCK(NETHERITE_BLOCK, "netherite_block")
    REGISTER_BLOCK(ANCIENT_DEBRIS, "ancient_debris")
    REGISTER_BLOCK(CRYING_OBSIDIAN, "crying_obsidian")
    REGISTER_BLOCK_BLOCKSTATES(RESPAWN_ANCHOR, "respawn_anchor", StateProperties::CHARGES())
    REGISTER_BLOCK(POTTED_CRIMSON_FUNGUS, "potted_crimson_fungus")
    REGISTER_BLOCK(POTTED_WARPED_FUNGUS, "potted_warped_fungus")
    REGISTER_BLOCK(POTTED_CRIMSON_ROOTS, "potted_crimson_roots")
    REGISTER_BLOCK(POTTED_WARPED_ROOTS, "potted_warped_roots")
    REGISTER_BLOCK(LODESTONE, "lodestone")
    REGISTER_BLOCK(BLACKSTONE, "blackstone")
    REGISTER_BLOCK_BLOCKSTATES(BLACKSTONE_STAIRS, "blackstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BLACKSTONE_WALL, "blackstone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK_BLOCKSTATES(BLACKSTONE_SLAB, "blackstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(POLISHED_BLACKSTONE, "polished_blackstone")
    REGISTER_BLOCK(POLISHED_BLACKSTONE_BRICKS, "polished_blackstone_bricks")
    REGISTER_BLOCK(CRACKED_POLISHED_BLACKSTONE_BRICKS, "cracked_polished_blackstone_bricks")
    REGISTER_BLOCK(CHISELED_POLISHED_BLACKSTONE, "chiseled_polished_blackstone")
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_BRICK_SLAB, "polished_blackstone_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_BRICK_STAIRS, "polished_blackstone_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_BRICK_WALL, "polished_blackstone_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(GILDED_BLACKSTONE, "gilded_blackstone")
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_STAIRS, "polished_blackstone_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_SLAB, "polished_blackstone_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_PRESSURE_PLATE, "polished_blackstone_pressure_plate", StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_BUTTON, "polished_blackstone_button", StateProperties::BLOCK_FACE(), StateProperties::FACING_HORIZONTAL(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_BLACKSTONE_WALL, "polished_blackstone_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(CHISELED_NETHER_BRICKS, "chiseled_nether_bricks")
    REGISTER_BLOCK(CRACKED_NETHER_BRICKS, "cracked_nether_bricks")
    REGISTER_BLOCK(QUARTZ_BRICKS, "quartz_bricks")
    REGISTER_BLOCK_BLOCKSTATES(CANDLE, "candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_CANDLE, "white_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_CANDLE, "orange_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_CANDLE, "magenta_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_CANDLE, "light_blue_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_CANDLE, "yellow_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LIME_CANDLE, "lime_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PINK_CANDLE, "pink_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_CANDLE, "gray_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_CANDLE, "light_gray_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_CANDLE, "cyan_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_CANDLE, "purple_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_CANDLE, "blue_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_CANDLE, "brown_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_CANDLE, "green_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(RED_CANDLE, "red_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_CANDLE, "black_candle", StateProperties::CANDLES(), StateProperties::LIT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CANDLE_CAKE, "candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(WHITE_CANDLE_CAKE, "white_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(ORANGE_CANDLE_CAKE, "orange_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(MAGENTA_CANDLE_CAKE, "magenta_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_BLUE_CANDLE_CAKE, "light_blue_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(YELLOW_CANDLE_CAKE, "yellow_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(LIME_CANDLE_CAKE, "lime_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(PINK_CANDLE_CAKE, "pink_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(GRAY_CANDLE_CAKE, "gray_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(LIGHT_GRAY_CANDLE_CAKE, "light_gray_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(CYAN_CANDLE_CAKE, "cyan_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(PURPLE_CANDLE_CAKE, "purple_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(BLUE_CANDLE_CAKE, "blue_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(BROWN_CANDLE_CAKE, "brown_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(GREEN_CANDLE_CAKE, "green_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(RED_CANDLE_CAKE, "red_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK_BLOCKSTATES(BLACK_CANDLE_CAKE, "black_candle_cake", StateProperties::LIT())
    REGISTER_BLOCK(AMETHYST_BLOCK, "amethyst_block")
    REGISTER_BLOCK(BUDDING_AMETHYST, "budding_amethyst")
    REGISTER_BLOCK_BLOCKSTATES(AMETHYST_CLUSTER, "amethyst_cluster", StateProperties::FACING_ANY(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(LARGE_AMETHYST_BUD, "large_amethyst_bud", StateProperties::FACING_ANY(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(MEDIUM_AMETHYST_BUD, "medium_amethyst_bud", StateProperties::FACING_ANY(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMALL_AMETHYST_BUD, "small_amethyst_bud", StateProperties::FACING_ANY(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(TUFF, "tuff")
    REGISTER_BLOCK_BLOCKSTATES(TUFF_SLAB, "tuff_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUFF_STAIRS, "tuff_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUFF_WALL, "tuff_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(POLISHED_TUFF, "polished_tuff")
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_TUFF_SLAB, "polished_tuff_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_TUFF_STAIRS, "polished_tuff_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_TUFF_WALL, "polished_tuff_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(CHISELED_TUFF, "chiseled_tuff")
    REGISTER_BLOCK(TUFF_BRICKS, "tuff_bricks")
    REGISTER_BLOCK_BLOCKSTATES(TUFF_BRICK_SLAB, "tuff_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUFF_BRICK_STAIRS, "tuff_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(TUFF_BRICK_WALL, "tuff_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(CHISELED_TUFF_BRICKS, "chiseled_tuff_bricks")
    REGISTER_BLOCK(CALCITE, "calcite")
    REGISTER_BLOCK(TINTED_GLASS, "tinted_glass")
    REGISTER_BLOCK(POWDER_SNOW, "powder_snow")
    REGISTER_BLOCK_BLOCKSTATES(SCULK_SENSOR, "sculk_sensor", StateProperties::POWER(), StateProperties::SCULK_SENSOR_PHASE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CALIBRATED_SCULK_SENSOR, "calibrated_sculk_sensor", StateProperties::FACING_HORIZONTAL(), StateProperties::POWER(), StateProperties::SCULK_SENSOR_PHASE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(SCULK, "sculk")
    REGISTER_BLOCK_BLOCKSTATES(SCULK_VEIN, "sculk_vein", StateProperties::DIRECTION_DOWN(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(SCULK_CATALYST, "sculk_catalyst", StateProperties::BLOOM())
    REGISTER_BLOCK_BLOCKSTATES(SCULK_SHRIEKER, "sculk_shrieker", StateProperties::CAN_SUMMON(), StateProperties::SHRIEKING(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(COPPER_BLOCK, "copper_block")
    REGISTER_BLOCK(EXPOSED_COPPER, "exposed_copper")
    REGISTER_BLOCK(WEATHERED_COPPER, "weathered_copper")
    REGISTER_BLOCK(OXIDIZED_COPPER, "oxidized_copper")
    REGISTER_BLOCK(COPPER_ORE, "copper_ore")
    REGISTER_BLOCK(DEEPSLATE_COPPER_ORE, "deepslate_copper_ore")
    REGISTER_BLOCK(OXIDIZED_CUT_COPPER, "oxidized_cut_copper")
    REGISTER_BLOCK(WEATHERED_CUT_COPPER, "weathered_cut_copper")
    REGISTER_BLOCK(EXPOSED_CUT_COPPER, "exposed_cut_copper")
    REGISTER_BLOCK(CUT_COPPER, "cut_copper")
    REGISTER_BLOCK(OXIDIZED_CHISELED_COPPER, "oxidized_chiseled_copper")
    REGISTER_BLOCK(WEATHERED_CHISELED_COPPER, "weathered_chiseled_copper")
    REGISTER_BLOCK(EXPOSED_CHISELED_COPPER, "exposed_chiseled_copper")
    REGISTER_BLOCK(CHISELED_COPPER, "chiseled_copper")
    REGISTER_BLOCK(WAXED_OXIDIZED_CHISELED_COPPER, "waxed_oxidized_chiseled_copper")
    REGISTER_BLOCK(WAXED_WEATHERED_CHISELED_COPPER, "waxed_weathered_chiseled_copper")
    REGISTER_BLOCK(WAXED_EXPOSED_CHISELED_COPPER, "waxed_exposed_chiseled_copper")
    REGISTER_BLOCK(WAXED_CHISELED_COPPER, "waxed_chiseled_copper")
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_CUT_COPPER_STAIRS, "oxidized_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_CUT_COPPER_STAIRS, "weathered_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_CUT_COPPER_STAIRS, "exposed_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CUT_COPPER_STAIRS, "cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_CUT_COPPER_SLAB, "oxidized_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_CUT_COPPER_SLAB, "weathered_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_CUT_COPPER_SLAB, "exposed_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CUT_COPPER_SLAB, "cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(WAXED_COPPER_BLOCK, "waxed_copper_block")
    REGISTER_BLOCK(WAXED_WEATHERED_COPPER, "waxed_weathered_copper")
    REGISTER_BLOCK(WAXED_EXPOSED_COPPER, "waxed_exposed_copper")
    REGISTER_BLOCK(WAXED_OXIDIZED_COPPER, "waxed_oxidized_copper")
    REGISTER_BLOCK(WAXED_OXIDIZED_CUT_COPPER, "waxed_oxidized_cut_copper")
    REGISTER_BLOCK(WAXED_WEATHERED_CUT_COPPER, "waxed_weathered_cut_copper")
    REGISTER_BLOCK(WAXED_EXPOSED_CUT_COPPER, "waxed_exposed_cut_copper")
    REGISTER_BLOCK(WAXED_CUT_COPPER, "waxed_cut_copper")
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_CUT_COPPER_STAIRS, "waxed_oxidized_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_CUT_COPPER_STAIRS, "waxed_weathered_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_CUT_COPPER_STAIRS, "waxed_exposed_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_CUT_COPPER_STAIRS, "waxed_cut_copper_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_CUT_COPPER_SLAB, "waxed_oxidized_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_CUT_COPPER_SLAB, "waxed_weathered_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_CUT_COPPER_SLAB, "waxed_exposed_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_CUT_COPPER_SLAB, "waxed_cut_copper_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COPPER_DOOR, "copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_COPPER_DOOR, "exposed_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_COPPER_DOOR, "oxidized_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_COPPER_DOOR, "weathered_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_COPPER_DOOR, "waxed_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_COPPER_DOOR, "waxed_exposed_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_COPPER_DOOR, "waxed_oxidized_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_COPPER_DOOR, "waxed_weathered_copper_door", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::DOOR_HINGE(), StateProperties::OPEN(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(COPPER_TRAPDOOR, "copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_COPPER_TRAPDOOR, "exposed_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_COPPER_TRAPDOOR, "oxidized_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_COPPER_TRAPDOOR, "weathered_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_COPPER_TRAPDOOR, "waxed_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_COPPER_TRAPDOOR, "waxed_exposed_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_COPPER_TRAPDOOR, "waxed_oxidized_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_COPPER_TRAPDOOR, "waxed_weathered_copper_trapdoor", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::OPEN(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COPPER_GRATE, "copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_COPPER_GRATE, "exposed_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_COPPER_GRATE, "weathered_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_COPPER_GRATE, "oxidized_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_COPPER_GRATE, "waxed_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_COPPER_GRATE, "waxed_exposed_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_COPPER_GRATE, "waxed_weathered_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_COPPER_GRATE, "waxed_oxidized_copper_grate", StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COPPER_BULB, "copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(EXPOSED_COPPER_BULB, "exposed_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WEATHERED_COPPER_BULB, "weathered_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(OXIDIZED_COPPER_BULB, "oxidized_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_COPPER_BULB, "waxed_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_EXPOSED_COPPER_BULB, "waxed_exposed_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_WEATHERED_COPPER_BULB, "waxed_weathered_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(WAXED_OXIDIZED_COPPER_BULB, "waxed_oxidized_copper_bulb", StateProperties::LIT(), StateProperties::POWERED())
    REGISTER_BLOCK_BLOCKSTATES(LIGHTNING_ROD, "lightning_rod", StateProperties::FACING_ANY(), StateProperties::POWERED(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POINTED_DRIPSTONE, "pointed_dripstone", StateProperties::THICKNESS(), StateProperties::VERTICAL_DIRECTION(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK(DRIPSTONE_BLOCK, "dripstone_block")
    REGISTER_BLOCK_BLOCKSTATES(CAVE_VINES, "cave_vines", StateProperties::AGE_25(), StateProperties::BERRIES())
    REGISTER_BLOCK_BLOCKSTATES(CAVE_VINES_PLANT, "cave_vines_plant", StateProperties::BERRIES())
    REGISTER_BLOCK(SPORE_BLOSSOM, "spore_blossom")
    REGISTER_BLOCK(AZALEA, "azalea")
    REGISTER_BLOCK(FLOWERING_AZALEA, "flowering_azalea")
    REGISTER_BLOCK(MOSS_CARPET, "moss_carpet")
    REGISTER_BLOCK_BLOCKSTATES(PINK_PETALS, "pink_petals", StateProperties::FACING_HORIZONTAL(), StateProperties::FLOWER_AMOUNT())
    REGISTER_BLOCK_BLOCKSTATES(WILDFLOWERS, "wildflowers", StateProperties::FACING_HORIZONTAL(), StateProperties::FLOWER_AMOUNT())
    REGISTER_BLOCK_BLOCKSTATES(LEAF_LITTER, "leaf_litter", StateProperties::FACING_HORIZONTAL(), StateProperties::SEGMENT_AMOUNT())
    REGISTER_BLOCK(MOSS_BLOCK, "moss_block")
    REGISTER_BLOCK_BLOCKSTATES(BIG_DRIPLEAF, "big_dripleaf", StateProperties::FACING_HORIZONTAL(), StateProperties::TILT(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(BIG_DRIPLEAF_STEM, "big_dripleaf_stem", StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(SMALL_DRIPLEAF, "small_dripleaf", StateProperties::FACING_HORIZONTAL(), StateProperties::DOUBLE_BLOCK_HALF(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(HANGING_ROOTS, "hanging_roots", StateProperties::WATERLOGGED())
    REGISTER_BLOCK(ROOTED_DIRT, "rooted_dirt")
    REGISTER_BLOCK(MUD, "mud")
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE, "deepslate", StateProperties::AXIS())
    REGISTER_BLOCK(COBBLED_DEEPSLATE, "cobbled_deepslate")
    REGISTER_BLOCK_BLOCKSTATES(COBBLED_DEEPSLATE_STAIRS, "cobbled_deepslate_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COBBLED_DEEPSLATE_SLAB, "cobbled_deepslate_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(COBBLED_DEEPSLATE_WALL, "cobbled_deepslate_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(POLISHED_DEEPSLATE, "polished_deepslate")
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_DEEPSLATE_STAIRS, "polished_deepslate_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_DEEPSLATE_SLAB, "polished_deepslate_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(POLISHED_DEEPSLATE_WALL, "polished_deepslate_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(DEEPSLATE_TILES, "deepslate_tiles")
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_TILE_STAIRS, "deepslate_tile_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_TILE_SLAB, "deepslate_tile_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_TILE_WALL, "deepslate_tile_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(DEEPSLATE_BRICKS, "deepslate_bricks")
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_BRICK_STAIRS, "deepslate_brick_stairs", StateProperties::FACING_HORIZONTAL(), StateProperties::BLOCK_HALF(), StateProperties::STAIR_SHAPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_BRICK_SLAB, "deepslate_brick_slab", StateProperties::SLAB_TYPE(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(DEEPSLATE_BRICK_WALL, "deepslate_brick_wall", StateProperties::EAST_WALL_SHAPE(), StateProperties::NORTH_WALL_SHAPE(), StateProperties::SOUTH_WALL_SHAPE(), StateProperties::DIRECTION_UP(), StateProperties::WATERLOGGED(), StateProperties::WEST_WALL_SHAPE())
    REGISTER_BLOCK(CHISELED_DEEPSLATE, "chiseled_deepslate")
    REGISTER_BLOCK(CRACKED_DEEPSLATE_BRICKS, "cracked_deepslate_bricks")
    REGISTER_BLOCK(CRACKED_DEEPSLATE_TILES, "cracked_deepslate_tiles")
    REGISTER_BLOCK_BLOCKSTATES(INFESTED_DEEPSLATE, "infested_deepslate", StateProperties::AXIS())
    REGISTER_BLOCK(SMOOTH_BASALT, "smooth_basalt")
    REGISTER_BLOCK(RAW_IRON_BLOCK, "raw_iron_block")
    REGISTER_BLOCK(RAW_COPPER_BLOCK, "raw_copper_block")
    REGISTER_BLOCK(RAW_GOLD_BLOCK, "raw_gold_block")
    REGISTER_BLOCK(POTTED_AZALEA_BUSH, "potted_azalea_bush")
    REGISTER_BLOCK(POTTED_FLOWERING_AZALEA_BUSH, "potted_flowering_azalea_bush")
    REGISTER_BLOCK_BLOCKSTATES(OCHRE_FROGLIGHT, "ochre_froglight", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(VERDANT_FROGLIGHT, "verdant_froglight", StateProperties::AXIS())
    REGISTER_BLOCK_BLOCKSTATES(PEARLESCENT_FROGLIGHT, "pearlescent_froglight", StateProperties::AXIS())
    REGISTER_BLOCK(FROGSPAWN, "frogspawn")
    REGISTER_BLOCK(REINFORCED_DEEPSLATE, "reinforced_deepslate")
    REGISTER_BLOCK_BLOCKSTATES(DECORATED_POT, "decorated_pot", StateProperties::CRACKED(), StateProperties::FACING_HORIZONTAL(), StateProperties::WATERLOGGED())
    REGISTER_BLOCK_BLOCKSTATES(CRAFTER, "crafter", StateProperties::CRAFTING(), StateProperties::ORIENTATION(), StateProperties::TRIGGERED())
    REGISTER_BLOCK_BLOCKSTATES(TRIAL_SPAWNER, "trial_spawner", StateProperties::OMINOUS(), StateProperties::TRIAL_SPAWNER_STATE())
    REGISTER_BLOCK_BLOCKSTATES(VAULT, "vault", StateProperties::FACING_HORIZONTAL(), StateProperties::OMINOUS(), StateProperties::VAULT_STATE())
    REGISTER_BLOCK_BLOCKSTATES(HEAVY_CORE, "heavy_core", StateProperties::WATERLOGGED())
    REGISTER_BLOCK(PALE_MOSS_BLOCK, "pale_moss_block")
    REGISTER_BLOCK_BLOCKSTATES(PALE_MOSS_CARPET, "pale_moss_carpet", StateProperties::BOTTOM(), StateProperties::DIRECTION_EAST(), StateProperties::DIRECTION_NORTH(), StateProperties::DIRECTION_SOUTH(), StateProperties::DIRECTION_WEST())
    REGISTER_BLOCK_BLOCKSTATES(PALE_HANGING_MOSS, "pale_hanging_moss", StateProperties::TIP())
    REGISTER_BLOCK(OPEN_EYEBLOSSOM, "open_eyeblossom")
    REGISTER_BLOCK(CLOSED_EYEBLOSSOM, "closed_eyeblossom")
    REGISTER_BLOCK(POTTED_OPEN_EYEBLOSSOM, "potted_open_eyeblossom")
    REGISTER_BLOCK(POTTED_CLOSED_EYEBLOSSOM, "potted_closed_eyeblossom")
    REGISTER_BLOCK(FIREFLY_BUSH, "firefly_bush")

void Blocks::registerBlocks() {
    AIR();
    STONE();
    GRANITE();
    POLISHED_GRANITE();
    DIORITE();
    POLISHED_DIORITE();
    ANDESITE();
    POLISHED_ANDESITE();
    GRASS_BLOCK();
    DIRT();
    COARSE_DIRT();
    PODZOL();
    COBBLESTONE();
    OAK_PLANKS();
    SPRUCE_PLANKS();
    BIRCH_PLANKS();
    JUNGLE_PLANKS();
    ACACIA_PLANKS();
    CHERRY_PLANKS();
    DARK_OAK_PLANKS();
    PALE_OAK_WOOD();
    PALE_OAK_PLANKS();
    MANGROVE_PLANKS();
    BAMBOO_PLANKS();
    BAMBOO_MOSAIC();
    OAK_SAPLING();
    SPRUCE_SAPLING();
    BIRCH_SAPLING();
    JUNGLE_SAPLING();
    ACACIA_SAPLING();
    CHERRY_SAPLING();
    DARK_OAK_SAPLING();
    PALE_OAK_SAPLING();
    MANGROVE_PROPAGULE();
    BEDROCK();
    WATER();
    LAVA();
    SAND();
    SUSPICIOUS_SAND();
    RED_SAND();
    GRAVEL();
    SUSPICIOUS_GRAVEL();
    GOLD_ORE();
    DEEPSLATE_GOLD_ORE();
    IRON_ORE();
    DEEPSLATE_IRON_ORE();
    COAL_ORE();
    DEEPSLATE_COAL_ORE();
    NETHER_GOLD_ORE();
    OAK_LOG();
    SPRUCE_LOG();
    BIRCH_LOG();
    JUNGLE_LOG();
    ACACIA_LOG();
    CHERRY_LOG();
    DARK_OAK_LOG();
    PALE_OAK_LOG();
    MANGROVE_LOG();
    MANGROVE_ROOTS();
    MUDDY_MANGROVE_ROOTS();
    BAMBOO_BLOCK();
    STRIPPED_SPRUCE_LOG();
    STRIPPED_BIRCH_LOG();
    STRIPPED_JUNGLE_LOG();
    STRIPPED_ACACIA_LOG();
    STRIPPED_CHERRY_LOG();
    STRIPPED_DARK_OAK_LOG();
    STRIPPED_PALE_OAK_LOG();
    STRIPPED_OAK_LOG();
    STRIPPED_MANGROVE_LOG();
    STRIPPED_BAMBOO_BLOCK();
    OAK_WOOD();
    SPRUCE_WOOD();
    BIRCH_WOOD();
    JUNGLE_WOOD();
    ACACIA_WOOD();
    CHERRY_WOOD();
    DARK_OAK_WOOD();
    MANGROVE_WOOD();
    STRIPPED_OAK_WOOD();
    STRIPPED_SPRUCE_WOOD();
    STRIPPED_BIRCH_WOOD();
    STRIPPED_JUNGLE_WOOD();
    STRIPPED_ACACIA_WOOD();
    STRIPPED_CHERRY_WOOD();
    STRIPPED_DARK_OAK_WOOD();
    STRIPPED_PALE_OAK_WOOD();
    STRIPPED_MANGROVE_WOOD();
    OAK_LEAVES();
    SPRUCE_LEAVES();
    BIRCH_LEAVES();
    JUNGLE_LEAVES();
    ACACIA_LEAVES();
    CHERRY_LEAVES();
    DARK_OAK_LEAVES();
    PALE_OAK_LEAVES();
    MANGROVE_LEAVES();
    AZALEA_LEAVES();
    FLOWERING_AZALEA_LEAVES();
    SPONGE();
    WET_SPONGE();
    GLASS();
    LAPIS_ORE();
    DEEPSLATE_LAPIS_ORE();
    LAPIS_BLOCK();
    DISPENSER();
    SANDSTONE();
    CHISELED_SANDSTONE();
    CUT_SANDSTONE();
    NOTE_BLOCK();
    WHITE_BED();
    ORANGE_BED();
    MAGENTA_BED();
    LIGHT_BLUE_BED();
    YELLOW_BED();
    LIME_BED();
    PINK_BED();
    GRAY_BED();
    LIGHT_GRAY_BED();
    CYAN_BED();
    PURPLE_BED();
    BLUE_BED();
    BROWN_BED();
    GREEN_BED();
    RED_BED();
    BLACK_BED();
    POWERED_RAIL();
    DETECTOR_RAIL();
    STICKY_PISTON();
    COBWEB();
    SHORT_GRASS();
    FERN();
    DEAD_BUSH();
    BUSH();
    SHORT_DRY_GRASS();
    TALL_DRY_GRASS();
    SEAGRASS();
    TALL_SEAGRASS();
    PISTON();
    PISTON_HEAD();
    WHITE_WOOL();
    ORANGE_WOOL();
    MAGENTA_WOOL();
    LIGHT_BLUE_WOOL();
    YELLOW_WOOL();
    LIME_WOOL();
    PINK_WOOL();
    GRAY_WOOL();
    LIGHT_GRAY_WOOL();
    CYAN_WOOL();
    PURPLE_WOOL();
    BLUE_WOOL();
    BROWN_WOOL();
    GREEN_WOOL();
    RED_WOOL();
    BLACK_WOOL();
    MOVING_PISTON();
    DANDELION();
    TORCHFLOWER();
    POPPY();
    BLUE_ORCHID();
    ALLIUM();
    AZURE_BLUET();
    RED_TULIP();
    ORANGE_TULIP();
    WHITE_TULIP();
    PINK_TULIP();
    OXEYE_DAISY();
    CORNFLOWER();
    WITHER_ROSE();
    LILY_OF_THE_VALLEY();
    BROWN_MUSHROOM();
    RED_MUSHROOM();
    GOLD_BLOCK();
    IRON_BLOCK();
    BRICKS();
    TNT();
    BOOKSHELF();
    CHISELED_BOOKSHELF();
    MOSSY_COBBLESTONE();
    OBSIDIAN();
    TORCH();
    WALL_TORCH();
    FIRE();
    SOUL_FIRE();
    SPAWNER();
    CREAKING_HEART();
    OAK_STAIRS();
    CHEST();
    REDSTONE_WIRE();
    DIAMOND_ORE();
    DEEPSLATE_DIAMOND_ORE();
    DIAMOND_BLOCK();
    CRAFTING_TABLE();
    WHEAT();
    FARMLAND();
    FURNACE();
    OAK_SIGN();
    SPRUCE_SIGN();
    BIRCH_SIGN();
    ACACIA_SIGN();
    CHERRY_SIGN();
    JUNGLE_SIGN();
    DARK_OAK_SIGN();
    PALE_OAK_SIGN();
    MANGROVE_SIGN();
    BAMBOO_SIGN();
    OAK_DOOR();
    LADDER();
    RAIL();
    COBBLESTONE_STAIRS();
    OAK_WALL_SIGN();
    SPRUCE_WALL_SIGN();
    BIRCH_WALL_SIGN();
    ACACIA_WALL_SIGN();
    CHERRY_WALL_SIGN();
    JUNGLE_WALL_SIGN();
    DARK_OAK_WALL_SIGN();
    PALE_OAK_WALL_SIGN();
    MANGROVE_WALL_SIGN();
    BAMBOO_WALL_SIGN();
    OAK_HANGING_SIGN();
    SPRUCE_HANGING_SIGN();
    BIRCH_HANGING_SIGN();
    ACACIA_HANGING_SIGN();
    CHERRY_HANGING_SIGN();
    JUNGLE_HANGING_SIGN();
    DARK_OAK_HANGING_SIGN();
    PALE_OAK_HANGING_SIGN();
    CRIMSON_HANGING_SIGN();
    WARPED_HANGING_SIGN();
    MANGROVE_HANGING_SIGN();
    BAMBOO_HANGING_SIGN();
    OAK_WALL_HANGING_SIGN();
    SPRUCE_WALL_HANGING_SIGN();
    BIRCH_WALL_HANGING_SIGN();
    ACACIA_WALL_HANGING_SIGN();
    CHERRY_WALL_HANGING_SIGN();
    JUNGLE_WALL_HANGING_SIGN();
    DARK_OAK_WALL_HANGING_SIGN();
    PALE_OAK_WALL_HANGING_SIGN();
    MANGROVE_WALL_HANGING_SIGN();
    CRIMSON_WALL_HANGING_SIGN();
    WARPED_WALL_HANGING_SIGN();
    BAMBOO_WALL_HANGING_SIGN();
    LEVER();
    STONE_PRESSURE_PLATE();
    IRON_DOOR();
    OAK_PRESSURE_PLATE();
    SPRUCE_PRESSURE_PLATE();
    BIRCH_PRESSURE_PLATE();
    JUNGLE_PRESSURE_PLATE();
    ACACIA_PRESSURE_PLATE();
    CHERRY_PRESSURE_PLATE();
    DARK_OAK_PRESSURE_PLATE();
    PALE_OAK_PRESSURE_PLATE();
    MANGROVE_PRESSURE_PLATE();
    BAMBOO_PRESSURE_PLATE();
    REDSTONE_ORE();
    DEEPSLATE_REDSTONE_ORE();
    REDSTONE_TORCH();
    REDSTONE_WALL_TORCH();
    STONE_BUTTON();
    SNOW();
    ICE();
    SNOW_BLOCK();
    CACTUS();
    CACTUS_FLOWER();
    CLAY();
    SUGAR_CANE();
    JUKEBOX();
    OAK_FENCE();
    NETHERRACK();
    SOUL_SAND();
    SOUL_SOIL();
    BASALT();
    POLISHED_BASALT();
    SOUL_TORCH();
    SOUL_WALL_TORCH();
    GLOWSTONE();
    NETHER_PORTAL();
    CARVED_PUMPKIN();
    JACK_O_LANTERN();
    CAKE();
    REPEATER();
    WHITE_STAINED_GLASS();
    ORANGE_STAINED_GLASS();
    MAGENTA_STAINED_GLASS();
    LIGHT_BLUE_STAINED_GLASS();
    YELLOW_STAINED_GLASS();
    LIME_STAINED_GLASS();
    PINK_STAINED_GLASS();
    GRAY_STAINED_GLASS();
    LIGHT_GRAY_STAINED_GLASS();
    CYAN_STAINED_GLASS();
    PURPLE_STAINED_GLASS();
    BLUE_STAINED_GLASS();
    BROWN_STAINED_GLASS();
    GREEN_STAINED_GLASS();
    RED_STAINED_GLASS();
    BLACK_STAINED_GLASS();
    OAK_TRAPDOOR();
    SPRUCE_TRAPDOOR();
    BIRCH_TRAPDOOR();
    JUNGLE_TRAPDOOR();
    ACACIA_TRAPDOOR();
    CHERRY_TRAPDOOR();
    DARK_OAK_TRAPDOOR();
    PALE_OAK_TRAPDOOR();
    MANGROVE_TRAPDOOR();
    BAMBOO_TRAPDOOR();
    STONE_BRICKS();
    MOSSY_STONE_BRICKS();
    CRACKED_STONE_BRICKS();
    CHISELED_STONE_BRICKS();
    PACKED_MUD();
    MUD_BRICKS();
    INFESTED_STONE();
    INFESTED_COBBLESTONE();
    INFESTED_STONE_BRICKS();
    INFESTED_MOSSY_STONE_BRICKS();
    INFESTED_CRACKED_STONE_BRICKS();
    INFESTED_CHISELED_STONE_BRICKS();
    BROWN_MUSHROOM_BLOCK();
    RED_MUSHROOM_BLOCK();
    MUSHROOM_STEM();
    IRON_BARS();
    CHAIN();
    GLASS_PANE();
    PUMPKIN();
    MELON();
    ATTACHED_PUMPKIN_STEM();
    ATTACHED_MELON_STEM();
    PUMPKIN_STEM();
    MELON_STEM();
    VINE();
    GLOW_LICHEN();
    RESIN_CLUMP();
    OAK_FENCE_GATE();
    BRICK_STAIRS();
    STONE_BRICK_STAIRS();
    MUD_BRICK_STAIRS();
    MYCELIUM();
    LILY_PAD();
    RESIN_BLOCK();
    RESIN_BRICKS();
    RESIN_BRICK_STAIRS();
    RESIN_BRICK_SLAB();
    RESIN_BRICK_WALL();
    CHISELED_RESIN_BRICKS();
    NETHER_BRICKS();
    NETHER_BRICK_FENCE();
    NETHER_BRICK_STAIRS();
    NETHER_WART();
    ENCHANTING_TABLE();
    BREWING_STAND();
    CAULDRON();
    WATER_CAULDRON();
    LAVA_CAULDRON();
    POWDER_SNOW_CAULDRON();
    END_PORTAL();
    END_PORTAL_FRAME();
    END_STONE();
    DRAGON_EGG();
    REDSTONE_LAMP();
    COCOA();
    SANDSTONE_STAIRS();
    EMERALD_ORE();
    DEEPSLATE_EMERALD_ORE();
    ENDER_CHEST();
    TRIPWIRE_HOOK();
    TRIPWIRE();
    EMERALD_BLOCK();
    SPRUCE_STAIRS();
    BIRCH_STAIRS();
    JUNGLE_STAIRS();
    COMMAND_BLOCK();
    BEACON();
    COBBLESTONE_WALL();
    MOSSY_COBBLESTONE_WALL();
    FLOWER_POT();
    POTTED_TORCHFLOWER();
    POTTED_OAK_SAPLING();
    POTTED_SPRUCE_SAPLING();
    POTTED_BIRCH_SAPLING();
    POTTED_JUNGLE_SAPLING();
    POTTED_ACACIA_SAPLING();
    POTTED_CHERRY_SAPLING();
    POTTED_DARK_OAK_SAPLING();
    POTTED_PALE_OAK_SAPLING();
    POTTED_MANGROVE_PROPAGULE();
    POTTED_FERN();
    POTTED_DANDELION();
    POTTED_POPPY();
    POTTED_BLUE_ORCHID();
    POTTED_ALLIUM();
    POTTED_AZURE_BLUET();
    POTTED_RED_TULIP();
    POTTED_ORANGE_TULIP();
    POTTED_WHITE_TULIP();
    POTTED_PINK_TULIP();
    POTTED_OXEYE_DAISY();
    POTTED_CORNFLOWER();
    POTTED_LILY_OF_THE_VALLEY();
    POTTED_WITHER_ROSE();
    POTTED_RED_MUSHROOM();
    POTTED_BROWN_MUSHROOM();
    POTTED_DEAD_BUSH();
    POTTED_CACTUS();
    CARROTS();
    POTATOES();
    OAK_BUTTON();
    SPRUCE_BUTTON();
    BIRCH_BUTTON();
    JUNGLE_BUTTON();
    ACACIA_BUTTON();
    CHERRY_BUTTON();
    DARK_OAK_BUTTON();
    PALE_OAK_BUTTON();
    MANGROVE_BUTTON();
    BAMBOO_BUTTON();
    SKELETON_SKULL();
    SKELETON_WALL_SKULL();
    WITHER_SKELETON_SKULL();
    WITHER_SKELETON_WALL_SKULL();
    ZOMBIE_HEAD();
    ZOMBIE_WALL_HEAD();
    PLAYER_HEAD();
    PLAYER_WALL_HEAD();
    CREEPER_HEAD();
    CREEPER_WALL_HEAD();
    DRAGON_HEAD();
    DRAGON_WALL_HEAD();
    PIGLIN_HEAD();
    PIGLIN_WALL_HEAD();
    ANVIL();
    CHIPPED_ANVIL();
    DAMAGED_ANVIL();
    TRAPPED_CHEST();
    LIGHT_WEIGHTED_PRESSURE_PLATE();
    HEAVY_WEIGHTED_PRESSURE_PLATE();
    COMPARATOR();
    DAYLIGHT_DETECTOR();
    REDSTONE_BLOCK();
    NETHER_QUARTZ_ORE();
    HOPPER();
    QUARTZ_BLOCK();
    CHISELED_QUARTZ_BLOCK();
    QUARTZ_PILLAR();
    QUARTZ_STAIRS();
    ACTIVATOR_RAIL();
    DROPPER();
    WHITE_TERRACOTTA();
    ORANGE_TERRACOTTA();
    MAGENTA_TERRACOTTA();
    LIGHT_BLUE_TERRACOTTA();
    YELLOW_TERRACOTTA();
    LIME_TERRACOTTA();
    PINK_TERRACOTTA();
    GRAY_TERRACOTTA();
    LIGHT_GRAY_TERRACOTTA();
    CYAN_TERRACOTTA();
    PURPLE_TERRACOTTA();
    BLUE_TERRACOTTA();
    BROWN_TERRACOTTA();
    GREEN_TERRACOTTA();
    RED_TERRACOTTA();
    BLACK_TERRACOTTA();
    WHITE_STAINED_GLASS_PANE();
    ORANGE_STAINED_GLASS_PANE();
    MAGENTA_STAINED_GLASS_PANE();
    LIGHT_BLUE_STAINED_GLASS_PANE();
    YELLOW_STAINED_GLASS_PANE();
    LIME_STAINED_GLASS_PANE();
    PINK_STAINED_GLASS_PANE();
    GRAY_STAINED_GLASS_PANE();
    LIGHT_GRAY_STAINED_GLASS_PANE();
    CYAN_STAINED_GLASS_PANE();
    PURPLE_STAINED_GLASS_PANE();
    BLUE_STAINED_GLASS_PANE();
    BROWN_STAINED_GLASS_PANE();
    GREEN_STAINED_GLASS_PANE();
    RED_STAINED_GLASS_PANE();
    BLACK_STAINED_GLASS_PANE();
    ACACIA_STAIRS();
    CHERRY_STAIRS();
    DARK_OAK_STAIRS();
    PALE_OAK_STAIRS();
    MANGROVE_STAIRS();
    BAMBOO_STAIRS();
    BAMBOO_MOSAIC_STAIRS();
    SLIME_BLOCK();
    BARRIER();
    LIGHT();
    IRON_TRAPDOOR();
    PRISMARINE();
    PRISMARINE_BRICKS();
    DARK_PRISMARINE();
    PRISMARINE_STAIRS();
    PRISMARINE_BRICK_STAIRS();
    DARK_PRISMARINE_STAIRS();
    PRISMARINE_SLAB();
    PRISMARINE_BRICK_SLAB();
    DARK_PRISMARINE_SLAB();
    SEA_LANTERN();
    HAY_BLOCK();
    WHITE_CARPET();
    ORANGE_CARPET();
    MAGENTA_CARPET();
    LIGHT_BLUE_CARPET();
    YELLOW_CARPET();
    LIME_CARPET();
    PINK_CARPET();
    GRAY_CARPET();
    LIGHT_GRAY_CARPET();
    CYAN_CARPET();
    PURPLE_CARPET();
    BLUE_CARPET();
    BROWN_CARPET();
    GREEN_CARPET();
    RED_CARPET();
    BLACK_CARPET();
    TERRACOTTA();
    COAL_BLOCK();
    PACKED_ICE();
    SUNFLOWER();
    LILAC();
    ROSE_BUSH();
    PEONY();
    TALL_GRASS();
    LARGE_FERN();
    WHITE_BANNER();
    ORANGE_BANNER();
    MAGENTA_BANNER();
    LIGHT_BLUE_BANNER();
    YELLOW_BANNER();
    LIME_BANNER();
    PINK_BANNER();
    GRAY_BANNER();
    LIGHT_GRAY_BANNER();
    CYAN_BANNER();
    PURPLE_BANNER();
    BLUE_BANNER();
    BROWN_BANNER();
    GREEN_BANNER();
    RED_BANNER();
    BLACK_BANNER();
    WHITE_WALL_BANNER();
    ORANGE_WALL_BANNER();
    MAGENTA_WALL_BANNER();
    LIGHT_BLUE_WALL_BANNER();
    YELLOW_WALL_BANNER();
    LIME_WALL_BANNER();
    PINK_WALL_BANNER();
    GRAY_WALL_BANNER();
    LIGHT_GRAY_WALL_BANNER();
    CYAN_WALL_BANNER();
    PURPLE_WALL_BANNER();
    BLUE_WALL_BANNER();
    BROWN_WALL_BANNER();
    GREEN_WALL_BANNER();
    RED_WALL_BANNER();
    BLACK_WALL_BANNER();
    RED_SANDSTONE();
    CHISELED_RED_SANDSTONE();
    CUT_RED_SANDSTONE();
    RED_SANDSTONE_STAIRS();
    OAK_SLAB();
    SPRUCE_SLAB();
    BIRCH_SLAB();
    JUNGLE_SLAB();
    ACACIA_SLAB();
    CHERRY_SLAB();
    DARK_OAK_SLAB();
    PALE_OAK_SLAB();
    MANGROVE_SLAB();
    BAMBOO_SLAB();
    BAMBOO_MOSAIC_SLAB();
    STONE_SLAB();
    SMOOTH_STONE_SLAB();
    SANDSTONE_SLAB();
    CUT_SANDSTONE_SLAB();
    PETRIFIED_OAK_SLAB();
    COBBLESTONE_SLAB();
    BRICK_SLAB();
    STONE_BRICK_SLAB();
    MUD_BRICK_SLAB();
    NETHER_BRICK_SLAB();
    QUARTZ_SLAB();
    RED_SANDSTONE_SLAB();
    CUT_RED_SANDSTONE_SLAB();
    PURPUR_SLAB();
    SMOOTH_STONE();
    SMOOTH_SANDSTONE();
    SMOOTH_QUARTZ();
    SMOOTH_RED_SANDSTONE();
    SPRUCE_FENCE_GATE();
    BIRCH_FENCE_GATE();
    JUNGLE_FENCE_GATE();
    ACACIA_FENCE_GATE();
    CHERRY_FENCE_GATE();
    DARK_OAK_FENCE_GATE();
    PALE_OAK_FENCE_GATE();
    MANGROVE_FENCE_GATE();
    BAMBOO_FENCE_GATE();
    SPRUCE_FENCE();
    BIRCH_FENCE();
    JUNGLE_FENCE();
    ACACIA_FENCE();
    CHERRY_FENCE();
    DARK_OAK_FENCE();
    PALE_OAK_FENCE();
    MANGROVE_FENCE();
    BAMBOO_FENCE();
    SPRUCE_DOOR();
    BIRCH_DOOR();
    JUNGLE_DOOR();
    ACACIA_DOOR();
    CHERRY_DOOR();
    DARK_OAK_DOOR();
    PALE_OAK_DOOR();
    MANGROVE_DOOR();
    BAMBOO_DOOR();
    END_ROD();
    CHORUS_PLANT();
    CHORUS_FLOWER();
    PURPUR_BLOCK();
    PURPUR_PILLAR();
    PURPUR_STAIRS();
    END_STONE_BRICKS();
    TORCHFLOWER_CROP();
    PITCHER_CROP();
    PITCHER_PLANT();
    BEETROOTS();
    DIRT_PATH();
    END_GATEWAY();
    REPEATING_COMMAND_BLOCK();
    CHAIN_COMMAND_BLOCK();
    FROSTED_ICE();
    MAGMA_BLOCK();
    NETHER_WART_BLOCK();
    RED_NETHER_BRICKS();
    BONE_BLOCK();
    STRUCTURE_VOID();
    OBSERVER();
    SHULKER_BOX();
    WHITE_SHULKER_BOX();
    ORANGE_SHULKER_BOX();
    MAGENTA_SHULKER_BOX();
    LIGHT_BLUE_SHULKER_BOX();
    YELLOW_SHULKER_BOX();
    LIME_SHULKER_BOX();
    PINK_SHULKER_BOX();
    GRAY_SHULKER_BOX();
    LIGHT_GRAY_SHULKER_BOX();
    CYAN_SHULKER_BOX();
    PURPLE_SHULKER_BOX();
    BLUE_SHULKER_BOX();
    BROWN_SHULKER_BOX();
    GREEN_SHULKER_BOX();
    RED_SHULKER_BOX();
    BLACK_SHULKER_BOX();
    WHITE_GLAZED_TERRACOTTA();
    ORANGE_GLAZED_TERRACOTTA();
    MAGENTA_GLAZED_TERRACOTTA();
    LIGHT_BLUE_GLAZED_TERRACOTTA();
    YELLOW_GLAZED_TERRACOTTA();
    LIME_GLAZED_TERRACOTTA();
    PINK_GLAZED_TERRACOTTA();
    GRAY_GLAZED_TERRACOTTA();
    LIGHT_GRAY_GLAZED_TERRACOTTA();
    CYAN_GLAZED_TERRACOTTA();
    PURPLE_GLAZED_TERRACOTTA();
    BLUE_GLAZED_TERRACOTTA();
    BROWN_GLAZED_TERRACOTTA();
    GREEN_GLAZED_TERRACOTTA();
    RED_GLAZED_TERRACOTTA();
    BLACK_GLAZED_TERRACOTTA();
    WHITE_CONCRETE();
    ORANGE_CONCRETE();
    MAGENTA_CONCRETE();
    LIGHT_BLUE_CONCRETE();
    YELLOW_CONCRETE();
    LIME_CONCRETE();
    PINK_CONCRETE();
    GRAY_CONCRETE();
    LIGHT_GRAY_CONCRETE();
    CYAN_CONCRETE();
    PURPLE_CONCRETE();
    BLUE_CONCRETE();
    BROWN_CONCRETE();
    GREEN_CONCRETE();
    RED_CONCRETE();
    BLACK_CONCRETE();
    WHITE_CONCRETE_POWDER();
    ORANGE_CONCRETE_POWDER();
    MAGENTA_CONCRETE_POWDER();
    LIGHT_BLUE_CONCRETE_POWDER();
    YELLOW_CONCRETE_POWDER();
    LIME_CONCRETE_POWDER();
    PINK_CONCRETE_POWDER();
    GRAY_CONCRETE_POWDER();
    LIGHT_GRAY_CONCRETE_POWDER();
    CYAN_CONCRETE_POWDER();
    PURPLE_CONCRETE_POWDER();
    BLUE_CONCRETE_POWDER();
    BROWN_CONCRETE_POWDER();
    GREEN_CONCRETE_POWDER();
    RED_CONCRETE_POWDER();
    BLACK_CONCRETE_POWDER();
    KELP();
    KELP_PLANT();
    DRIED_KELP_BLOCK();
    TURTLE_EGG();
    SNIFFER_EGG();
    DEAD_TUBE_CORAL_BLOCK();
    DEAD_BRAIN_CORAL_BLOCK();
    DEAD_BUBBLE_CORAL_BLOCK();
    DEAD_FIRE_CORAL_BLOCK();
    DEAD_HORN_CORAL_BLOCK();
    TUBE_CORAL_BLOCK();
    BRAIN_CORAL_BLOCK();
    BUBBLE_CORAL_BLOCK();
    FIRE_CORAL_BLOCK();
    HORN_CORAL_BLOCK();
    DEAD_TUBE_CORAL();
    DEAD_BRAIN_CORAL();
    DEAD_BUBBLE_CORAL();
    DEAD_FIRE_CORAL();
    DEAD_HORN_CORAL();
    TUBE_CORAL();
    BRAIN_CORAL();
    BUBBLE_CORAL();
    FIRE_CORAL();
    HORN_CORAL();
    DEAD_TUBE_CORAL_FAN();
    DEAD_BRAIN_CORAL_FAN();
    DEAD_BUBBLE_CORAL_FAN();
    DEAD_FIRE_CORAL_FAN();
    DEAD_HORN_CORAL_FAN();
    TUBE_CORAL_FAN();
    BRAIN_CORAL_FAN();
    BUBBLE_CORAL_FAN();
    FIRE_CORAL_FAN();
    HORN_CORAL_FAN();
    DEAD_TUBE_CORAL_WALL_FAN();
    DEAD_BRAIN_CORAL_WALL_FAN();
    DEAD_BUBBLE_CORAL_WALL_FAN();
    DEAD_FIRE_CORAL_WALL_FAN();
    DEAD_HORN_CORAL_WALL_FAN();
    TUBE_CORAL_WALL_FAN();
    BRAIN_CORAL_WALL_FAN();
    BUBBLE_CORAL_WALL_FAN();
    FIRE_CORAL_WALL_FAN();
    HORN_CORAL_WALL_FAN();
    SEA_PICKLE();
    BLUE_ICE();
    CONDUIT();
    BAMBOO_SAPLING();
    BAMBOO();
    POTTED_BAMBOO();
    VOID_AIR();
    CAVE_AIR();
    BUBBLE_COLUMN();
    POLISHED_GRANITE_STAIRS();
    SMOOTH_RED_SANDSTONE_STAIRS();
    MOSSY_STONE_BRICK_STAIRS();
    POLISHED_DIORITE_STAIRS();
    MOSSY_COBBLESTONE_STAIRS();
    END_STONE_BRICK_STAIRS();
    STONE_STAIRS();
    SMOOTH_SANDSTONE_STAIRS();
    SMOOTH_QUARTZ_STAIRS();
    GRANITE_STAIRS();
    ANDESITE_STAIRS();
    RED_NETHER_BRICK_STAIRS();
    POLISHED_ANDESITE_STAIRS();
    DIORITE_STAIRS();
    POLISHED_GRANITE_SLAB();
    SMOOTH_RED_SANDSTONE_SLAB();
    MOSSY_STONE_BRICK_SLAB();
    POLISHED_DIORITE_SLAB();
    MOSSY_COBBLESTONE_SLAB();
    END_STONE_BRICK_SLAB();
    SMOOTH_SANDSTONE_SLAB();
    SMOOTH_QUARTZ_SLAB();
    GRANITE_SLAB();
    ANDESITE_SLAB();
    RED_NETHER_BRICK_SLAB();
    POLISHED_ANDESITE_SLAB();
    DIORITE_SLAB();
    BRICK_WALL();
    PRISMARINE_WALL();
    RED_SANDSTONE_WALL();
    MOSSY_STONE_BRICK_WALL();
    GRANITE_WALL();
    STONE_BRICK_WALL();
    MUD_BRICK_WALL();
    NETHER_BRICK_WALL();
    ANDESITE_WALL();
    RED_NETHER_BRICK_WALL();
    SANDSTONE_WALL();
    END_STONE_BRICK_WALL();
    DIORITE_WALL();
    SCAFFOLDING();
    LOOM();
    BARREL();
    SMOKER();
    BLAST_FURNACE();
    CARTOGRAPHY_TABLE();
    FLETCHING_TABLE();
    GRINDSTONE();
    LECTERN();
    SMITHING_TABLE();
    STONECUTTER();
    BELL();
    LANTERN();
    SOUL_LANTERN();
    CAMPFIRE();
    SOUL_CAMPFIRE();
    SWEET_BERRY_BUSH();
    WARPED_STEM();
    STRIPPED_WARPED_STEM();
    WARPED_HYPHAE();
    STRIPPED_WARPED_HYPHAE();
    WARPED_NYLIUM();
    WARPED_FUNGUS();
    WARPED_WART_BLOCK();
    WARPED_ROOTS();
    NETHER_SPROUTS();
    CRIMSON_STEM();
    STRIPPED_CRIMSON_STEM();
    CRIMSON_HYPHAE();
    STRIPPED_CRIMSON_HYPHAE();
    CRIMSON_NYLIUM();
    CRIMSON_FUNGUS();
    SHROOMLIGHT();
    WEEPING_VINES();
    WEEPING_VINES_PLANT();
    TWISTING_VINES();
    TWISTING_VINES_PLANT();
    CRIMSON_ROOTS();
    CRIMSON_PLANKS();
    WARPED_PLANKS();
    CRIMSON_SLAB();
    WARPED_SLAB();
    CRIMSON_PRESSURE_PLATE();
    WARPED_PRESSURE_PLATE();
    CRIMSON_FENCE();
    WARPED_FENCE();
    CRIMSON_TRAPDOOR();
    WARPED_TRAPDOOR();
    CRIMSON_FENCE_GATE();
    WARPED_FENCE_GATE();
    CRIMSON_STAIRS();
    WARPED_STAIRS();
    CRIMSON_BUTTON();
    WARPED_BUTTON();
    CRIMSON_DOOR();
    WARPED_DOOR();
    CRIMSON_SIGN();
    WARPED_SIGN();
    CRIMSON_WALL_SIGN();
    WARPED_WALL_SIGN();
    STRUCTURE_BLOCK();
    JIGSAW();
    TEST_BLOCK();
    TEST_INSTANCE_BLOCK();
    COMPOSTER();
    TARGET();
    BEE_NEST();
    BEEHIVE();
    HONEY_BLOCK();
    HONEYCOMB_BLOCK();
    NETHERITE_BLOCK();
    ANCIENT_DEBRIS();
    CRYING_OBSIDIAN();
    RESPAWN_ANCHOR();
    POTTED_CRIMSON_FUNGUS();
    POTTED_WARPED_FUNGUS();
    POTTED_CRIMSON_ROOTS();
    POTTED_WARPED_ROOTS();
    LODESTONE();
    BLACKSTONE();
    BLACKSTONE_STAIRS();
    BLACKSTONE_WALL();
    BLACKSTONE_SLAB();
    POLISHED_BLACKSTONE();
    POLISHED_BLACKSTONE_BRICKS();
    CRACKED_POLISHED_BLACKSTONE_BRICKS();
    CHISELED_POLISHED_BLACKSTONE();
    POLISHED_BLACKSTONE_BRICK_SLAB();
    POLISHED_BLACKSTONE_BRICK_STAIRS();
    POLISHED_BLACKSTONE_BRICK_WALL();
    GILDED_BLACKSTONE();
    POLISHED_BLACKSTONE_STAIRS();
    POLISHED_BLACKSTONE_SLAB();
    POLISHED_BLACKSTONE_PRESSURE_PLATE();
    POLISHED_BLACKSTONE_BUTTON();
    POLISHED_BLACKSTONE_WALL();
    CHISELED_NETHER_BRICKS();
    CRACKED_NETHER_BRICKS();
    QUARTZ_BRICKS();
    CANDLE();
    WHITE_CANDLE();
    ORANGE_CANDLE();
    MAGENTA_CANDLE();
    LIGHT_BLUE_CANDLE();
    YELLOW_CANDLE();
    LIME_CANDLE();
    PINK_CANDLE();
    GRAY_CANDLE();
    LIGHT_GRAY_CANDLE();
    CYAN_CANDLE();
    PURPLE_CANDLE();
    BLUE_CANDLE();
    BROWN_CANDLE();
    GREEN_CANDLE();
    RED_CANDLE();
    BLACK_CANDLE();
    CANDLE_CAKE();
    WHITE_CANDLE_CAKE();
    ORANGE_CANDLE_CAKE();
    MAGENTA_CANDLE_CAKE();
    LIGHT_BLUE_CANDLE_CAKE();
    YELLOW_CANDLE_CAKE();
    LIME_CANDLE_CAKE();
    PINK_CANDLE_CAKE();
    GRAY_CANDLE_CAKE();
    LIGHT_GRAY_CANDLE_CAKE();
    CYAN_CANDLE_CAKE();
    PURPLE_CANDLE_CAKE();
    BLUE_CANDLE_CAKE();
    BROWN_CANDLE_CAKE();
    GREEN_CANDLE_CAKE();
    RED_CANDLE_CAKE();
    BLACK_CANDLE_CAKE();
    AMETHYST_BLOCK();
    BUDDING_AMETHYST();
    AMETHYST_CLUSTER();
    LARGE_AMETHYST_BUD();
    MEDIUM_AMETHYST_BUD();
    SMALL_AMETHYST_BUD();
    TUFF();
    TUFF_SLAB();
    TUFF_STAIRS();
    TUFF_WALL();
    POLISHED_TUFF();
    POLISHED_TUFF_SLAB();
    POLISHED_TUFF_STAIRS();
    POLISHED_TUFF_WALL();
    CHISELED_TUFF();
    TUFF_BRICKS();
    TUFF_BRICK_SLAB();
    TUFF_BRICK_STAIRS();
    TUFF_BRICK_WALL();
    CHISELED_TUFF_BRICKS();
    CALCITE();
    TINTED_GLASS();
    POWDER_SNOW();
    SCULK_SENSOR();
    CALIBRATED_SCULK_SENSOR();
    SCULK();
    SCULK_VEIN();
    SCULK_CATALYST();
    SCULK_SHRIEKER();
    COPPER_BLOCK();
    EXPOSED_COPPER();
    WEATHERED_COPPER();
    OXIDIZED_COPPER();
    COPPER_ORE();
    DEEPSLATE_COPPER_ORE();
    OXIDIZED_CUT_COPPER();
    WEATHERED_CUT_COPPER();
    EXPOSED_CUT_COPPER();
    CUT_COPPER();
    OXIDIZED_CHISELED_COPPER();
    WEATHERED_CHISELED_COPPER();
    EXPOSED_CHISELED_COPPER();
    CHISELED_COPPER();
    WAXED_OXIDIZED_CHISELED_COPPER();
    WAXED_WEATHERED_CHISELED_COPPER();
    WAXED_EXPOSED_CHISELED_COPPER();
    WAXED_CHISELED_COPPER();
    OXIDIZED_CUT_COPPER_STAIRS();
    WEATHERED_CUT_COPPER_STAIRS();
    EXPOSED_CUT_COPPER_STAIRS();
    CUT_COPPER_STAIRS();
    OXIDIZED_CUT_COPPER_SLAB();
    WEATHERED_CUT_COPPER_SLAB();
    EXPOSED_CUT_COPPER_SLAB();
    CUT_COPPER_SLAB();
    WAXED_COPPER_BLOCK();
    WAXED_WEATHERED_COPPER();
    WAXED_EXPOSED_COPPER();
    WAXED_OXIDIZED_COPPER();
    WAXED_OXIDIZED_CUT_COPPER();
    WAXED_WEATHERED_CUT_COPPER();
    WAXED_EXPOSED_CUT_COPPER();
    WAXED_CUT_COPPER();
    WAXED_OXIDIZED_CUT_COPPER_STAIRS();
    WAXED_WEATHERED_CUT_COPPER_STAIRS();
    WAXED_EXPOSED_CUT_COPPER_STAIRS();
    WAXED_CUT_COPPER_STAIRS();
    WAXED_OXIDIZED_CUT_COPPER_SLAB();
    WAXED_WEATHERED_CUT_COPPER_SLAB();
    WAXED_EXPOSED_CUT_COPPER_SLAB();
    WAXED_CUT_COPPER_SLAB();
    COPPER_DOOR();
    EXPOSED_COPPER_DOOR();
    OXIDIZED_COPPER_DOOR();
    WEATHERED_COPPER_DOOR();
    WAXED_COPPER_DOOR();
    WAXED_EXPOSED_COPPER_DOOR();
    WAXED_OXIDIZED_COPPER_DOOR();
    WAXED_WEATHERED_COPPER_DOOR();
    COPPER_TRAPDOOR();
    EXPOSED_COPPER_TRAPDOOR();
    OXIDIZED_COPPER_TRAPDOOR();
    WEATHERED_COPPER_TRAPDOOR();
    WAXED_COPPER_TRAPDOOR();
    WAXED_EXPOSED_COPPER_TRAPDOOR();
    WAXED_OXIDIZED_COPPER_TRAPDOOR();
    WAXED_WEATHERED_COPPER_TRAPDOOR();
    COPPER_GRATE();
    EXPOSED_COPPER_GRATE();
    WEATHERED_COPPER_GRATE();
    OXIDIZED_COPPER_GRATE();
    WAXED_COPPER_GRATE();
    WAXED_EXPOSED_COPPER_GRATE();
    WAXED_WEATHERED_COPPER_GRATE();
    WAXED_OXIDIZED_COPPER_GRATE();
    COPPER_BULB();
    EXPOSED_COPPER_BULB();
    WEATHERED_COPPER_BULB();
    OXIDIZED_COPPER_BULB();
    WAXED_COPPER_BULB();
    WAXED_EXPOSED_COPPER_BULB();
    WAXED_WEATHERED_COPPER_BULB();
    WAXED_OXIDIZED_COPPER_BULB();
    LIGHTNING_ROD();
    POINTED_DRIPSTONE();
    DRIPSTONE_BLOCK();
    CAVE_VINES();
    CAVE_VINES_PLANT();
    SPORE_BLOSSOM();
    AZALEA();
    FLOWERING_AZALEA();
    MOSS_CARPET();
    PINK_PETALS();
    WILDFLOWERS();
    LEAF_LITTER();
    MOSS_BLOCK();
    BIG_DRIPLEAF();
    BIG_DRIPLEAF_STEM();
    SMALL_DRIPLEAF();
    HANGING_ROOTS();
    ROOTED_DIRT();
    MUD();
    DEEPSLATE();
    COBBLED_DEEPSLATE();
    COBBLED_DEEPSLATE_STAIRS();
    COBBLED_DEEPSLATE_SLAB();
    COBBLED_DEEPSLATE_WALL();
    POLISHED_DEEPSLATE();
    POLISHED_DEEPSLATE_STAIRS();
    POLISHED_DEEPSLATE_SLAB();
    POLISHED_DEEPSLATE_WALL();
    DEEPSLATE_TILES();
    DEEPSLATE_TILE_STAIRS();
    DEEPSLATE_TILE_SLAB();
    DEEPSLATE_TILE_WALL();
    DEEPSLATE_BRICKS();
    DEEPSLATE_BRICK_STAIRS();
    DEEPSLATE_BRICK_SLAB();
    DEEPSLATE_BRICK_WALL();
    CHISELED_DEEPSLATE();
    CRACKED_DEEPSLATE_BRICKS();
    CRACKED_DEEPSLATE_TILES();
    INFESTED_DEEPSLATE();
    SMOOTH_BASALT();
    RAW_IRON_BLOCK();
    RAW_COPPER_BLOCK();
    RAW_GOLD_BLOCK();
    POTTED_AZALEA_BUSH();
    POTTED_FLOWERING_AZALEA_BUSH();
    OCHRE_FROGLIGHT();
    VERDANT_FROGLIGHT();
    PEARLESCENT_FROGLIGHT();
    FROGSPAWN();
    REINFORCED_DEEPSLATE();
    DECORATED_POT();
    CRAFTER();
    TRIAL_SPAWNER();
    VAULT();
    HEAVY_CORE();
    PALE_MOSS_BLOCK();
    PALE_MOSS_CARPET();
    PALE_HANGING_MOSS();
    OPEN_EYEBLOSSOM();
    CLOSED_EYEBLOSSOM();
    POTTED_OPEN_EYEBLOSSOM();
    POTTED_CLOSED_EYEBLOSSOM();
    FIREFLY_BUSH();
}

} // namespace stratos::block
