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

#ifndef CONFIG_H
#define CONFIG_H
#include "utils/io/FileUtils.h"

#include <optional>
#include <unordered_map>
#include <vector>

namespace stratos {
class Config {
public:
    explicit Config(const Path& file);
    Config(const Path& file, const std::string& default_);
    virtual ~Config() = default;

    virtual void load() = 0;
    virtual void save() = 0;
    virtual void close();

    [[nodiscard]] const Path& getPath() const { return configPath; }
    [[nodiscard]] std::fstream& getFile() { return configFile; }
protected:
    Path configPath;
    std::fstream configFile;
    bool dirty = false;
};
class PropertiesConfig final : public Config {
public:
    class Property {
    public:
        std::string key;
        std::string value;

        Property() = default;
        Property(std::string k, std::string v) : key(std::move(k)), value(std::move(v)) {}
        [[nodiscard]] int asInt() const;
        [[nodiscard]] long asLong() const;
        [[nodiscard]] float asFloat() const;
        [[nodiscard]] double asDouble() const;
        [[nodiscard]] bool asBool() const;
        [[nodiscard]] std::string asString() const;
        bool operator==(const Property& other) const;
    };

    explicit PropertiesConfig(const Path& file) : Config(file) { load(); }
    PropertiesConfig(const Path& file, const std::string& default_) : Config(file, default_) { load(); }

    void load() override;
    void save() override;
    void close() override;

    [[nodiscard]] std::optional<std::reference_wrapper<const Property>> getProperty(const std::string& key) const;
    void removeProperty(const std::string& key);
    void writeProperty(const Property& property);
private:
    std::unordered_map<std::string, Property> properties;
    std::vector<std::string> propertiesKeys;
    static std::optional<Property> parseLine(const std::string& line, const int &lineNumber);
};
} // stratos

#endif //CONFIG_H
