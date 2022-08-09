//
// Created by serdok on 06/08/22.
//

#ifndef SPP_SOCKETS_PLATFORM_H
#define SPP_SOCKETS_PLATFORM_H

#if defined(SPP_PLATFORM_IS_WINDOWS)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
// Base classes and defines
#include <sys/socket.h>

// IP v4
#include <arpa/inet.h>
#endif

#endif //SPP_SOCKETS_PLATFORM_H
