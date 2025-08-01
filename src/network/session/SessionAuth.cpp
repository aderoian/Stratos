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

#include "SessionAuth.h"

#include "cpr/session.h"
#include "network/protocol/definition/PacketLogin.h"
#include "NetworkClient.h"
#include "nlohmann/json.hpp"
#include "spdlog/logger.h"
#include "utils/UUID.h"
using json = nlohmann::json;

#include <iomanip>
#include <openssl/sha.h>

namespace stratos::network {
void authenticate(NetworkConnection* connection, const std::string& serverId, const std::vector<uint8_t>& secret, const EVPKeyPtr& pubKey) {
    const std::string loginHash = generateMinecraftSha1HexDigest(serverId, secret, pubKey);

    const auto session = std::make_shared<cpr::Session>();
    session->SetUrl(getAuthenticationUrl(connection->getSessionInfo()->get().username, loginHash, ""));//connection->getNetwork()->getAddress()));
    session->SetHeader({{"User-Agent", "Stratos/1.0"}});
    session->SetHeader({{"Content-Type", "application/json"}});
    session->SetTimeout(std::chrono::seconds(10));

    std::thread([s = session, conn = connection] {
        cpr::Response r = s->Get();

        if (conn && !conn->isDisconnected()) {
            if (r.status_code == 200) {
                auto body = json::parse(r.text);
                UUID id = UUIDFromString(body["id"]);
                std::string name = body["name"];

                conn->updateSessionInfo({name, id});
                conn->getLogger()->info("Successfully authenticated user {} with UUID {}", conn->getSessionInfo()->get().username, UUIDToString(id));
                std::vector<LoginProperty> properties = {{body["properties"][0]["name"], body["properties"][0]["value"], body["properties"][0]["signature"]}};
                conn->sendPacket(new LoginSuccess(id, std::move(name), std::move(properties)));
            } else {
                conn->getLogger()->error("Failed to authenticate user {}: HTTP {} - {}", conn->getSessionInfo()->get().username, r.status_code, r.error.message);
                conn->disconnect("Authentication failed");
            }
        }
    }).detach();
}
cpr::Url getAuthenticationUrl(const std::string& username, const std::string& loginHash, const std::string& serverIp) {
    return {"https://sessionserver.mojang.com/session/minecraft/hasJoined?username=" + username + "&serverId=" + loginHash + "&ip=" + serverIp};
}
std::string generateMinecraftSha1HexDigest(const std::string& serverId, const std::vector<uint8_t>& secret, const EVPKeyPtr& pubKey) {
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, serverId.data(), serverId.size());
    SHA1_Update(&ctx, secret.data(), secret.size());
    const std::vector<uint8_t> pubKeyDER = encodeServerPublicKey(&pubKey);
    SHA1_Update(&ctx, pubKeyDER.data(), pubKeyDER.size());

    uint8_t hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &ctx);

    bool isNegative = (hash[0] & 0x80) != 0;
    std::vector num(hash, hash + SHA_DIGEST_LENGTH);

    if (isNegative) {
        for (auto& b : num) b = ~b;
        for (int i = SHA_DIGEST_LENGTH - 1; i >= 0; --i) {
            if (++num[i] != 0) break;
        }
    }

    std::ostringstream oss;
    if (isNegative) oss << "-";

    bool leading = true;
    for (uint8_t byte : num) {
        if (leading && byte == 0) continue;
        leading = false;
        oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(byte);
    }

    if (oss.str().empty() || oss.str() == "-")
        oss << "0";

    return oss.str();
}
} // namespace stratos::network