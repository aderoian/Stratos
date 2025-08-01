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

#include "PacketLoginHandler.h"

#include "network/Network.h"
#include "network/protocol/definition/PacketLogin.h"
#include "network/session/NetworkClient.h"
#include "network/session/SessionAuth.h"
#include "Server.h"

namespace stratos::network {
bool PacketLoginHandler::handle(const LoginStart* packet) {
    if (connection->getNetwork()->useEncryption()) {
        connection->updateSessionInfo({packet->name, packet->uuid});
        connection->encryptionKey = &connection->getNetwork()->getEncryptionKey();
        std::vector<uint8_t> token = connection->verifyToken = generateRandomBytes(16);
        connection->sendPacket(new EncryptionRequest(server->getName(), encodeServerPublicKey(connection->encryptionKey), std::move(token), server->isOnlineMode()));
    } else {
        connection->updateSessionInfo({packet->name, generateOfflineUUID(packet->name)});
        connection->sendPacket(new LoginSuccess(packet->uuid, packet->name, std::vector<LoginProperty>()));
    }
    return true;
}
bool PacketLoginHandler::handle(const EncryptionResponse* packet) {
    if (const std::vector<uint8_t> decryptToken = rsaDecrypt(connection->encryptionKey, packet->verifyToken); decryptToken != connection->verifyToken) {
        connection->disconnect();
        return false;
    }
    connection->clientSecret = std::move(rsaDecrypt(connection->encryptionKey, packet->sharedSecret));
    connection->encryptionEnabled = false;

    if (server->isOnlineMode()) {
        authenticate(connection, server->getName(), connection->clientSecret, *connection->encryptionKey);
    } else {
        std::string username = connection->getSessionInfo()->get().username;
        connection->updateSessionInfo({username, generateOfflineUUID(username)});
        connection->sendPacket(new LoginSuccess(connection->getSessionInfo()->get().uuid, std::move(username), std::vector<LoginProperty>()));
    }
    return true;
}
bool PacketLoginHandler::handle(const LoginPluginResponse* packet) { return false; }
bool PacketLoginHandler::handle(const LoginAcknowledge* packet) {
    connection->createNetworkSession();
    connection->changeState(Configuration);
    return true;
}
bool PacketLoginHandler::handle(const LoginCookieResponse* packet) { return false; }
} // namespace stratos::network