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

#include "Config.h"

#include "utils/StringUtils.h"

#include <ranges>
#include <regex>

namespace fs = std::filesystem;

namespace stratos {
Config::Config(const Path& file) : configPath(file) {
    configFile = std::fstream(file.toString(), std::ios::in | std::ios::out);
    if (!configFile.is_open()) throw std::runtime_error("Failed to open config file: " + file.toString());
}
Config::Config(const Path& file, const std::string& default_) : configPath(file) {
    if (!file.exists() || !file.isFile()) {
        configFile = std::fstream(file.toString(), std::ios::in | std::ios::out | std::ios::trunc);
        configFile << default_;
        configFile.flush();
        configFile.seekg(0);
    } else {
        configFile = std::fstream(file.toString(), std::ios::in | std::ios::out);
    }
}
void Config::close() {
    save();
    if (configFile.is_open())
        configFile.close();
}
int PropertiesConfig::Property::asInt() const { return std::stoi(key); }
long PropertiesConfig::Property::asLong() const { return std::stol(key); }
float PropertiesConfig::Property::asFloat() const { return std::stof(key); }
double PropertiesConfig::Property::asDouble() const { return std::stod(key); }
bool PropertiesConfig::Property::asBool() const { return value == "true" || value == "1"; }
std::string PropertiesConfig::Property::asString() const { return value; }
bool PropertiesConfig::Property::operator==(const Property& other) const { return key == other.key && value == other.value; }
void PropertiesConfig::load() {
    int         lineNumber = 1;
    std::string line;
    while (std::getline(configFile, line)) {
        if (auto property = parseLine(line, lineNumber); property.has_value()) {
            propertiesKeys.push_back(property->key);
            properties[property->key] = std::move(*property);
        }
        lineNumber++;
    }
}
void PropertiesConfig::save() {
    if (dirty) {
        configFile.clear();
        configFile.seekp(0, std::ios::beg);
        for (const auto& property : propertiesKeys) {
            if (auto it = properties.find(property); it != properties.end())
                configFile << it->first << "=" << it->second.value << "\n";
        }
        dirty = configFile.tellp() < fs::file_size(configPath.getNativePath()); // If the current position is less than the file size, we have removed some content
    }
    configFile.flush();
}
void PropertiesConfig::close() {
    if (dirty && configFile.is_open()) {
        save();
        const std::streampos endPos = configFile.tellp();
        configFile.close();
        // Resize the file to the current position if we have removed some content
        if (dirty) fs::resize_file(configPath.getNativePath(), endPos);
    } else {
        if (configFile.is_open()) configFile.close();
    }
}
std::optional<std::reference_wrapper<const PropertiesConfig::Property>> PropertiesConfig::getProperty(const std::string& key) const {
    if (key.empty()) throw std::runtime_error("Cannot get property with empty key.");
    const auto it = properties.find(key);
    return it != properties.end() ? std::make_optional(std::cref(it->second)) : std::nullopt;
}
void PropertiesConfig::removeProperty(const std::string& key) {
    if (key.empty()) throw std::runtime_error("Cannot remove property with empty key.");
    if (const auto it = properties.find(key); it != properties.end()) {
        properties.erase(it);
        dirty = true;
        std::erase(propertiesKeys, it->first);
    } else {
        throw std::runtime_error("Property with key '" + key + "' does not exist.");
    }
}
void PropertiesConfig::writeProperty(const Property& property) {
    if (property.key.empty()) throw std::runtime_error("Cannot write property with empty key.");
    properties[property.key] = property;
    if (std::ranges::find(propertiesKeys, property.key) == propertiesKeys.end())
        propertiesKeys.push_back(property.key);
    dirty = true;
}
std::optional<PropertiesConfig::Property> PropertiesConfig::parseLine(const std::string& line, const int& lineNumber) {
    if (line.empty() || line[0] == '#' || line[0] == '!') return std::nullopt;
    const size_t pos = line.find('=');
    if (pos == std::string::npos) throw std::runtime_error("Properties Syntax Error: Missing '=' in line " + std::to_string(lineNumber) + ": " + line);

    const std::string key   = trim(line.substr(0, pos));
    const std::string value = trim(line.substr(pos + 1));
    if (key.empty()) throw std::runtime_error("Properties Syntax Error: Empty key in line " + std::to_string(lineNumber) + ": " + line);

    return Property{key, value};
}
} // namespace stratos