#include "Tcp_Server.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#include <cstring> // memset
#include <cstdio> // snprintf

namespace NetFlux {
namespace Tcp
{
    bool Server::listen ( uint16_t port, int family, int backlog )
    {
        // We convert the unsigned short port into C string.
        char port_str [ PORT_LENGTH + 1 ];
        int ret = snprintf ( port_str, PORT_LENGTH + 1, "%hu", port );
        if ( ret < 0 || ret > PORT_LENGTH )
        {
#ifdef DEBUG
            std::cout << "NetFlux::Tcp::Server::listen (snprintf): invalid return value ("
                << ret << ")";
#endif
            return false;
        }

        // We give hints on what kinds of socket configs we are looking for.
        addrinfo hints;
        memset ( &hints, 0, sizeof ( addrinfo ) );
        hints.ai_family = family;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = ( AI_PASSIVE | AI_NUMERICSERV );

        // We get the socket configs list
        addrinfo * config_list;
        ret = getaddrinfo ( 0, port_str, &hints, &config_list );
        if ( ret != 0 )
        {
#ifdef DEBUG
            std::cout << "NetFlux::Tcp::Server::listen (getaddrinfo): "
                << gai_strerror ( ret ) << std::endl;
#endif
            return false;
        }

        SOCKET sockfd;

        // We try each config
        for ( addrinfo * current = config_list ; current != 0 ; current = current -> ai_next )
        {
            sockfd = socket ( current -> ai_family, current -> ai_socktype, current -> ai_protocol );
            if ( sockfd == INVALID )
            {
#ifdef DEBUG
                perror ( "NetFlux::Tcp::Server::listen (socket)" );
#endif
                continue;
            }

            const int yes = 1;
            ret = setsockopt ( sockfd, SOL_SOCKET, SO_REUSEADDR, ( const char * ) &yes, sizeof ( int ) );
            if ( ret == -1 )
            {
                perror ( "NetFlux::Tcp::Server::listen (setsockopt)" );
                closesocket ( sockfd );
                continue;
            }

            ret = bind ( sockfd, current -> ai_addr, current -> ai_addrlen );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::Tcp::Server::listen (bind)" );
#endif
                closesocket ( sockfd );
                continue;
            }

            ret = ::listen ( sockfd, backlog );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::Tcp::Server::listen (listen)" );
#endif
                closesocket ( sockfd );
                break;
            }

            msocket = sockfd;
            fillAddress ( current -> ai_addr );

            freeaddrinfo ( config_list );
            return true;
        }

        // We haven't found any suitable config.
#ifdef DEBUG
        std::cout << "Netflux::Tcp::Server::listen (getaddrinfo): didn't return any config matching given hints." << std::endl;
#endif
        freeaddrinfo ( config_list );
        msocket = INVALID;
        return false;
    }

    Server::~Server ( ) { }

    Server::Server ( SOCKET sock, const InetAddress & address ) : Socket ( sock, address ) { }

    void Server::timeoutEventAction ( ) { }
} }
