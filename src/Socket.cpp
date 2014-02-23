#include "Socket.hpp"

namespace NetFlux
{
    Socket::Socket ( int socket, const InetAddress & address )
        : InetAddress ( address ), msocket ( socket ) { }

    Socket::~Socket ( )
    {
        if ( msocket != INVALID )
        {
            ::close ( msocket );
        }
    }

    bool Socket::close ( )
    {
        if ( msocket == INVALID )
        {
            return false;
        }

        ::close ( msocket );
        msocket = INVALID;

        return true;
    }

    Socket::Socket ( ) : msocket ( INVALID ) { }
}
