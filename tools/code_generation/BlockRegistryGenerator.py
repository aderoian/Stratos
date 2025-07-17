#
#                _____  _                 _
#               /  ___|| |               | |
#               \ `--. | |_  _ __   __ _ | |_   ___   ___
#                `--. \| __|| '__| / _` || __| / _ \ / __|
#               /\__/ /| |_ | |   | (_| || |_ | (_) |\__ \
#               \____/  \__||_|    \__,_| \__| \___/ |___/
#
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  Copyright (C) 2025 Armen Deroian
#

import argparse

parser = argparse.ArgumentParser(description='Generate a block registry for the specified blocks.')
parser.add_argument("--output-header", type=str, required=True, help="Output header file for the block registry.")
parser.add_argument("--output-source", type=str, required=True, help="Output source file for the block registry.")
parser.add_argument("--blocks", type=str, required=True, help="Dump of blocks to be included in the registry.")
parser.add_argument("--block-states", type=str, required=True, help="Dump of block states to be included in the registry.")
args = parser.parse_args()

def get_corrected_blockstate_codename(block, block_state_name):
    if block_state_name == "axis":
        if block == "nether_portal":
            return "HORIZONTAL_AXIS"
        else:
            return "AXIS"
    elif block_state_name == "facing":
        if block in ["amethyst_cluster", "large_amethyst_bud", "medium_amethyst_bud", "small_amethyst_bud", "barrel", "end_rod", "lightning_rod", "observer", "piston", "sticky_piston", "moving_piston", "piston_head", "dispenser", "command_block", "dropper"] or "_shulker_box" in block:
            return "FACING_ANY"
        elif block == "hopper":
            return "FACING_HOPPER"
        else:
            return "FACING_HORIZONTAL"

    if block_state_name in ["east", "north", "south", "west", "up", "down"]:
        if block_state_name == "up" or block_state_name == "down":
            return "DIRECTION_" + block_state_name.upper()
        else:
            if block == "redstone_wire":
                return block_state_name.upper() + "_WIRE_CONNECTION"
            elif block.endswith("_wall"):
                return block_state_name.upper() + "_WALL_SHAPE"
            else:
                return "DIRECTION_" + block_state_name.upper()


    if block in ["mangrove_propagule", "pitcher_crop"] and block_state_name == "age":
        return "AGE_4"
    elif block in ["water", "lava", "light"] and block_state_name == "level":
        return "LEVEL_15"
    elif "_leaves" in block and block_state_name == "distance":
        return "DISTANCE_1_7"
    elif "_bed" in block and block_state_name == "part":
        return "BED_PART"
    elif "rail" in block and block_state_name == "shape":
        return "RAIL_SHAPE"
    elif block in ["tall_seagrass", "sunflower", "lilac", "rose_bush", "peony", "tall_grass", "large_fern", "pitcher_crop", "pitcher_plant", "small_dripleaf"] and block_state_name == "half":
        return "DOUBLE_BLOCK_HALF"
    elif (block == "piston_head" or block == "moving_piston") and block_state_name == "type":
        return "PISTON_TYPE"
    elif block in ["fire", "cactus", "sugar_cane"] and block_state_name == "age":
        return "AGE_15"
    elif "_stairs" in block:
        if block_state_name == "half":
            return "BLOCK_HALF"
        elif block_state_name == "shape":
            return "STAIR_SHAPE"
        else:
            return block_state_name.upper()
    elif (block == "chest" or block == "trapped_chest") and block_state_name == "type":
        return "CHEST_TYPE"
    elif block in ["wheat", "pumpkin_stem", "melon_stem", "carrots", "potatoes", "beetroots", "torchflower_crop"] and block_state_name == "age":
        return "AGE_7"
    elif "_door" in block:
        if block_state_name == "half":
            return "DOUBLE_BLOCK_HALF"
        elif block_state_name == "hinge":
            return "DOOR_HINGE"
        elif block_state_name == "facing":
            return "FACING_HORIZONTAL"
        else:
            return block_state_name.upper()
    elif block == "lever" and block_state_name == "face":
        return "BLOCK_FACE"
    elif "_button" in block and block_state_name == "face":
        return "BLOCK_FACE"
    elif "_trapdoor" in block and block_state_name == "half":
        return "BLOCK_HALF"
    elif "_slab" in block and block_state_name == "type":
        return "SLAB_TYPE"
    elif block in ["nether_wart", "frosted_ice", "sweet_berry_bush"] and block_state_name == "age":
        return "AGE_3"
    elif (block == "water_cauldron" or block == "powder_snow_cauldron") and block_state_name == "level":
        return "LEVEL_3"
    elif block == "cocoa" and block_state_name == "age":
        return "AGE_2"
    elif block == "comparator" and block_state_name == "mode":
        return "COMPARATOR_MODE"
    elif block == "chorus_flower" and block_state_name == "age":
        return "AGE_5"
    elif block in ["kelp", "weeping_vines", "twisting_vines", "cave_vines"] and block_state_name == "age":
        return "AGE_25"
    elif block == "bamboo":
        if block_state_name == "age":
            return "AGE_1"
        elif block_state_name == "leaves":
            return "BAMBOO_LEAVES"
        else:
            return block_state_name.upper()
    elif block == "scaffolding" and block_state_name == "distance":
        return "DISTANCE_0_7"
    elif block == "grindstone" and block_state_name == "face":
        return "BLOCK_FACE"
    elif block == "structure_block" and block_state_name == "mode":
        return "STRUCTURE_BLOCK_MODE"
    elif block == "test_block" and block_state_name == "mode":
        return "TEST_BLOCK_MODE"
    elif block == "composter" and block_state_name == "level":
        return "LEVEL_8"
    else:
        return block_state_name.upper()


