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

parser = argparse.ArgumentParser(description='Generate a biome registry for the specified biomes.')
parser.add_argument("--output-header", type=str, required=True, help="Output header file for the biome registry.")
parser.add_argument("--output-source", type=str, required=True, help="Output source file for the biome registry.")
parser.add_argument("--biomes", type=str, required=True, help="Dump of biomes to be included in the registry.")
args = parser.parse_args()

def generate_biome_registry(output_header, output_source, biomes_dump):
    """
    Generates a biome registry from the provided biomes dump.

    :param output_header: The file to write the biome registry to.
    :param output_source: The source file to write the biome registry implementation to.
    :param biomes_dump: A file containing the biomes dump.
    """
    # Read the biomes from the provided dump
    biomes = []
    with open(biomes_dump, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                biomes.append(line)

    # Open the output header file for writing
    with open(output_header, 'w') as f:
        # Write the header for the biome registry
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

#ifndef BIOMES_H
#define BIOMES_H

namespace stratos::utils {
struct Identifier;
}
namespace stratos::world {
class Biome;
Biome* registerBiome(const utils::Identifier& id, Biome* biome);

class Biomes {
public:
    // AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

""")

        # Write the biome registry entries
        for biome in biomes:
            parts = biome.split(':', 1)
            if len(parts) != 2:
                raise ValueError(f"Invalid biome format: {biome}. Expected format is 'namespace:biome_name'.")
            namespace, biome_name = parts[0].strip(), parts[1].strip()
            f.write(f"    static const Biome* {biome_name.upper()}();\n")

        f.write("\n    static void registerBiomes();")
        f.write("\n};\n} // namespace stratos::world\n\n#endif // BIOMES_H\n")

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

#include "Biomes.h"

#include "Biome.h"
#include "registry/Registries.h"
#include "utils/Identifier.h"

#define REGISTER_BIOME(codeName, name) \\
    const Biome* Biomes::codeName() { \\
        static const Biome* biome = registerBiome(utils::Identifier("minecraft", name), new Biome()); \\
        return biome; \\
    }

namespace stratos::world {

Biome* registerBiome(const utils::Identifier& id, Biome* biome) {
    registry::Registries::BIOMES()->registerEntry({{"minecraft", "biome"}, id}, biome);
    return biome;
}

// AUTOMATICALLY GENERATED -- DO NOT EDIT BY HAND

""")
        i = 0
        for biome in biomes:
            parts = biome.split(':', 1)
            if len(parts) != 2:
                raise ValueError(f"Invalid biome format: {biome}. Expected format is 'namespace:biome_name'.")
            namespace, biome_name = parts[0].strip(), parts[1].strip()
            f.write(f"REGISTER_BIOME({biome_name.upper()}, \"{biome_name}\")\n")
        f.write("\nvoid Biomes::registerBiomes() {\n")
        for biome in biomes:
            parts = biome.split(':', 1)
            namespace, name = parts[0].strip(), parts[1].strip()
            f.write(f"    {name.upper()}();\n")

        f.write("}\n\n")
        f.write("} // namespace stratos::world\n")

generate_biome_registry(args.output_header, args.output_source, args.biomes)

# Example usage:
# python BiomeRegistryGenerator.py --output-header "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\world\biome\Biomes.h" --output-source "D:\Development\Game Development\Minecraft\StratosMC\Stratos\src\world\biome\Biomes.cpp" --biomes "D:\Development\Game Development\Minecraft\StratosMC\stratos-client\run\minecraft-worldgen\biome.txt"