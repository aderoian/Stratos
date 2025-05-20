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

#include "Socket.h"

stratos::TCPSocket::TCPSocket(const std::shared_ptr<spdlog::logger>& logger, const std::string& address,
                              const int& port)
    : Socket(logger, address, port) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }
#else
    // unix
#endif
}

void stratos::TCPSocket::bind() {
#ifdef _WIN32
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);

    if (address == "0.0.0.0") { // edge case where Windows doesn't like inet_pton of 0.0.0.0
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) != 1) {
        closesocket(socket_fd);
        WSACleanup();
        throw std::runtime_error("Invalid address format: " + address);
    }

    if (::bind(socket_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        const int err = WSAGetLastError();
        closesocket(socket_fd);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket to address '" + address + "' (Code: " + std::to_string(err) +
                                 ").");
    }
#else
    // unix
#endif

    isBound = true;
}

void stratos::TCPSocket::stop() {
    if (isBound) {
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#else
        // unix
#endif
        isBound = false;
    }
}

stratos::TCPSocket::~TCPSocket() {
    stop();
}