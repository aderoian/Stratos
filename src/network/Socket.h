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
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else

#endif
#include <atomic>
#include <memory>
#include <thread>

namespace spdlog {
class logger;
}

namespace stratos {
class SocketServer {
public:
    SocketServer(const std::shared_ptr<spdlog::logger>& logger, const std::string& address, const int& port) : logger(logger), address(address), port(port) {}
    virtual ~SocketServer()   = default;
    virtual void bind() = 0;
    virtual void listen() { listen(SOMAXCONN); }
    virtual void listen(int backlog) = 0;
    virtual void stop()              = 0;

protected:
    std::shared_ptr<spdlog::logger> logger;
    unsigned long long              socket_fd;
    const std::string               address;
    int                             port;
    bool                            isBound   = false;
};

class TCPServer final : public SocketServer {
public:
    TCPServer(const std::shared_ptr<spdlog::logger>& logger, const std::string& address, const int& port);
    ~TCPServer() override;
    void bind() override;
    void listen(int backlog) override;
    void run();
    void stop() override;

private:
#ifdef _WIN32
    WSADATA     wsaData;
    std::thread runner;
    std::atomic<bool>               isRunning = false;
#endif
};

class SocketConnection {
public:
    SocketConnection(const std::shared_ptr<spdlog::logger>& logger, std::string address, const int& port) : logger(logger), address(std::move(address)), port(port) {}
    virtual ~SocketConnection() = default;

    virtual int receive(int amount, byte& buffer) = 0;
    virtual int send(const byte& buffer, int length, int flags = 0) = 0;
    virtual void close() = 0;

    [[nodiscard]] const std::string& getAddress() const { return address; }
    [[nodiscard]] int getPort() const { return port; }
protected:
    std::shared_ptr<spdlog::logger> logger;
    unsigned long long              socket_fd;
    const std::string               address;
    int                             port;
};

class TCPConnection final : public SocketConnection {
public:
    TCPConnection(const std::shared_ptr<spdlog::logger>& logger, std::string address, const int& port) : SocketConnection(logger, std::move(address), port) {}
    ~TCPConnection() override;

    int receive(int length, byte& buffer) override;
    int send(const byte& buffer, int length, int flags = 0) override;
    void close() override;
};
} // namespace stratos

#endif // SOCKET_H
