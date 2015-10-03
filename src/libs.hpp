#ifndef LIBS_HPP_
#define LIBS_HPP_

#if __unix__ || __posix__ || __linux__ || __APPLE__
#include <sys/socket.h> // socket
#include <unistd.h> // close
#include <arpa/inet.h> // htonl, htons...
#include <netinet/in.h> // struct sockaddr_in
#include <netdb.h> // AF_UNSPEC
typedef int SOCKET;
#define closesocket ::close

#elif _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define inet_ntop(param1,param2,param3,param4) inet_ntop(param1,(PVOID)param2,param3,param4)
#define snprintf _snprintf_s
typedef int ssize_t;

#else
#error Platform not supported.
#endif




#include <cstdint>

#ifdef DEBUG
#include <cerrno>
#include <cstdio>
#else
#define NDEBUG
#endif

#include <cassert>

#endif
