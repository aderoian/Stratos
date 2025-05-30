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

namespace stratos {
class PacketHandler;
class NetworkSession;
class PacketBuffer;

enum ProtocolState { Handshaking = 0x00, Status = 0x01, Login = 0x02, Configuration = 0x03, Play = 0x04 };
enum PacketDirection { Clientbound = 0x00, Serverbound = 0x01 };

class Packet {
public:
    explicit Packet(const int id) : id(id) {}
    virtual ~Packet() = default;

    int getId() const { return id; }
    virtual void decrypt(PacketBuffer& buffer) = 0;
    virtual void encrypt(PacketBuffer& buffer) = 0;
    virtual bool accept(PacketHandler& handler) = 0;

    int id;
};



class ClientboundPacket : virtual public Packet {
public:
    explicit ClientboundPacket(const int id) : Packet(id) {}
    ~ClientboundPacket() override = default;
    void decrypt(PacketBuffer& buffer) override {}
    bool accept(PacketHandler& handler) override { return false; } // Clientbound packets are not handled by handlers
};

class ServerboundPacket : virtual public Packet {
public:
    explicit ServerboundPacket(const int id) : Packet(id) {}
    ~ServerboundPacket() override = default;
    void encrypt(PacketBuffer& buffer) override {}
};

struct PacketKey {
    int state;
    int direction;
    int id;

    bool operator==(const PacketKey& other) const;
};

inline bool PacketKey::operator==(const PacketKey& other) const {
    return state == other.state && direction == other.direction && id == other.id;
}
}

template <>
struct std::hash<stratos::PacketKey> {
    std::size_t operator()(const stratos::PacketKey& key) const noexcept {
        const std::size_t h1 = std::hash<int>()(key.state);
        const std::size_t h2 = std::hash<int>()(key.direction);
        const std::size_t h3 = std::hash<int>()(key.id);

        std::size_t seed = h1;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

namespace stratos {
class PacketRegistry final {
  public:
    typedef std::function<std::unique_ptr<Packet>()> PacketFactory;

    PacketRegistry();

    static PacketRegistry& instance() {
        static PacketRegistry registry;
        return registry;
    }

    std::unique_ptr<Packet> create(const PacketKey& key);

  private:
    std::unordered_map<PacketKey, PacketFactory> factories ;

    void setup();
    void registerPacket(const PacketKey& key, PacketFactory factory);
};

inline PacketRegistry::PacketRegistry() : factories() {
    setup();
}
inline std::unique_ptr<Packet> PacketRegistry::create(const PacketKey& key) {
    if (const auto it = factories.find(key); it != factories.end()) return it->second();
    return nullptr;
}
inline void PacketRegistry::registerPacket(const PacketKey& key, PacketFactory factory) {
    factories[key] = std::move(factory);
}

} // namespace stratos

#endif //PACKET_H
