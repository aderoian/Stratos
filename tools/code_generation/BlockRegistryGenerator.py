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
args = parser.parse_args()

def generate_block_registry(output_header, output_source, blocks_dump):
    """
    Generates a block registry from the provided blocks dump.

    :param output_header: The file to write the block registry to.
    :param output_source: The source file to write the block registry implementation to.
    :param blocks_dump: A file containing the blocks dump.
    """
    # Read the blocks from the provided dump
    blocks = []
    with open(blocks_dump, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                blocks.append(line)

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

#define REGISTER_BLOCK(codeName, name) \
    const Block* Blocks::codeName() { \
        static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block()); \
        return block; \
    }
#define REGISTER_BLOCK(codeName, name, stateBuilder...) \
    const Block* Blocks::codeName() { \
        static const Block* block = registerBlock(utils::Identifier("minecraft", name), new Block(BlockStateManager::Builder()stateBuilder)); \
        return block; \
    }

namespace stratos::block {

Block* registerBlock(const utils::Identifier& id, Block* block) {
    registry::BLOCKS.registerEntry({{"minecraft", "block"}, id}, block);
    return block;
}

""")
        f.write("// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND\n\n")
        # Write the block registry implementations
        for block in blocks:
            parts = block.split(':', 1)
            if len(parts) != 2:
                raise ValueError(f"Invalid block format: {block}. Expected format is 'namespace:block_name'.")
            namespace, block_name = parts[0].strip(), parts[1].strip()
            f.write(f"    REGISTER_BLOCK({block_name.upper()}, \"{block_name}\")\n")
        f.write("} // namespace stratos::block\n")

generate_block_registry(args.output_header, args.output_source, args.blocks)

# Example usage:
# python BlockRegistryGenerator.py --output-header "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\block\Blocks.h" --output-source "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\block\Blocks.cpp" --blocks "D:\Development\Game Development\Minecraft\StratosMC\stratos-client\run\minecraft-block.txt"