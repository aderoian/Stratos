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

#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
#include <vector>

namespace stratos {

std::string trim(const std::string& str);
std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);
std::string replaceFirst(const std::string& str, const std::string& from, const std::string& to);
std::string join(const std::string& delimiter, const std::vector<std::string>& elements);
std::vector<std::string> split(const std::string& str, const std::string& delimiter);
std::vector<std::string> split(const std::string& str, char delimiter);
} // stratos

#endif //STRINGUTILS_H
