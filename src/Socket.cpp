#include "Socket.hpp"

namespace NetFlux
{

    Socket::Socket ( int socket, const InetAddress & address )
        : msocket ( socket ), maddress ( address ) { }

    Socket::~Socket ( )
    {
        if ( msocket != INVALID )
        {
            ::close ( msocket );
        }
    }

    bool Socket::getAddressString ( std::string & str )
    {
        return maddress.ipToString ( str );
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
