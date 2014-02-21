#include "TcpServer.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <cstring> // memset
#include <cstdlib> // atoi
#include <cstdio> // snprintf

namespace NetFlux
{
    TcpServer::TcpServer ( )
    {
    }

    TcpServer::~TcpServer ( )
    {
    }

    bool TcpServer::listen ( uint16_t port, int backlog )
    {
        if ( msocket != INVALID )
        {
            return false;
        }

        // We convert the unsigned short port into C string.
        char port_str [ 6 ];
        int ret = snprintf ( port_str, 6, "%hu", port );

        // We give hints on what kinds of socket configs we are looking for.
        struct addrinfo hints;
        memset ( &hints, 0, sizeof ( struct addrinfo ) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = ( AI_PASSIVE | AI_NUMERICSERV );

        // We get the socket configs list
        struct addrinfo * config_list;
        ret = getaddrinfo ( 0, port_str, &hints, &config_list );
        if ( ret != 0 )
        {
#ifdef DEBUG
            std::cout << "NetFlux::TcpServer::listen (getaddrinfo): "
                << gai_strerror ( ret ) << std::endl;
#endif
            return false;
        }

        // We try each config
        bool found = false;
        for ( struct addrinfo * current = config_list ; current -> ai_next != 0 ; ++current )
        {
            msocket = socket ( current -> ai_family, current -> ai_socktype, current -> ai_protocol );
            if ( msocket == INVALID )
            {
#ifdef DEBUG
                perror ( "NetFlux::TcpServer::listen (socket)" );
#endif
                continue;
            }

            ret = bind ( msocket, current -> ai_addr, sizeof ( struct sockaddr ) );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::TcpServer::listen (bind)" );
#endif
                close ( );
                continue;
            }

            found = true;
            break;
        }
        freeaddrinfo ( config_list );

        if ( ! found )
        {
#ifdef DEBUG
            std::cout << "Netflux::TcpServer::listen (getaddrinfo): didn't return any config matching given hints." << std::endl;
#endif
            return false;
        }

        ret = ::listen ( msocket, backlog );
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
}
