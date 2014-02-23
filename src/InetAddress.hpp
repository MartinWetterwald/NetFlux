#ifndef _INET_ADDRESS_HPP_
#define _INET_ADDRESS_HPP_

#include "libs.hpp"

#include <string>
#include <cstring> // memcpy

namespace NetFlux
{
    class InetAddress : protected sockaddr
    {
    public:
        InetAddress ( );
        InetAddress ( const sockaddr & saddr );
        InetAddress ( const sockaddr_in & sin );
        InetAddress ( const sockaddr_in6 & sin6 );

        std::string retrieveIp ( ) const;
        uint16_t retrievePort ( ) const;


    protected:
        inline void fillAddress ( const sockaddr * saddr )
        {
            sa_family = saddr -> sa_family;
            memcpy ( sa_data, saddr -> sa_data, sizeof ( saddr -> sa_data ) );
        }
    };
}

#endif
