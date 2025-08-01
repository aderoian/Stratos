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

#ifndef PACKETPLAYHANDLER_H
#define PACKETPLAYHANDLER_H
#include "network/protocol/Packet.h"
namespace stratos {
class NetworkSession;
}
namespace stratos::network {
class PacketPlayHandler final : public PacketHandler {
public:
    explicit PacketPlayHandler(NetworkSession* session) : PacketHandler(), session(session) {}

    bool handle(const ConfigurationClientInformation* packet) override { return false; }
    bool handle(const ConfigurationCookieResponse* packet) override { return false; }
    bool handle(const ConfigurationServerPluginMessage* packet) override { return false; }
    bool handle(const AcknowledgeFinishConfiguration* packet) override { return false; }
    bool handle(const ConfigurationServerboundKeepAlive* packet) override { return false; }
    bool handle(const ConfigurationPong* packet) override { return false; }
    bool handle(const ConfigurationResourcePackResponse* packet) override { return false; }
    bool handle(const ServerboundKnownPacks* packet) override { return false; }
    bool handle(const ClientHandshake* packet) override { return false; }
    bool handle(const LegacyServerListPing* packet) override { return false; }
    bool handle(const LoginStart* packet) override { return false; }
    bool handle(const EncryptionResponse* packet) override { return false; }
    bool handle(const LoginPluginResponse* packet) override { return false; }
    bool handle(const LoginAcknowledge* packet) override { return false; }
    bool handle(const LoginCookieResponse* packet) override { return false; }
    bool handle(const StatusRequest* packet) override { return false; }
    bool handle(const PingRequest* packet) override { return false; }
private:
    NetworkSession* session;
};
} // namespace stratos::network
#endif //PACKETPLAYHANDLER_H
