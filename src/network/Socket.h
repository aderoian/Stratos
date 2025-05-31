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

#ifndef SOCKET_H
#define SOCKET_H

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#endif
#include <atomic>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace stratos {
#ifdef _WIN32
using SocketFd                   = SOCKET;
constexpr auto INVALID_SOCKET_FD = INVALID_SOCKET;
#else
using SocketFd                       = int;
constexpr SocketFd INVALID_SOCKET_FD = -1;
constexpr int      SOCKET_ERROR      = -1;
#endif

using byte    = unsigned char;
using ByteVec = std::vector<byte>;

struct ClientInfo {
    SocketFd    socket;
    std::string ip;
    int         port;

    bool operator==(const ClientInfo& other) const { return socket == other.socket && ip == other.ip && port == other.port; }
};

class Socket {
  public:
    Socket(std::string address, const int& port) : address(std::move(address)), port(port) {}
    Socket(const Socket&) = delete;
    Socket(Socket&&)      = default;
    virtual ~Socket()     = default;

    [[nodiscard]] SocketFd           getFd() const { return socketFd; }
    [[nodiscard]] const std::string& getAddress() const { return address; }
    [[nodiscard]] int                getPort() const { return port; }
    [[nodiscard]] bool               isValid() const { return socketFd != INVALID_SOCKET_FD; }

    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&)      = default;

  protected:
    SocketFd    socketFd = INVALID_SOCKET_FD;
    std::string address;
    int         port;
};

class SocketServer : public Socket {
  public:
    SocketServer(const std::string& address, const int& port) : Socket(address, port) {}
    ~SocketServer() override = default;

    virtual void       bind() = 0;
    virtual void       listen() { listen(SOMAXCONN); }
    virtual void       listen(int backlog) = 0;
    virtual ClientInfo accept()            = 0;
    virtual void       close()             = 0;

  protected:
    bool isBound = false;
};

class TCPServer final : public SocketServer {
  public:
    TCPServer(const std::string& address, const int& port);
    ~TCPServer() override;
    void       bind() override;
    void       listen(int backlog) override;
    ClientInfo accept() override;
    void       close() override;

  private:
#ifdef _WIN32
    WSADATA wsaData;
#else
    int epollFd;
#endif
};

int    setNonBlocking(SocketFd socketFd);

class SocketConnection : public Socket {
  public:
    SocketConnection(const SocketFd socketFd, const std::string& address, const int& port) : Socket(address, port) { this->socketFd = socketFd; }
    ~SocketConnection() override = default;

    virtual int  receive(int length, ByteVec& buffer)               = 0;
    virtual int  send(const ByteVec& buffer, int length, int flags) = 0;
    virtual bool close()                                            = 0;
};

class TCPConnection : public SocketConnection {
  public:
    TCPConnection(const SocketFd socketFd, const std::string& address, const int& port) : SocketConnection(socketFd, address, port) {}
    ~TCPConnection() override = default;

    int  receive(int length, ByteVec& buffer) override;
    int  send(const ByteVec& buffer, int length, int flags) override;
    bool close() override;

    [[nodiscard]] bool isClosed() const { return closed.load(std::memory_order_acquire); }

  protected:
    std::atomic<bool> closed = false;
};
} // namespace stratos

template <> struct std::hash<stratos::ClientInfo> {
    size_t operator()(const stratos::ClientInfo& client) const noexcept { return hash<stratos::SocketFd>()(client.socket) ^ hash<string>()(client.ip) ^ hash<int>()(client.port); }
};

#endif // SOCKET_H
