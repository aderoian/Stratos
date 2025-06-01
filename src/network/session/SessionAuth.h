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

#ifndef SESSIONAUTH_H
#define SESSIONAUTH_H
#include "cpr/cprtypes.h"
#include "utils/crypto/CryptoUtils.h"

#include <string>
#include <vector>

namespace stratos {
class NetworkConnection;

void authenticate(NetworkConnection* connection, const std::string& serverId, const std::vector<uint8_t>& secret, const EVPKeyPtr& pubKey);
cpr::Url getAuthenticationUrl(const std::string& username, const std::string& loginHash, const std::string& serverIp);
std::string generateMinecraftSha1HexDigest(const std::string& serverId, const std::vector<uint8_t>& secret, const EVPKeyPtr& pubKey);
}// namespace stratos

#endif //SESSIONAUTH_H
