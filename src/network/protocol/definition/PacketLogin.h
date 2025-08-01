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

#ifndef PACKETLOGIN_H
#define PACKETLOGIN_H
#include "network/protocol/Packet.h"
#include "utils/Identifier.h"
#include "utils/Types.h"
#include "utils/UUID.h"

#include <optional>
#include <vector>

namespace stratos::network {

class LoginStart final : public ServerboundPacket {//<LoginStart> {
public:
    constexpr static int ID = 0x00;
    std::string name; // String(16)
    UUID uuid;

    LoginStart() : ServerboundPacket(ID), uuid() {}
    SERVERBOUND_PACKET_FOOTER(LoginStart)
};

class EncryptionResponse final : public ServerboundPacket {//<EncryptionResponse> {
public:
    constexpr static int ID = 0x01;
    std::vector<uint8_t> sharedSecret; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray

    EncryptionResponse() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(EncryptionResponse)
};

class LoginPluginResponse final : public ServerboundPacket {//<LoginPluginResponse> {
public:
    constexpr static int ID = 0x02;
    int messageId; // VarInt
    std::optional<std::vector<uint8_t>> data; // prefixed optional ByteArray

    LoginPluginResponse() : ServerboundPacket(ID), messageId(0), data() {}
    SERVERBOUND_PACKET_FOOTER(LoginPluginResponse)
};

class LoginAcknowledge final : public ServerboundPacket {//<LoginAcknowledge> {
public:
    constexpr static int ID = 0x03;

    LoginAcknowledge() : ServerboundPacket(ID) {}
    SERVERBOUND_PACKET_FOOTER(LoginAcknowledge)
};

class LoginCookieResponse final : public ServerboundPacket {//<LoginCookieResponse> {
public:
    constexpr static int ID = 0x04;
    utils::Identifier cookie;
    std::optional<std::vector<uint8_t>> payload; // prefixed optional ByteArray

    LoginCookieResponse() : ServerboundPacket(ID), cookie({"",""}) {}
    SERVERBOUND_PACKET_FOOTER(LoginCookieResponse)
};

class LoginDisconnect final : public ClientboundPacket {//LoginDisconnect> {
public:
    constexpr static int ID = 0x00;
    std::string reason; // JSON Text Component

    LoginDisconnect() : ClientboundPacket(ID) {}
    explicit LoginDisconnect(std::string&& reason) : ClientboundPacket(ID), reason(std::move(reason)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginDisconnect)
};

class EncryptionRequest final : public ClientboundPacket {//EncryptionRequest> {
public:
    constexpr static int ID = 0x01;
    std::string serverId; // String(20)
    std::vector<uint8_t> publicKey; // prefixed ByteArray
    std::vector<uint8_t> verifyToken; // prefixed ByteArray
    bool shouldAuthenticate;

    EncryptionRequest() : ClientboundPacket(ID), shouldAuthenticate(false) {}
    EncryptionRequest(std::string&& serverId, std::vector<uint8_t>&& publicKey, std::vector<uint8_t>&& verifyToken, const bool shouldAuthenticate)
         : ClientboundPacket(ID), serverId(std::move(serverId)), publicKey(std::move(publicKey)), verifyToken(std::move(verifyToken)), shouldAuthenticate(shouldAuthenticate) {}
    CLIENTBOUND_PACKET_FOOTER(EncryptionRequest)
};

class LoginSuccess final : public ClientboundPacket {//LoginSuccess> {
public:
    constexpr static int ID = 0x02;
    UUID uuid;
    std::string username; // String(16)
    std::vector<LoginProperty> properties; // prefixed array(16)

    LoginSuccess() : ClientboundPacket(ID), uuid() {}
    LoginSuccess(const UUID& uuid, const std::string& username, const std::vector<LoginProperty>& properties)
         : ClientboundPacket(ID), uuid(uuid), username(username), properties(properties) {}
    CLIENTBOUND_PACKET_FOOTER(LoginSuccess)
};

class SetCompression final : public ClientboundPacket {//SetCompression> {
public:
    constexpr static int ID = 0x03;
    int threshold; // VarInt

    SetCompression() : ClientboundPacket(ID), threshold(0) {}
    explicit SetCompression(const int threshold) : ClientboundPacket(ID), threshold(threshold) {}
    CLIENTBOUND_PACKET_FOOTER(SetCompression)
};

class LoginPluginRequest final : public ClientboundPacket {//LoginPluginRequest> {
public:
    constexpr static int ID = 0x04;
    int messageId; // VarInt
    utils::Identifier channel;
    std::vector<uint8_t> data; // ByteArray

    LoginPluginRequest() : ClientboundPacket(ID), messageId(0), channel({"",""}) {}
    LoginPluginRequest(const int messageId, utils::Identifier channel, std::vector<uint8_t>&& data)
         : ClientboundPacket(ID), messageId(messageId), channel(std::move(channel)), data(std::move(data)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginPluginRequest)
};

class LoginCookieRequest final : public ClientboundPacket {//LoginCookieRequest> {
public:
    constexpr static int ID = 0x05;
    utils::Identifier cookie;

    LoginCookieRequest() : ClientboundPacket(ID), cookie({"",""}) {}
    explicit LoginCookieRequest(utils::Identifier  cookie) : ClientboundPacket(ID), cookie(std::move(cookie)) {}
    CLIENTBOUND_PACKET_FOOTER(LoginCookieRequest)
};

} // namespace stratos::network

#endif //PACKETLOGIN_H
