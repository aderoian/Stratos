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

#ifndef PACKET_H
#define PACKET_H

namespace stratos {
class NetworkSession;
class PacketBuffer;

class Packet {
public:
    explicit Packet(const int id) : id(id) {}
    virtual ~Packet();

    int getId() const { return id; }
    virtual void decrypt(PacketBuffer& buffer) = 0;
    virtual void encrypt(PacketBuffer& buffer) = 0;

    int id;
};

class ClientboundPacket : public Packet {
  public:
    explicit ClientboundPacket(const int id) : Packet(id) {}
};

class ServerboundPacket : public Packet {
  public:
    explicit ServerboundPacket(const int id) : Packet(id) {}
    virtual void handle(NetworkSession& session) = 0;
};

} // namespace stratos

#endif //PACKET_H
