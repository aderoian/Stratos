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
#ifdef _WIN32
#include <ws2tcpip.h>
#endif

#include <cstring>
#include <stdexcept>
#include <vector>

stratos::TCPServer::TCPServer(const std::string& address, const int& port) : SocketServer(address, port) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    }

    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }

    u_long mode = 1;
    if (ioctlsocket(socketFd, FIONBIO, &mode) != 0) {
        closesocket(socketFd);
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
        closesocket(socketFd);
        WSACleanup();
        throw std::runtime_error("Invalid address format: " + address);
    }

    if (::bind(socketFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        const int err = WSAGetLastError();
        closesocket(socketFd);
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
    if (::listen(socketFd, backlog) == SOCKET_ERROR) {
        const int err = WSAGetLastError();
        closesocket(socketFd);
        WSACleanup();
        throw std::runtime_error("Failed to listen on socket (Code: " + std::to_string(err) + ").");
    }
#endif
}

stratos::ClientInfo stratos::TCPServer::accept() {
#ifdef _WIN32
    fd_set  readSet;
    timeval timeout{};
    timeout.tv_sec   = 0;
    timeout.tv_usec  = 10000;
    u_long blockMode = 1;

    int err;
    FD_ZERO(&readSet);
    FD_SET(socketFd, &readSet);

    const int result = select(0, &readSet, nullptr, nullptr, &timeout);
    if (result == SOCKET_ERROR) {
        err = WSAGetLastError();
        throw std::runtime_error("select() failed (code: " + std::to_string(err) + ").");
    }

    if (result > 0 && FD_ISSET(socketFd, &readSet)) {
        sockaddr_in    clientAddr{};
        int            addrLen      = sizeof(clientAddr);
        const SocketFd clientSocket = ::accept(socketFd, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);

        if (clientSocket == INVALID_SOCKET) {
            if (err = WSAGetLastError(); err != WSAEWOULDBLOCK) throw std::runtime_error("accept() failed (code: " + std::to_string(err) + ").");
        }

        ioctlsocket(clientSocket, FIONREAD, &blockMode); // Set to non-blocking mode
        return {clientSocket, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port)};
    }

    return {INVALID_SOCKET, "", -1};
#else
    // unix
#endif
}

void stratos::TCPServer::close() {
#ifdef _WIN32

    if (socketFd != INVALID_SOCKET) {
        closesocket(socketFd);
        socketFd = INVALID_SOCKET;
    }
    if (WSACleanup() != 0) {
        throw std::runtime_error("Failed to clean up Winsock");
    }
#else
    // unix
#endif
}

stratos::TCPServer::~TCPServer() {
    close();
}

/**
 * Receives data from the socket.
 * @param length Amount of data to receive in bytes.
 * @param buffer Buffer to store the received data.
 * @return Number of bytes received, zero if the connection was closed, or -1 if there was no data to read.
 * @throws runtime_error if a SOCKET_ERROR occurs.
 */
int stratos::TCPConnection::receive(const int length, byte& buffer) {
#ifdef _WIN32
    if (!buffer || length <= 0) return SOCKET_ERROR;

    std::vector<char> readBuf(length);
    const int         bytes = recv(socketFd, readBuf.data(), length, 0);
    if (bytes == SOCKET_ERROR) {
        if (const int err = WSAGetLastError(); err == WSAEWOULDBLOCK || err == WSAEINTR) return -1;
        throw std::runtime_error("recv() failed (code: " + std::to_string(WSAGetLastError()) + ").");
    }

    if (bytes > 0) std::memcpy(&buffer, readBuf.data(), bytes);
    return bytes;
#else
    // unix
#endif
}

int stratos::TCPConnection::send(const byte& buffer, const int length, const int flags) {
#ifdef _WIN32
    int        sent    = 0;
    const auto sendBuf = reinterpret_cast<const char*>(&buffer);
    while (sent < length) {
        const int bytes = ::send(socketFd, sendBuf + sent, length - sent, flags);
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
    if (socketFd != INVALID_SOCKET) {
        closesocket(socketFd);
        socketFd = INVALID_SOCKET;
    }
#else
    // unix
#endif
}

stratos::TCPConnection::~TCPConnection() {
    close();
}