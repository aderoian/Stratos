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

#ifndef FILEUTILS_H
#define FILEUTILS_H
#include "ByteBuffer.h"

#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;

namespace stratos {
class Path {
public:
    explicit Path(const char* path) : path(fs::path(path)) {}
    explicit Path(const std::string& path) : path(fs::path(path)) {}
    explicit Path(fs::path  path) : path(std::move(path)) {}
    Path(const Path&) = default;
    Path(Path&&)      = default;

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] bool        isAbsolute() const;
    [[nodiscard]] bool        isRelative() const;
    [[nodiscard]] bool        exists() const;
    [[nodiscard]] bool        isDirectory() const;
    [[nodiscard]] bool        isSymlink() const;
    [[nodiscard]] bool        isFile() const;
    [[nodiscard]] std::string getFileName() const;
    [[nodiscard]] std::string getFileNameWithoutExtension() const;
    [[nodiscard]] std::string getFileNameWithExtension() const;
    [[nodiscard]] std::string getFileExtension() const;
    [[nodiscard]] std::string getParentDirectory() const;
    [[nodiscard]] fs::path    getNativePath() const;
    [[nodiscard]] fs::path    getRelativePath(const Path& base) const;
    [[nodiscard]] fs::path    getAbsolutePath() const;
    [[nodiscard]] Path        resolve(const std::string& path) const;
    [[nodiscard]] bool        mkdir() const;
    [[nodiscard]] bool        mkdirs() const;
    [[nodiscard]] bool        rmdir() const;
    [[nodiscard]] bool        rmdirs() const;
    [[nodiscard]] bool        remove() const;

    Path operator/(const Path& other) const;
    Path operator/(const fs::path& other) const;
    Path operator/(const std::string& other) const;
    Path operator/(const char* other) const;

private:
    fs::path path;
};

std::fstream open(const Path& path, std::ios::openmode mode);
std::fstream open(const std::string& path, std::ios::openmode mode);
std::fstream open(const char* path, std::ios::openmode mode);
void close(std::fstream& file);

ByteVec readAllBytes(const Path& path);
void writeAllBytes(const Path& path, const ByteVec& data);
}// namespace stratos

#endif //FILEUTILS_H
