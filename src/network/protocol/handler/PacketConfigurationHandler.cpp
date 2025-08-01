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

#include "PacketConfigurationHandler.h"

#include "network/protocol/definition/PacketConfiguration.h"
#include "network/session/NetworkClient.h"

namespace stratos::network {
bool PacketConfigurationHandler::handle(const ConfigurationClientInformation* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const ConfigurationCookieResponse* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const ConfigurationServerPluginMessage* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const AcknowledgeFinishConfiguration* packet) {
    session->changeState(Play);
    session->loginPlayer();
    return true;
}
bool PacketConfigurationHandler::handle(const ConfigurationServerboundKeepAlive* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const ConfigurationPong* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const ConfigurationResourcePackResponse* packet) {
    return false;
}
bool PacketConfigurationHandler::handle(const ServerboundKnownPacks* packet) {
    return false;
}
} // namespace stratos::network