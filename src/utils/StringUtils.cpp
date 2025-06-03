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

#include "StringUtils.h"

namespace stratos {
std::string trim(const std::string& str) {
    const size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    const size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}
std::string toLower(const std::string& str) {
    std::string result;
    result.reserve(str.size());
    for (const char c : str)
        result += static_cast<char>(std::tolower(c));
    return result;
}
std::string toUpper(const std::string& str) {
    std::string result;
    result.reserve(str.size());
    for (const char c : str)
        result += static_cast<char>(std::toupper(c));
    return result;
}
std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
    std::string result = str;
    size_t        startPos = 0;
    while ((startPos = result.find(from, startPos)) != std::string::npos) {
        result.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return result;
}
std::string replaceFirst(const std::string& str, const std::string& from, const std::string& to) {
    std::string result = str;
    if (const size_t startPos = result.find(from); startPos != std::string::npos) {
        result.replace(startPos, from.length(), to);
    }
    return result;
}
std::string join(const std::string& delimiter, const std::vector<std::string>& elements) {
    if (elements.empty()) return "";
    std::string result;
    result.reserve(elements.size() * 10);
    for (size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (i < elements.size() - 1) result += delimiter;
    }
    return result;
}
std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t                   start = 0;
    size_t                   end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        result.emplace_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    result.emplace_back(str.substr(start));
    return result;
}
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t                   start = 0;
    size_t                   end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        result.emplace_back(str.substr(start, end - start));
        start = end + 1;
    }
    result.emplace_back(str.substr(start));
    return result;
}
} // stratos