#include "Udp_Client.hpp"

#ifdef DEBUG
#include <iostream>
#endif

namespace NetFlux {
namespace Udp
{
    Client::~Client ( ) { }

    bool Client::connectTo ( const std::string & host, uint16_t port )
    {
        // We convert the unsigned short port into C string.
        char port_str [ PORT_LENGTH + 1 ];
        int ret = snprintf ( port_str, PORT_LENGTH + 1, "%hu", port );
        if ( ret < 0 || ret > PORT_LENGTH )
        {
#ifdef DEBUG
            std::cout << "NetFlux::Udp::Client::connectTo (snprintf): invalid return value ("
                << ret << ")";
#endif
            return false;
        }

        // We give hints on what kinds of socket configs we are looking for.
        addrinfo hints;
        memset ( &hints, 0, sizeof ( addrinfo ) );
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        // We get the socket configs list
        addrinfo * config_list;
        ret = getaddrinfo ( host.c_str ( ), port_str, &hints, &config_list );
        if ( ret != 0 )
        {
#ifdef DEBUG
            std::cout << "NetFlux::Udp::Client::connectTo (getaddrinfo): "
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
                perror ( "NetFlux::Udp::Client::connectTo (socket)" );
#endif
                continue;
            }

            ret = connect ( sockfd, current -> ai_addr, current -> ai_addrlen );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::Udp::Client::connectTo (connect)" );
#endif
                closesocket ( sockfd );
                continue;
            }

            msocket = sockfd;
            fillAddress ( current -> ai_addr );

            freeaddrinfo ( config_list );
            return true;
        }

        // We haven't found any suitable config.
#ifdef DEBUG
        std::cout << "Netflux::Udp::Client::connectTo (getaddrinfo): didn't return any config matching given hints." << std::endl;
#endif
        freeaddrinfo ( config_list );
        msocket = INVALID;
        return false;
    }

    Client::Client ( SOCKET sock, const InetAddress & address )
        : Net::Socket ( sock, address ) { }
} }

