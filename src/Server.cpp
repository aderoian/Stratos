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

#include "utils/MathUtils.h"
#include "utils/TimeUtils.h"

namespace stratos {

    std::unique_ptr<Server> server = nullptr;

    Server::Server(const std::shared_ptr<spdlog::logger>& logger) : logger(logger) {
        averageTPS.fill(20.0f);
        averageUse.fill(1.0f);

        // TODO: Load server settings from config file
    }

    std::shared_ptr<spdlog::logger> Server::getLogger() const {
        return logger;
    }

    bool Server::isRunning() const {
        return running.load();
    }

    unsigned int Server::getTick() const {
        return tickCounter;
    }

    float Server::getCurrentTPS() const {
        return currentTPS;
    }

    float Server::getCurrentLoad() const {
        return currentUse;
    }

    float Server::getAverageTPS() const {
        float total = 0.0f;
        for (const float tps : averageTPS) {
            total += tps;
        }

        return utils::round(total / averageTPS.size(), 2);
    }

    float Server::getAverageLoad() const {
        float total = 0.0f;
        for (const float use : averageUse) {
            total += use;
        }

        return utils::round((total / averageUse.size()) * 100.0f, 2);
    }

    void Server::start() {
        logger->info("Starting server...");
        running = true;

        startTime = utils::currentTimeMillis();

        tickProcessor();
    }

    void Server::shutdown() {
        logger->info("Shutting down server...");
        running = false;
    }

    void Server::tickProcessor() {
        nextTick = utils::currentTimeMillis();

        while (running) {
            tick();

            if (int sleepTime = std::max(0L, (nextTick - utils::currentTimeMillis())); sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }
    }

    void Server::tick() {
        const long tickTime = utils::currentTimeMillis();
        if ((tickTime - nextTick) < -25) {
            return;
        }

        ++tickCounter;

        // Tick server

        const long now = utils::currentTimeMillis();
        const long totalTickTime = now - tickTime;
        currentTPS = std::min(TARGET_TICKS_PER_SECOND, 1000.0f / std::max(1L, totalTickTime));
        currentUse = std::min(1.0f, totalTickTime / TARGET_MILLIS_PER_TICK);

        const int index = tickCounter % static_cast<int>(TARGET_TICKS_PER_SECOND);
        averageTPS[index] = currentTPS;
        averageUse[index] = currentUse;

        if ((nextTick - tickTime) < -1000) {
            nextTick = now;
        } else {
            nextTick += TARGET_MILLIS_PER_TICK;
        }
    }
} // stratos