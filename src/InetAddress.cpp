#include "InetAddress.hpp"

#include <cstring> // memcpy

namespace NetFlux
{
    InetAddress::InetAddress ( ) { }

    InetAddress::InetAddress ( const sockaddr & saddr )
    {
        sa_family = saddr.sa_family;
        memcpy ( sa_data, saddr.sa_data, sizeof ( saddr.sa_data ) );
    }


    InetAddress::InetAddress ( const sockaddr_in & sin )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin ) ) { }


    InetAddress::InetAddress ( const sockaddr_in6 & sin6 )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin6 ) ) { }


    bool InetAddress::ipToString ( std::string & str )
    {
        char dest [ INET6_ADDRSTRLEN ];
        const char * ret;

        switch ( sa_family )
        {
            case AF_INET:
            {
                sockaddr_in * sin = reinterpret_cast <sockaddr_in *> ( this );
                ret = inet_ntop ( sa_family, &sin -> sin_addr, dest, INET6_ADDRSTRLEN );
            }
            break;

            case AF_INET6:
            {
                sockaddr_in6 * sin6 = reinterpret_cast <sockaddr_in6 *> ( this );
                ret = inet_ntop ( sa_family, &sin6 -> sin6_addr, dest, INET6_ADDRSTRLEN );
            }
            break;

            default:
                return false;
        }

        if ( ret == 0 )
        {
            return false;
        }

        str = ret;
        return true;
    }
}
