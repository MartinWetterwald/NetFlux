#include "Net_InetAddress.hpp"
#include <sstream>

namespace NetFlux {
namespace Net
{
    InetAddress::InetAddress ( const sockaddr & saddr )
    {
        fillAddress ( &saddr );
    }

    InetAddress::InetAddress ( const sockaddr_in & sin )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin ) ) { }


    InetAddress::InetAddress ( const sockaddr_in6 & sin6 )
        : InetAddress ( reinterpret_cast <const sockaddr &> ( sin6 ) ) { }

    InetAddress::~InetAddress ( ) { }


    void InetAddress::fillAddress ( const sockaddr * psaddr )
    {
        assert ( psaddr != nullptr );

        char dest [ INET6_ADDRSTRLEN ];

        switch ( psaddr -> sa_family )
        {
            case AF_INET:
            {
                const sockaddr_in * sin = reinterpret_cast <const sockaddr_in *> ( &psaddr );
                mip = inet_ntop ( psaddr -> sa_family, &sin -> sin_addr, dest, INET6_ADDRSTRLEN );
                mport = ntohs ( reinterpret_cast <const sockaddr_in *> ( psaddr ) -> sin_port );
            }
            break;

            case AF_INET6:
            {
                const sockaddr_in6 * sin6 = reinterpret_cast <const sockaddr_in6 *> ( psaddr );
                mip = inet_ntop ( psaddr -> sa_family, &sin6 -> sin6_addr, dest, INET6_ADDRSTRLEN );
                mport = ntohs ( reinterpret_cast <const sockaddr_in6 *> ( psaddr ) -> sin6_port );
            }
            break;

            default:
                assert ( false );
        }
    }

    void InetAddress::toString ( std::ostream & os ) const
    {
        os << mip << ":" << mport;
    }
} }


std::ostream & operator<< ( std::ostream & os, const NetFlux::Net::InetAddress & addr )
{
    addr.toString ( os );
    return os;
}
