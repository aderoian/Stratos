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

#include "Server.h"

#include <filesystem>
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

using std::cout;
using std::cerr;
using std::endl;

std::shared_ptr<spdlog::logger> createLogger(bool debug);

int main(int argc, char *argv[]) {
    cout << "Starting Stratos server..." << endl;

    cout << "Configuring logger..." << endl;

    std::shared_ptr<spdlog::logger> logger;
    try {
        logger = createLogger(argc > 1 && std::string(argv[1]) == "--debug");
        spdlog::set_default_logger(logger);
    } catch (const std::exception &e) {
        cerr << "Failed to configure logger: " << e.what() << endl;
        return 1;
    }

    logger->info("Logger initialized.");

    stratos::server = std::make_unique<stratos::Server>(logger, stratos::Path("./"));
    stratos::server->start();

    return 0;
}

std::string generateLogFilePath() {
    const auto now  = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "logs/log_%Y-%m-%d_%H-%M-%S.log");
    return oss.str();
}

std::shared_ptr<spdlog::logger> createLogger(const bool debug = false) {
    std::filesystem::create_directories("logs");

    const std::string logFilePath = generateLogFilePath();
    constexpr size_t maxSize = 1024 * 1024 * 100; // 500 MB
    constexpr size_t maxFiles = 200000;

    const auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        logFilePath, maxSize, maxFiles, true);

#ifdef _WIN32
    auto consoleSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
    auto consoleSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif

    const std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%^%l%$] : - %v";
    fileSink->set_pattern(pattern);
    consoleSink->set_pattern(pattern);

    std::vector<spdlog::sink_ptr> sinks{consoleSink, fileSink};
    auto logger = std::make_shared<spdlog::logger>("logger", sinks.begin(), sinks.end());
    logger->set_level(debug ? spdlog::level::debug : spdlog::level::info);
    logger->flush_on(spdlog::level::info);

    spdlog::set_default_logger(logger);
    return logger;
}