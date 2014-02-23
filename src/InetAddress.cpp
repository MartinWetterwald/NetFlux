#include "InetAddress.hpp"

namespace NetFlux
{
    InetAddress::InetAddress ( ) { }

    InetAddress::InetAddress ( const sockaddr & saddr )
    {
        fillAddress ( &saddr );
    }

    InetAddress::InetAddress ( const sockaddr_in & sin )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin ) ) { }


    InetAddress::InetAddress ( const sockaddr_in6 & sin6 )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin6 ) ) { }


    std::string InetAddress::retrieveIp ( ) const
    {
        char dest [ INET6_ADDRSTRLEN ];
        const char * ret;

        switch ( sa_family )
        {
            case AF_INET:
            {
                const sockaddr_in * sin = reinterpret_cast <const sockaddr_in *> ( this );
                ret = inet_ntop ( sa_family, &sin -> sin_addr, dest, INET6_ADDRSTRLEN );
            }
            break;

            case AF_INET6:
            {
                const sockaddr_in6 * sin6 = reinterpret_cast <const sockaddr_in6 *> ( this );
                ret = inet_ntop ( sa_family, &sin6 -> sin6_addr, dest, INET6_ADDRSTRLEN );
            }
            break;

            default:
                ret = 0;
        }
        return std::string ( ret );
    }

    uint16_t InetAddress::retrievePort ( ) const
    {
        switch ( sa_family )
        {
            case AF_INET:
                return ntohs ( reinterpret_cast <const sockaddr_in *> ( this ) -> sin_port );

            case AF_INET6:
                return ntohs ( reinterpret_cast <const sockaddr_in6 *> ( this ) -> sin6_port );

            default:
                return 0;
        }
    }
}
