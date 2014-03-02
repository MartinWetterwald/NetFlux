#ifndef _LIBS_HPP_
#define _LIBS_HPP_

#ifndef _WIN32
#include <sys/socket.h> // socket
#include <unistd.h> // close
#include <arpa/inet.h> // htonl, htons...
#include <netinet/in.h> // struct sockaddr_in
#include <netdb.h> // AF_UNSPEC
#define SOCKET int
#define closesocket ::close
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#define inet_ntop(param1,param2,param3,param4) inet_ntop(param1,(PVOID)param2,param3,param4)
#define snprintf _snprintf_s
#endif

#include <cstdint>

#ifdef DEBUG
#include <cerrno>
#include <cstdio>
#endif

#endif