def generate_block_registry(output_header, output_source, blocks_dump, block_states_dump):
    """
    Generates a block registry from the provided blocks dump.

    :param output_header: The file to write the block registry to.
    :param output_source: The source file to write the block registry implementation to.
    :param blocks_dump: A file containing the blocks dump.
    :param block_states_dump: A file containing the block states dump.
    """
    # Read the blocks from the provided dump
    blocks = []
    with open(blocks_dump, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                blocks.append(line)
    block_states = []
    with open(block_states_dump, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                block_states.append(line)

    # Open the output header file for writing
    with open(output_header, 'w') as f:
        # Write the header for the block registry
        f.write("""/*
 *
 *               _____  _                 _
 *              /  ___|| |               | |
 *              \\ `--. | |_  _ __   __ _ | |_   ___   ___
 *               `--. \\| __|| '__| / _` || __| / _ \\ / __|
 *              /\\__/ /| |_ | |   | (_| || |_ | (_) |\\__ \\
 *              \\____/  \\__||_|    \\__,_| \\__| \\___/ |___/
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

#ifndef BLOCKS_H
#define BLOCKS_H

#include "registry/Registries.h"

namespace stratos::block {
Block* registerBlock(const utils::Identifier& id, Block* block);

class Blocks {
public:
""")
        f.write("// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND\n\n")


        # Write the block registry entries
        for block in blocks:
            parts = block.split(':', 1)
            if len(parts) != 2:
                raise ValueError(f"Invalid block format: {block}. Expected format is 'namespace:block_name'.")
            namespace, block_name = parts[0].strip(), parts[1].strip()
            f.write(f"    static const Block* {block_name.upper()}();\n")
        f.write("\n};\n} // namespace stratos::block\n\n#endif // BLOCKS_H\n")

    # Open the output source file for writing
    with open(output_source, 'w') as f:
        # Write the source file header
        f.write("""/*
 *
 *               _____  _                 _
 *              /  ___|| |               | |
 *              \\ `--. | |_  _ __   __ _ | |_   ___   ___
 *               `--. \\| __|| '__| / _` || __| / _ \\ / __|
 *              /\\__/ /| |_ | |   | (_| || |_ | (_) |\\__ \\
 *              \\____/  \\__||_|    \\__,_| \\__| \\___/ |___/
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
#include "state/StateProperties.h"

#define REGISTER_BLOCK(codeName, name) \
    const Block* Blocks::codeName() { \
        static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block()); \
        return block; \
    }
#define REGISTER_BLOCK_BLOCKSTATES(codeName, name, stateBuilder...) \
    const Block* Blocks::codeName() { \
        static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block(BlockStateManager::Builder().add(stateBuilder))); \
        return block; \
    }

namespace stratos::block {

Block* registerBlock(const utils::Identifier& id, Block* block) {
    registry::BLOCKS.registerEntry({{"minecraft", "block"}, id}, block);
    return block;
}

""")
        f.write("// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND\n\n")

        i = 0
        for block in blocks:
            no_state = False
            states = []
            state = block_states[i]
            print(f"Processing block state: {state} for block {block}")
            block_def = state[6:state.index('}')]
            if block != block_def:
                raise ValueError(f"Block definition mismatch: {block} does not match expected block state {block_def}.")
            if '[' not in state:
                no_state = True
            else:
                states = state[state.index('[') + 1:state.index(']')].split(',')

            # Consume all states for the current block
            state_def = block_def
            while state_def == block and i < len(block_states)-1:
                i += 1
                state_def = block_states[i][6:block_states[i].index('}')]

            if no_state:
                parts = block.split(':', 1)
                if len(parts) != 2:
                    raise ValueError(f"Invalid block format: {block}. Expected format is 'namespace:block_name'.")
                namespace, block_name = parts[0].strip(), parts[1].strip()
                f.write(f"    REGISTER_BLOCK({block_name.upper()}, \"{block_name}\")\n")
            else:
                parts = block_def.split(':', 1)
                namespace, block_name = parts[0].strip(), parts[1].strip()
                state_names = (s[0:s.index('=')] for s in states)
                state_builder = ', '.join(f"StateProperties::{get_corrected_blockstate_codename(block_name, s)}()" for s in state_names)
                if len(parts) != 2:
                    raise ValueError(f"Invalid block format: {block_def}. Expected format is 'namespace:block_name'.")
                f.write(f"    REGISTER_BLOCK_BLOCKSTATES({block_name.upper()}, \"{block_name}\", {state_builder})\n")
        f.write("} // namespace stratos::block\n")

generate_block_registry(args.output_header, args.output_source, args.blocks, args.block_states)

# Example usage:
# python BlockRegistryGenerator.py --output-header "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\block\Blocks.h" --output-source "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\block\Blocks.cpp" --blocks "D:\Development\Game Development\Minecraft\StratosMC\stratos-client\run\minecraft-block.txt --block-states "D:\Development\Game Development\Minecraft\StratosMC\stratos-client\run\block_states.txt"