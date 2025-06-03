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

#include "FileUtils.h"

namespace stratos {
std::string Path::toString() const { return path.string(); }
bool        Path::isAbsolute() const { return path.is_absolute(); }
bool        Path::isRelative() const { return path.is_relative(); }
bool        Path::exists() const { return fs::exists(path); }
bool        Path::isDirectory() const { return fs::is_directory(path); }
bool        Path::isSymlink() const { return fs::is_symlink(path); }
bool        Path::isFile() const { return fs::is_regular_file(path); }
std::string Path::getFileName() const { return path.filename().string(); }
std::string Path::getFileNameWithoutExtension() const { return path.stem().string(); }
std::string Path::getFileNameWithExtension() const { return path.filename().string(); }
std::string Path::getFileExtension() const { return path.extension().string(); }
std::string Path::getParentDirectory() const { return path.has_parent_path() ? path.parent_path().string() : std::string(); }
fs::path    Path::getNativePath() const { return path; }
fs::path    Path::getRelativePath(const Path& base) const { return fs::relative(path, base.path); }
fs::path    Path::getAbsolutePath() const { return fs::absolute(path); }
Path        Path::resolve(const std::string& path) const { return Path(fs::absolute(this->path / path)); }
bool        Path::mkdir() const { return fs::create_directory(path); }
bool        Path::mkdirs() const { return fs::create_directories(path); }
bool        Path::rmdir() const { return fs::remove_all(path); }
bool        Path::rmdirs() const { return fs::remove_all(path); }
bool        Path::remove() const { return isFile() && fs::remove(path); }
Path Path::operator/(const Path& other) const { return Path(path / other.path); }
Path Path::operator/(const fs::path& other) const { return Path(path / other); }
Path Path::operator/(const std::string& other) const { return Path(path / other); }
Path Path::operator/(const char* other) const { return Path(path / other); }

std::fstream open(const Path& path, const std::ios::openmode mode) {
    std::fstream file(path.getNativePath(), mode);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path.toString());
    }
    return file;
}
std::fstream open(const std::string& path, const std::ios::openmode mode) {
    return open(Path(path), mode);
}
std::fstream open(const char* path, const std::ios::openmode mode) {
    return open(Path(path), mode);
}
void close(std::fstream& file) { if (file.is_open()) file.close(); }
}