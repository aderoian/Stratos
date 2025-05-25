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

#include "network/Network.h"
#include "utils/MathUtils.h"
#include "utils/TimeUtils.h"

namespace stratos {

std::unique_ptr<Server> server = nullptr;

Server::Server(const std::shared_ptr<spdlog::logger>& logger) : logger(logger) {
    averageTPS.fill(20.0f);
    averageUse.fill(1.0f);

    // TODO: Load server settings from config file
    address = "0.0.0.0";
    port    = 25566;

    try {
        logger->info("Starting network...");
        network = std::make_unique<NetworkManager>(this, logger, address, port);
    } catch (const std::exception& e) {
        logger->error("Failed to create NetworkManager: {}", e.what());
        throw;
    }
}

Server::~Server() {}

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

    try {
        network->start();
    } catch (std::exception& e) {
        logger->error("Error starting server: {}", e.what());
        // TODO: Crash? Force Shutdown?
        return;
    }

    tickProcessor();
}

void Server::shutdown() {
    logger->info("Shutting down server...");
    running = false;

    try {
        network->stop();
    } catch (std::exception& e) {
        logger->error("Error shutting down server: {}", e.what());
    }
}

void Server::tickProcessor() {
    do {
        // Tick the server, calculate the time taken,
        long tickTime = utils::currentTimeMillis();
        if (const long tickDur = tick(tickTime); tickDur < TARGET_MILLIS_PER_TICK) {
            // Sleep for the remaining time to maintain the target tick rate
            if (long sleepTime = TARGET_MILLIS_PER_TICK - tickDur; sleepTime > 0) {
                assert(sleepTime <= 50);
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }
    } while (running);
}

long Server::tick(const long& tickTime) {
    ++tickCounter;

    // Tick server
    network->tick();

    const long now           = utils::currentTimeMillis();
    const long totalTickTime = now - tickTime;
    currentTPS               = std::min(TARGET_TICKS_PER_SECOND, 1000.0f / std::max(1L, totalTickTime));
    currentUse               = std::min(1.0f, totalTickTime / TARGET_MILLIS_PER_TICK);

    const int index   = tickCounter % static_cast<int>(TARGET_TICKS_PER_SECOND);
    averageTPS[index] = currentTPS;
    averageUse[index] = currentUse;

    return now - tickTime;
}
} // namespace stratos