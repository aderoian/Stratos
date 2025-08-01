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

#include "PacketLogin.h"

#include "network/protocol/serialization/PacketBuffer.h"

namespace stratos::network {
void LoginStart::decrypt(const PacketBuffer& buffer) {
    name = buffer.readString(16);
    uuid = buffer.readUUID();
}
void EncryptionResponse::decrypt(const PacketBuffer& buffer) {
    sharedSecret = buffer.readByteArray(buffer.readVarInt());
    verifyToken  = buffer.readByteArray(buffer.readVarInt());
}
void LoginPluginResponse::decrypt(const PacketBuffer& buffer) {
    messageId = buffer.readVarInt();
    data      = buffer.readPrefixedOptionalInferredByteArray();
}
void LoginAcknowledge::decrypt(const PacketBuffer& buffer) {}
void LoginCookieResponse::decrypt(const PacketBuffer& buffer) {
    cookie = buffer.readIdentifier();
    payload = buffer.readPrefixedOptionalPrefixedByteArray();
}
void LoginDisconnect::encrypt(PacketBuffer& buffer) const {
    buffer.writeString(reason, 32767);
}
void EncryptionRequest::encrypt(PacketBuffer& buffer) const {
    buffer.writeString(serverId, 20);
    buffer.writePrefixedByteArray(publicKey);
    buffer.writePrefixedByteArray(verifyToken);
    buffer.writeBoolean(shouldAuthenticate);
}
void LoginSuccess::encrypt(PacketBuffer& buffer) const {
    buffer.writeUUID(uuid);
    buffer.writeString(username, 16);
    buffer.writeLoginProperty(properties);
}
void SetCompression::encrypt(PacketBuffer& buffer) const {
    buffer.writeVarInt(threshold);
}
void LoginPluginRequest::encrypt(PacketBuffer& buffer) const {
    buffer.writeVarInt(messageId);
    buffer.writeIdentifier(channel);
    buffer.writeByteArray(data);
}
void LoginCookieRequest::encrypt(PacketBuffer& buffer) const {
    buffer.writeIdentifier(cookie);
}
} // namespace stratos::network