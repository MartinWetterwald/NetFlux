#include "Socket.hpp"

namespace NetFlux
{
    Socket::Socket ( ) : msocket ( INVALID )
    {
    }

    Socket::Socket ( int socket ) : msocket ( socket )
    {
    }

    Socket::~Socket ( )
    {
        if ( msocket )
        {
            ::close ( msocket );
        }
    }

    bool Socket::close ( )
    {
        if ( ! msocket )
        {
            return false;
        }

        ::close ( msocket );
        msocket = INVALID;

        return true;
    }
}
