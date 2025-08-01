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

#ifndef PACKETCONFIGURATIONHANDLER_H
#define PACKETCONFIGURATIONHANDLER_H
#include "network/protocol/Packet.h"

namespace stratos::network {
class NetworkSession;
class ServerboundKnownPacks;
class ConfigurationResourcePackResponse;
class ConfigurationPong;
class ConfigurationServerboundKeepAlive;
class AcknowledgeFinishConfiguration;
class ConfigurationServerPluginMessage;
class ConfigurationCookieResponse;
class ConfigurationClientInformation;
class PacketConfigurationHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit PacketConfigurationHandler(NetworkSession* session) : session(session) {}
    bool handle(const ConfigurationClientInformation* packet) override;
    bool handle(const ConfigurationCookieResponse* packet) override;
    bool handle(const ConfigurationServerPluginMessage* packet) override;
    bool handle(const AcknowledgeFinishConfiguration* packet) override;
    bool handle(const ConfigurationServerboundKeepAlive* packet) override;
    bool handle(const ConfigurationPong* packet) override;
    bool handle(const ConfigurationResourcePackResponse* packet) override;
    bool handle(const ServerboundKnownPacks* packet) override;
protected:
    NetworkSession* session;
};
} // namespace stratos::network

#endif //PACKETCONFIGURATIONHANDLER_H
