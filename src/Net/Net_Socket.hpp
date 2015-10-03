#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "Net_InetAddress.hpp"
#include "../SocketIOEvent/SocketIOEvent_Subscriber.hpp"
#include "../SocketIOEvent/SocketIOEvent_Notifier.hpp"

namespace NetFlux
{
    namespace Net
    {
        class Socket : public InetAddress, public SocketIOEvent::Subscriber
        {
        public:
            Socket ( SOCKET socket, const InetAddress & address );
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
            static const SOCKET INVALID = ( SOCKET ) -1;

            friend class SocketIOEvent::Notifier;


        private:
            Socket ( const Socket & ) = delete;
            Socket & operator= ( const Socket & ) = delete;
        };
    }
}

#endif
