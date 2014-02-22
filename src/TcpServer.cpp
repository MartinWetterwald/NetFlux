#include "TcpServer.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <cstring> // memset
#include <cstdlib> // atoi
#include <cstdio> // snprintf

namespace NetFlux
{
    TcpServer * TcpServer::Create ( uint16_t port )
    {
        // We convert the unsigned short port into C string.
        char port_str [ 6 ];
        int ret = snprintf ( port_str, 6, "%hu", port );

        // We give hints on what kinds of socket configs we are looking for.
        addrinfo hints;
        memset ( &hints, 0, sizeof ( addrinfo ) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = ( AI_PASSIVE | AI_NUMERICSERV );

        // We get the socket configs list
        addrinfo * config_list;
        ret = getaddrinfo ( 0, port_str, &hints, &config_list );
        if ( ret != 0 )
        {
#ifdef DEBUG
            std::cout << "NetFlux::TcpServer::listen (getaddrinfo): "
                << gai_strerror ( ret ) << std::endl;
#endif
            return 0;
        }

        int sockfd;

        // We try each config
        for ( addrinfo * current = config_list ; current -> ai_next != 0 ; ++current )
        {
            sockfd = socket ( current -> ai_family, current -> ai_socktype, current -> ai_protocol );
            if ( sockfd == INVALID )
            {
#ifdef DEBUG
                perror ( "NetFlux::TcpServer::listen (socket)" );
#endif
                continue;
            }

            ret = bind ( sockfd, current -> ai_addr, sizeof ( sockaddr ) );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::TcpServer::listen (bind)" );
#endif
                ::close ( sockfd );
                continue;
            }

            // Everything is fine. We can allocate the TcpServer.
            TcpServer * tcpServer = new TcpServer ( sockfd, * current -> ai_addr );
            freeaddrinfo ( config_list );
            return tcpServer;
        }

        // We haven't found any suitable config.
#ifdef DEBUG
        std::cout << "Netflux::TcpServer::listen (getaddrinfo): didn't return any config matching given hints." << std::endl;
#endif
        freeaddrinfo ( config_list );
        return 0;
    }

    TcpServer::~TcpServer ( )
    {
    }

    bool TcpServer::listen ( int backlog )
    {
        int ret = ::listen ( msocket, backlog );
        if ( ret == -1 )
        {
#ifdef DEBUG
            perror ( "NetFlux::TcpServer::listen (listen)" );
#endif
            close ( );
            return false;
        }

        return true;
    }

    TcpServer::TcpServer ( int sock, const InetAddress & address )
        : Socket::Socket ( sock, address )
    {
    }
}
