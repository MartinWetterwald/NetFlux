#include "Socket.hpp"
#include "../SocketIOEvent/Notifier.hpp"

namespace NetFlux {
namespace Net
{
    Socket::Socket ( int socket, const InetAddress & address )
        : InetAddress ( address ), msocket ( socket ), notifier ( 0 ) { }

    Socket::~Socket ( )
    {
        if ( msocket != INVALID )
        {
            if ( notifier )
            {
                notifier -> unsubscribe ( this );
            }

            ::close ( msocket );
        }
    }

    bool Socket::close ( )
    {
        if ( msocket == INVALID )
        {
            return false;
        }

        if ( notifier )
        {
            notifier -> unsubscribe ( this );
        }

        ::close ( msocket );
        msocket = INVALID;

        return true;
    }

    Socket::Socket ( ) : msocket ( INVALID ), notifier ( 0 ) { }
} }