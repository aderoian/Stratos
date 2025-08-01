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

#ifndef PACKETLOGINHANDLER_H
#define PACKETLOGINHANDLER_H
#include "network/protocol/Packet.h"

namespace stratos::network {
class NetworkConnection;
class LoginCookieResponse;
class LoginAcknowledge;
class LoginPluginResponse;
class EncryptionResponse;
class LoginStart;
class PacketLoginHandler final : public PacketHandler {
public:
    using PacketHandler::handle;
    explicit PacketLoginHandler(NetworkConnection* connection) : connection(connection) {}
    bool handle(const LoginStart* packet) override;
    bool handle(const EncryptionResponse* packet) override;
    bool handle(const LoginPluginResponse* packet) override;
    bool handle(const LoginAcknowledge* packet) override;
    bool handle(const LoginCookieResponse* packet) override;
protected:
    NetworkConnection* connection;
};
} // namespace stratos::network

#endif //PACKETLOGINHANDLER_H
