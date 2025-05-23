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
#include <iphlpapi.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <ifaddrs.h>
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
    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd == INVALID_SOCKET_FD) {
        throw std::runtime_error("Failed to create socket");
    }

    epollFd = epoll_create1(0);
    if (epollFd == -1) {
        throw std::runtime_error("epoll_create1 failed: " + std::string(strerror(errno)));
    }

    const int flags = fcntl(socketFd, F_GETFL, 0);
    if (flags == -1) {
        ::close(socketFd);
        throw std::runtime_error("Failed to get socket flags");
    }

    if (fcntl(socketFd, F_SETFL, flags | O_NONBLOCK) == SOCKET_ERROR) {
        ::close(socketFd);
        throw std::runtime_error("Failed to set non-blocking mode");
    }

    epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = socketFd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, socketFd, &event) == -1)
        throw std::runtime_error("epoll_ctl failed: " + std::string(strerror(errno)));
#endif
}

void stratos::TCPServer::bind() {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);

    if (address == "0.0.0.0") {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else if (inet_pton(AF_INET, address.c_str(), &addr.sin_addr) != 1) {
#ifdef _WIN32
        closesocket(socketFd);
        WSACleanup();
#else
        ::close(socketFd);
#endif
        throw std::runtime_error("Invalid address format: " + address);
    }

    if (::bind(socketFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
#ifdef _WIN32
        const int err = WSAGetLastError();
        closesocket(socketFd);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket to address '" + address + "' (Code: " + std::to_string(err) + ").");
#else
        const int err = errno;
        ::close(socketFd);
        throw std::runtime_error("Failed to bind socket to address '" + address + "' (Code: " + std::to_string(err) + ": " + strerror(err) + ").");
#endif
    }
    isBound = true;
}
void stratos::TCPServer::listen(const int backlog) {
    if (!isBound) bind();
    if (::listen(socketFd, backlog) == SOCKET_ERROR) {
#ifdef _WIN32
        const int err = WSAGetLastError();
        closesocket(socketFd);
        WSACleanup();
        throw std::runtime_error("Failed to listen on socket (Code: " + std::to_string(err) + ").");
#else
        const int err = errno;
        ::close(socketFd);
        throw std::runtime_error("Failed to listen on socket (Code: " + std::to_string(err) + ": " + strerror(err) + ").");
#endif
    }
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

    return {INVALID_SOCKET_FD, "", -1};
#else
    epoll_event events[1];
    int result = epoll_wait(epollFd, events, 1, 10000); // 10 sec timeout

    if (result == -1)
        throw std::runtime_error("epoll_wait() failed (code: " + std::to_string(errno) + ": " + strerror(errno) + ").");

    if (result > 0 && events[0].data.fd == socketFd && (events[0].events & EPOLLIN)) {
        sockaddr_in clientAddr{};
        socklen_t addrLen = sizeof(clientAddr);
        if (int clientSocket = ::accept(socketFd, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen); clientSocket == -1) {
            if (errno != EWOULDBLOCK && errno != EAGAIN)
                throw std::runtime_error("accept() failed (code: " + std::to_string(errno) + ": " + strerror(errno) + ").");
        } else {
            if (setNonBlocking(clientSocket) == -1) {
                ::close(clientSocket);
                throw std::runtime_error("failed to set non-blocking mode: " + std::string(strerror(errno)));
            }

            return {clientSocket, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port)};
        }
    }

    return {INVALID_SOCKET_FD, "", -1};
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
    if (socketFd != INVALID_SOCKET_FD) {
        ::close(socketFd);
        socketFd = INVALID_SOCKET_FD;
    }
    if (epollFd != -1) {
        ::close(epollFd);
        epollFd = -1;
    }
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
int stratos::TCPConnection::receive(const int length, ByteVec& buffer) {
    if (!buffer.data() || length <= 0) return SOCKET_ERROR;

    const int bytes = recv(socketFd, reinterpret_cast<char*>(buffer.data()), length, 0);
    if (bytes == SOCKET_ERROR) {
#ifdef _WIN32
        const int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK || err == WSAEINTR) return -1;
        if (err == WSAECONNRESET) return 0; // Connection reset by peer
#else
        const int err = errno;
        if (err == EAGAIN || err == EWOULDBLOCK || err == EINTR) return -1;
        if (err == ECONNRESET) return 0; // Connection reset by peer
    }
#endif
    buffer.resize(bytes);
    return bytes;
}

