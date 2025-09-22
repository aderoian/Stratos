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
#include <functional>
#include <memory>

#define SERVERBOUND_PACKET_FOOTER(clazz) \
bool accept(PacketHandler& handler) const override { return handler.handle(static_cast<const clazz*>(this)); } \
~clazz() override = default; \
void decrypt(const PacketBuffer& buffer) override;
#define CLIENTBOUND_PACKET_FOOTER(clazz) \
~clazz() override = default; \
void encrypt(PacketBuffer& buffer) const override;

namespace stratos::network {
class PingRequest;
class StatusRequest;
class LoginCookieResponse;
class LoginAcknowledge;
class LoginPluginResponse;
class EncryptionResponse;
class KeepAliveResponse;
class LoginStart;
class LegacyServerListPing;
class ClientHandshake;
class ServerboundKnownPacks;
class ConfigurationResourcePackResponse;
class ConfigurationPong;
class ConfigurationServerboundKeepAlive;
class AcknowledgeFinishConfiguration;
class ConfigurationServerPluginMessage;
class ConfigurationCookieResponse;
class ConfigurationClientInformation;
class Packet;
class PacketHandler;
class PacketBuffer;

typedef std::function<const Packet*()> PacketFactory;

enum ProtocolState { Handshaking = 0x00, Status = 0x01, Login = 0x02, Configuration = 0x03, Play = 0x04 };
enum PacketDirection { Clientbound = 0x00, Serverbound = 0x01 };

class Packet {
public:
    explicit Packet(const int id) : id(id) {}
    virtual ~Packet() = default;

    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] virtual PacketDirection getDirection() const = 0;
    virtual void decrypt(const PacketBuffer& buffer) = 0;
    virtual void encrypt(PacketBuffer& buffer) const = 0;
    virtual bool accept(PacketHandler& handler) const = 0;

    int id;
};

class PacketHandler {
public:
    virtual ~PacketHandler() = default;
    virtual bool handle(const Packet* packet) { return false; }
    virtual bool handle(const ConfigurationClientInformation* packet) { return false; }
    virtual bool handle(const ConfigurationCookieResponse* packet) { return false; }
    virtual bool handle(const ConfigurationServerPluginMessage* packet) { return false; }
    virtual bool handle(const AcknowledgeFinishConfiguration* packet) { return false; }
    virtual bool handle(const ConfigurationServerboundKeepAlive* packet) { return false; }
    virtual bool handle(const ConfigurationPong* packet) { return false; }
    virtual bool handle(const ConfigurationResourcePackResponse* packet) { return false; }
    virtual bool handle(const ServerboundKnownPacks* packet) { return false; }
    virtual bool handle(const ClientHandshake* packet) { return false; }
    virtual bool handle(const LegacyServerListPing* packet) { return false; }
    virtual bool handle(const LoginStart* packet) { return false; }
    virtual bool handle(const EncryptionResponse* packet) { return false; }
    virtual bool handle(const LoginPluginResponse* packet) { return false; }
    virtual bool handle(const LoginAcknowledge* packet) { return false; }
    virtual bool handle(const LoginCookieResponse* packet) { return false; }
    virtual bool handle(const KeepAliveResponse* packet) { return false; }
    virtual bool handle(const StatusRequest* packet) { return false; }
    virtual bool handle(const PingRequest* packet) { return false; }
};

// template <typename T>
// class TypedPacket : public Packet {
// public:
//     explicit TypedPacket(const int id) : Packet(id) {}
//     ~TypedPacket() override = default;
//
//     [[nodiscard]] T& as() { return static_cast<T&>(*this); }
//     [[nodiscard]] const T& as() const { return static_cast<const T&>(*this); }
//
//     virtual bool accept(PacketHandler& handler) const override { return handler.handle(static_cast<const T*>(this)); }
// };
//
// class IClientboundPacket {
// public:
//     virtual ~IClientboundPacket() = default;
// };

// template <typename T>
class ClientboundPacket : public Packet {//public TypedPacket<T>, public IClientboundPacket {
public:
    explicit ClientboundPacket(const int id) : Packet(id){}
    ~ClientboundPacket() override = default;
    [[nodiscard]] PacketDirection getDirection() const override { return Clientbound; }
    void decrypt(const PacketBuffer& buffer) override {}
    bool accept(PacketHandler& handler) const override { return false; } // Clientbound packets are not handled by handlers
};

// class IServerboundPacket {
// public:
//     virtual ~IServerboundPacket() = default;
//     [[nodiscard]] virtual int getId() const = 0;
//     virtual bool accept(PacketHandler& handler) const = 0;
// };

// template <typename T>
class ServerboundPacket : public Packet {//public TypedPacket<T>, public IServerboundPacket {
public:
    explicit ServerboundPacket(const int id) : Packet(id) {}
    ~ServerboundPacket() override = default;
    [[nodiscard]] PacketDirection getDirection() const override { return Serverbound; }
    void encrypt(PacketBuffer& buffer) const override {}
};

struct PacketKey {
    ProtocolState state;
    PacketDirection direction;
    int id;

    bool operator==(const PacketKey& other) const {
        return state == other.state && direction == other.direction && id == other.id;
    }
};

struct PacketDefinition {
    int id;
    PacketFactory factory;
    ProtocolState state;
    PacketDirection direction;
};
} // namespace stratos::network

template <>
struct std::hash<stratos::network::PacketKey> {
    std::size_t operator()(const stratos::network::PacketKey& key) const noexcept {
        return std::hash<int>()(key.state) ^ std::hash<int>()(key.direction) ^ std::hash<int>()(key.id) << 1;
    }
};
#endif //PACKET_H