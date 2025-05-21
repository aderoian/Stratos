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

#include "spdlog/logger.h"

stratos::TCPServer::TCPServer(const std::shared_ptr<spdlog::logger>& logger, const std::string& address, const int& port) : SocketServer(logger, address, port) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }

    u_long mode = 1;
    if (ioctlsocket(socket_fd, FIONBIO, &mode) != 0) {
        closesocket(socket_fd);
        WSACleanup();
        throw std::runtime_error("Failed to set non-blocking mode.");
    }
#else
    // unix
#endif
}

void stratos::TCPServer::bind() {
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
        throw std::runtime_error("Failed to bind socket to address '" + address + "' (Code: " + std::to_string(err) + ").");
    }
#else
    // unix
#endif

    isBound = true;
}
void stratos::TCPServer::listen(const int backlog) {
    if (!isBound) bind();
#ifdef _WIN32
    if (::listen(socket_fd, backlog) == SOCKET_ERROR) {
        const int err = WSAGetLastError();
        closesocket(socket_fd);
        WSACleanup();
        throw std::runtime_error("Failed to listen on socket (Code: " + std::to_string(err) + ").");
    }
#endif

    runner = std::thread(&TCPServer::run, this);
    if (!runner.joinable()) {
#ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
#endif
        throw std::runtime_error("Failed to create thread for socket.");
    }

    runner.detach();
}

void stratos::TCPServer::run() {
    if (isRunning || !isBound) return;

    bool expected = false;
    isRunning.compare_exchange_strong(expected, true);
#ifdef _WIN32
    fd_set  readSet;
    timeval timeout{};
    timeout.tv_sec  = 0;
    timeout.tv_usec = 10000;
    u_long blockMode = 1;

    int err;
    while (isRunning) {
        FD_ZERO(&readSet);
        FD_SET(socket_fd, &readSet);

        const int result = select(0, &readSet, nullptr, nullptr, &timeout);
        if (result == SOCKET_ERROR) {
            err = WSAGetLastError();
            logger->error("select() failed (code: {}).", err);
            break;
        }

        if (result > 0 && FD_ISSET(socket_fd, &readSet)) {
            sockaddr_in  clientAddr{};
            int          addrLen      = sizeof(clientAddr);
            const SOCKET clientSocket = accept(socket_fd, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

            if (clientSocket == INVALID_SOCKET) {
                if (err = WSAGetLastError(); err != WSAEWOULDBLOCK) logger->error("accept() failed (code: {}).", err);
                continue;
            }

            logger->info("Accepted connection from {}:{}", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
            ioctlsocket(clientSocket, FIONREAD, &blockMode); // Set to non-blocking mode
            // TODO: spawn client handler thread or queue work
            closesocket(clientSocket); // Placeholder
        }
    }

    closesocket(socket_fd);
    WSACleanup();
    isBound = false;
#else
    // Unix implementation
#endif
}

void stratos::TCPServer::stop() {
    bool expected = true;
    isRunning.compare_exchange_strong(expected, false);

    runner.join();
}

stratos::TCPServer::~TCPServer() {
    stop();
}

int stratos::TCPConnection::receive(int amount, byte& buffer) {
#ifdef _WIN32
    char      readBuf[amount];
    const int bytes = recv(socket_fd, readBuf, amount, 0);
    if (bytes == SOCKET_ERROR) {
        if (const int err = WSAGetLastError(); err == WSAEWOULDBLOCK) {
            Sleep(0); // Yield to other threads to avoid busy waiting on blocked socket
            return 0;
        }
        return SOCKET_ERROR;
    }

    if (bytes > 0) std::memcpy(&buffer, readBuf, bytes);
    return bytes;
#else
    // unix
#endif
}

int stratos::TCPConnection::send(const byte& buffer, const int length, const int flags) {
#ifdef _WIN32
    int        sent    = 0;
    const auto sendBuf = reinterpret_cast<const char*>(&buffer);
    while(sent < length) {
        const int bytes = ::send(socket_fd, sendBuf + sent, length - sent, flags);
        if (bytes == SOCKET_ERROR) {
            if (const int err = WSAGetLastError(); err == WSAEWOULDBLOCK) {
                Sleep(0); // Yield to other threads to avoid busy waiting on blocked socket
                continue;
            }
            return SOCKET_ERROR;
        }

        sent += bytes;
    }

    return sent;
#else
    // unix
#endif
}

void stratos::TCPConnection::close() {
#ifdef _WIN32
    if (socket_fd != INVALID_SOCKET) {
        closesocket(socket_fd);
        socket_fd = INVALID_SOCKET;
    }
#else
    // unix
#endif
}

stratos::TCPConnection::~TCPConnection() {
    close();
}