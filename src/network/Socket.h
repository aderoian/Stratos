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

#endif
#include <string>
#include <utility>

namespace stratos {
#ifdef _WIN32
using SocketFd                   = SOCKET;
constexpr auto INVALID_SOCKET_FD = INVALID_SOCKET;
#else
using SocketFd                       = int;
constexpr SocketFd INVALID_SOCKET_FD = -1;
#endif

struct ClientInfo {
    SocketFd    socket;
    std::string ip;
    int         port;

    bool operator==(const ClientInfo& other) const {
        return socket == other.socket && ip == other.ip && port == other.port;
    }
};

class Socket {
  public:
    Socket(std::string address, const int& port) : address(std::move(address)), port(port) {}
    Socket(const Socket&) = delete;
    Socket(Socket&&)      = default;
    virtual ~Socket()     = default;

    [[nodiscard]] const std::string& getAddress() const { return address; }
    [[nodiscard]] int                getPort() const { return port; }
    [[nodiscard]] int                getLastError() const { return lastError; }
    [[nodiscard]] bool               isValid() const { return socketFd != INVALID_SOCKET; }

    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&)      = default;

  protected:
    SocketFd    socketFd = INVALID_SOCKET;
    std::string address;
    int         port;

    int lastError = 0;
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
#endif
};

class SocketConnection : public Socket {
  public:
    SocketConnection(const SocketFd socketFd, const std::string& address, const int& port) : Socket(address, port) { this->socketFd = socketFd; }
    ~SocketConnection() override = default;

    virtual int  receive(int length, byte& buffer)               = 0;
    virtual int  send(const byte& buffer, int length, int flags) = 0;
    virtual void close()                                         = 0;
};

class TCPConnection final : public SocketConnection {
  public:
    TCPConnection(const SocketFd socketFd, const std::string& address, const int& port) : SocketConnection(socketFd, address, port) {}
    ~TCPConnection() override;

    int  receive(int length, byte& buffer) override;
    int  send(const byte& buffer, int length, int flags) override;
    void close() override;
};
} // namespace stratos

template <> struct std::hash<stratos::ClientInfo> {
    size_t operator()(const stratos::ClientInfo& client) const noexcept { return hash<stratos::SocketFd>()(client.socket) ^ hash<string>()(client.ip) ^ hash<int>()(client.port); }
};

#endif // SOCKET_H
