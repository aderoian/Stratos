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

#ifndef SERVER_H_
#define SERVER_H_

#include "spdlog/spdlog.h"
#include "utils/io/FileUtils.h"

#include <array>
#include <atomic>

namespace stratos {
class PropertiesConfig;
class NetworkManager;

class Server final {

public:
    static constexpr float TARGET_TICKS_PER_SECOND = 20.0f;
    static constexpr float TARGET_SECONDS_PER_TICK = 1.0f / TARGET_TICKS_PER_SECOND;
    static constexpr float TARGET_MILLIS_PER_TICK = TARGET_SECONDS_PER_TICK * 1000.0f;

    Server(const std::shared_ptr<spdlog::logger>& logger, Path root);
    ~Server();

    [[nodiscard]] std::shared_ptr<spdlog::logger> getLogger() const;
    [[nodiscard]] bool isRunning() const;

    [[nodiscard]] unsigned int getTick() const;
    [[nodiscard]] float getCurrentTPS() const;
    [[nodiscard]] float getCurrentLoad() const;
    [[nodiscard]] float getAverageTPS() const;
    [[nodiscard]] float getAverageLoad() const;

    [[nodiscard]] const Path& getServerDirectory() const;
    [[nodiscard]] const std::unique_ptr<PropertiesConfig>& getServerProperties() const;
    [[nodiscard]] std::string getAddress() const;
    [[nodiscard]] int getPort() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getMotd() const;
    [[nodiscard]] bool isOnlineMode() const;

    [[nodiscard]] int getMaxPlayers() const;
    [[nodiscard]] int getOnlinePlayers() const;

    void start();
    void shutdown();
    void tickProcessor();
    long tick(const long& tickTime);

private:
    static std::unique_ptr<Server> _instance;
    std::shared_ptr<spdlog::logger> logger;

    Path root;
    std::unique_ptr<PropertiesConfig> serverConfig;

    std::unique_ptr<NetworkManager> network;

    std::atomic<bool> running = false;
    long startTime;

    // Server TPS
    unsigned int tickCounter;
    float currentTPS;
    float currentUse;
    std::array<float, 20> averageTPS;
    std::array<float, 20> averageUse;

    std::string                address;
    int port;
    std::string name;
    std::string motd;
    bool onlineMode;

    int maxPlayers;
    int onlinePlayers = 0;
};

extern std::unique_ptr<Server> server;
} // namespace stratos

#endif //SERVER_H_
