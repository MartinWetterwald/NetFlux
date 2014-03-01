#ifndef _LIBS_HPP_
#define _LIBS_HPP_

#ifndef _WIN32
#include <sys/socket.h> // socket
#include <unistd.h> // close
#include <arpa/inet.h> // htonl, htons...
#include <netinet/in.h> // struct sockaddr_in
#include <netdb.h> // AF_UNSPEC
#define SOCKET int
#define SOCKADDR_IN6 sockaddr_in6
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr
#else
#define NTDDI_VERSION NTDDI_VISTA
#include <winsock2.h>
#include <ws2tcpip.h>
#define inet_ntop(param1,param2,param3,param4) WSAAddressToString(param1,param2,param3,param4)
#endif

#include <cstdint>

#ifdef DEBUG
#include <cerrno>
#include <cstdio>
#endif

#endif
