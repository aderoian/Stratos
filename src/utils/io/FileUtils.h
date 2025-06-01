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
#include <exception>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace stratos {

class Path {
  public:
    explicit Path(const char* path) : path(fs::path(path)) {}
    explicit Path(const std::string& path) : path(fs::path(path)) {}
    explicit Path(const fs::path& path) : path(path) {}
    Path(const Path&) = default;
    Path(Path&&)      = default;

    [[nodiscard]] std::string toString() const { return path.string(); }
    [[nodiscard]] bool        isAbsolute() const { return path.is_absolute(); }
    [[nodiscard]] bool        isRelative() const { return path.is_relative(); }
    [[nodiscard]] bool        exists() const { return fs::exists(path); }
    [[nodiscard]] bool        isDirectory() const { return fs::is_directory(path); }
    [[nodiscard]] bool        isSymlink() const { return fs::is_symlink(path); }
    [[nodiscard]] bool        isFile() const { return fs::is_regular_file(path); }
    [[nodiscard]] std::string getFileName() const { return path.filename().string(); }
    [[nodiscard]] std::string getFileNameWithoutExtension() const { return path.stem().string(); }
    [[nodiscard]] std::string getFileNameWithExtension() const { return path.filename().string(); }
    [[nodiscard]] std::string getFileExtension() const { return path.extension().string(); }
    [[nodiscard]] std::string getParentDirectory() const { return path.has_parent_path() ? path.parent_path().string() : std::string(); }
    [[nodiscard]] fs::path    getNativePath() const { return path; }
    [[nodiscard]] fs::path    getRelativePath(const Path& base) const { return fs::relative(path, base.path); }
    [[nodiscard]] fs::path    getAbsolutePath() const { return fs::absolute(path); }
    [[nodiscard]] Path        resolve(const std::string& path) const { return Path(fs::absolute(this->path / path)); }
    [[nodiscard]] bool        mkdir() const { return fs::create_directory(path); }
    [[nodiscard]] bool        mkdirs() const { return fs::create_directories(path); }
    [[nodiscard]] bool        rmdir() const { return fs::remove_all(path); }
    [[nodiscard]] bool        rmdirs() const { return fs::remove_all(path); }
    [[nodiscard]] bool        remove() const { return isFile() && fs::remove(path); }

  private:
    fs::path path;
};

inline std::fstream open(const Path& path, const std::ios::openmode mode) {
    std::fstream file(path.getNativePath(), mode);
    if (!file.is_open()) {
        throw fs::filesystem_error("Failed to open file: " + path.toString(), std::error_code());
    }
    return file;
}
inline std::fstream open(const std::string& path, const std::ios::openmode mode) {
    return open(Path(path), mode);
}
inline std::fstream open(const char* path, const std::ios::openmode mode) {
    return open(Path(path), mode);
}
inline void close(std::fstream& file) { if (file.is_open()) file.close(); }

} // namespace stratos

#endif //FILEUTILS_H
