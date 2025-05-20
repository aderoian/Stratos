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
#include <memory>

namespace spdlog {
class logger;
}

namespace stratos {

class Socket {
public:
    Socket (const std::shared_ptr<spdlog::logger> & logger, const std::string & address, const int & port)
        : logger(logger), address(address), port(port) {}
    virtual ~Socket() = default;
    virtual void bind() = 0;
    virtual void stop() = 0;
protected:
    std::shared_ptr<spdlog::logger> logger;
    unsigned long long socket_fd;
    const std::string address;
    int port;
    bool isBound = false;
};

class TCPSocket final : public Socket {
public:
    TCPSocket(const std::shared_ptr<spdlog::logger> & logger, const std::string & address, const int & port);
    ~TCPSocket() override;
    void bind() override;
    void stop() override;
private:
#ifdef _WIN32
    WSADATA wsaData;
#endif
};

} // namespace stratos

#endif //SOCKET_H