/**
 * Sends data to the socket.
 * @param buffer Buffer containing the data to send.
 * @param length Amount of data to send in bytes.
 * @param flags Flags for the send operation (default is 0).
 * @return Number of bytes sent, or SOCKET_ERROR if an error occurred.
 */
int stratos::TCPConnection::send(const ByteVec& buffer, const int length, const int flags) {
    const int bytes = ::send(socketFd, reinterpret_cast<const char*>(buffer.data()), length, flags);
    if (bytes == SOCKET_ERROR) {
#if _WIN32
        if (const int err = WSAGetLastError(); err == WSAEWOULDBLOCK)
#else
        if (const int err = errno; err == EAGAIN || err == EWOULDBLOCK)
#endif
            return 0;
        return SOCKET_ERROR;
    }
    return bytes;
}

void stratos::TCPConnection::close() {
    if (socketFd != INVALID_SOCKET_FD) {
#ifdef _WIN32
        closesocket(socketFd);
#else
        ::close(socketFd);
#endif
        socketFd = INVALID_SOCKET_FD;
    }
}
int stratos::setNonBlocking(SocketFd socketFd) {
#ifdef _WIN32
    u_long mode = 1;
    if (ioctlsocket(socketFd, FIONBIO, &mode) == SOCKET_ERROR)
        return SOCKET_ERROR;
#else
    const int flags = fcntl(socketFd, F_GETFL, 0);
    return (flags != -1 && fcntl(socketFd, F_SETFL, flags | O_NONBLOCK) != -1) ? 0 : -1;
#endif
}
int stratos::getMTUForSocket(const SocketFd socketFd) {
#ifdef _WIN32
    std::cout << "Getting MTU for socket: " << socketFd << "\n";
    sockaddr_in addr{};
    int addrLen = sizeof(addr);
    if (getsockname(socketFd, reinterpret_cast<sockaddr*>(&addr), &addrLen) == SOCKET_ERROR) return -1;

    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ipStr, sizeof(ipStr));
    const std::string socketIp = ipStr;
    if (socketIp == "127.0.0.1") return 1280; // Localhost MTU

    ULONG outBufLen = 15000;
    std::vector<BYTE> buffer(outBufLen);
    auto* adapterAddresses = reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buffer.data());
    if (const DWORD result = GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST, nullptr, adapterAddresses, &outBufLen); result != NO_ERROR) return -1;

    for (const auto* adapter = adapterAddresses; adapter != nullptr; adapter = adapter->Next) {
        for (const IP_ADAPTER_UNICAST_ADDRESS* ua = adapter->FirstUnicastAddress; ua != nullptr; ua = ua->Next) {
            char adapterIp[INET_ADDRSTRLEN] = {};
            if (ua->Address.lpSockaddr->sa_family == AF_INET) {
                const auto sa_in = reinterpret_cast<sockaddr_in*>(ua->Address.lpSockaddr);
                inet_ntop(AF_INET, &sa_in->sin_addr, adapterIp, sizeof(adapterIp));
                if (socketIp == adapterIp) return static_cast<int>(adapter->Mtu);
            }
        }
    }

    return -1;
#else
    sockaddr_in addr{};
    socklen_t addrLen = sizeof(addr);
    if (getsockname(socketFd, reinterpret_cast<sockaddr*>(&addr), &addrLen) == -1)return -1;

    char ipStr[INET_ADDRSTRLEN];
    if (!inet_ntop(AF_INET, &addr.sin_addr, ipStr, sizeof(ipStr)))return -1;
    std::string socketIp = ipStr;
    if (socketIp == "127.0.0.1") return 1280; // Default for loopback

    ifaddrs* ifaddr;
    if (getifaddrs(&ifaddr) == -1)
        return -1;

    int mtu = -1;
    for (const ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;

        const auto* sa = reinterpret_cast<sockaddr_in*>(ifa->ifa_addr);
        char ifaceIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sa->sin_addr, ifaceIp, sizeof(ifaceIp));

        if (socketIp == ifaceIp) {
            int fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd == -1) break;

            ifreq ifr{};
            strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ);
            if (ioctl(fd, SIOCGIFMTU, &ifr) != -1)
                mtu = ifr.ifr_mtu;

            close(fd);
            break;
        }
    }

    freeifaddrs(ifaddr);
    return mtu;
#endif
}