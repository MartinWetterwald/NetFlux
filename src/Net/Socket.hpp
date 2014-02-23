#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include "InetAddress.hpp"

namespace NetFlux
{
    namespace SocketIOEvent
    {
        class Notifier;
    }

    namespace Net
    {
        class Socket : public InetAddress
        {
        public:
            Socket ( int socket, const InetAddress & address );
            virtual ~Socket ( );

            inline operator bool ( ) const
            {
                return ( msocket != INVALID );
            }

            bool close ( );


        protected:
            Socket ( );
            int msocket;

            SocketIOEvent::Notifier * notifier;
            static const int INVALID = -1;

            friend class SocketIOEvent::Notifier;
        };
    }
}

#endif
