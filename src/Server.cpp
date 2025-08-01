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

#include "block/Blocks.h"
#include "block/state/BlockState.h"
#include "network/Network.h"
#include "utils/config/Config.h"
#include "utils/MathUtils.h"
#include "utils/TimeUtils.h"
#include "world/biome/Biomes.h"
#include "world/format/io/Region.h"

#define DEFAULT_SERVER_PROPERTIES R"(# Basic server settings
server-name=
motd=A Minecraft Server
max-players=20
online-mode=true
pvp=true
difficulty=1
gamemode=0
hardcore=false
allow-nether=true
enable-command-block=false
spawn-npcs=true
spawn-animals=true
spawn-monsters=true
generate-structures=true

# Networking
server-port=25565
server-ip=
enable-query=false
enable-rcon=false

# World settings
level-name=world
level-seed=
level-type=default
view-distance=10
simulation-distance=10
max-build-height=256

# Performance tuning
max-tick-time=60000
tick-distance=10

# Logging
debug=false)"

namespace stratos {

std::unique_ptr<Server> server = nullptr;

Server::Server(const std::shared_ptr<spdlog::logger>& logger, Path path) : logger(logger), root(std::move(path)) {
    // Static initialization
    // TODO: Is there a better way to handle this?
    block::Blocks::registerBlocks();
    world::Biomes::registerBiomes();

    averageTPS.fill(20.0f);
    averageUse.fill(1.0f);

    try {
        serverConfig = std::make_unique<PropertiesConfig>(root / "server.properties", DEFAULT_SERVER_PROPERTIES);
        logger->info("Loaded server.properties");
    } catch (const std::exception& e) {
        logger->error("Failed to load server configuration: {}", e.what());
        throw;
    }

    try {
        const std::optional<PropertiesConfig::Property> ip = serverConfig->getProperty("server-ip");
        address = ip && !ip->value.empty() ? std::move(ip->asString()) : "0.0.0.0";
        port = serverConfig->getProperty("server-port").value().get().asInt();
        name = serverConfig->getProperty("server-name").value().get().asString();
        motd = serverConfig->getProperty("motd").value().get().asString();
        onlineMode = serverConfig->getProperty("online-mode").value().get().asBool();
        maxPlayers = serverConfig->getProperty("max-players").value().get().asInt();
    } catch (const std::bad_optional_access& e) {
        throw std::runtime_error("Missing required properties in 'server.properties'");
    }

    try {
        logger->info("Starting network...");
        network = new network::NetworkManager(this, logger, address, port);
    } catch (const std::exception& e) {
        logger->error("Failed to create NetworkManager: {}", e.what());
        throw;
    }

    Path          worldRegion = root / "world" / "region";
    world::Region region(0, 0, worldRegion);

    world::Chunk* chunk = region.loadChunk(0, 0);

}

Server::~Server() {}

std::shared_ptr<spdlog::logger> Server::getLogger() const {
    return logger;
}

bool Server::isRunning() const {
    return running.load();
}
const network::NetworkManager* Server::getNetwork() const {
    return network;
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
const Path& Server::getServerDirectory() const { return root; }
const std::unique_ptr<PropertiesConfig>& Server::getServerProperties() const { return serverConfig; }
std::string Server::getAddress() const { return address; }
int Server::getPort() const { return port; }
std::string Server::getName() const { return name; }
std::string Server::getMotd() const { return motd; }
bool Server::isOnlineMode() const { return onlineMode; }
int Server::getMaxPlayers() const { return maxPlayers; }
int Server::getOnlinePlayers() const { return onlinePlayers; }
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