#include "Socket.hpp"

namespace NetFlux
{
    Socket::Socket ( ) : msocket ( INVALID )
    {
    }

    Socket::Socket ( int socket, const struct sockaddr & sin )
        : msocket ( socket ), msin ( sin )
    {
    }

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
}
