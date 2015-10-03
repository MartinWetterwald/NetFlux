#ifndef TCP_CLIENT_HPP_
#define TCP_CLIENT_HPP_

#include "../Net/Net_Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class Client : public Net::Socket
        {
        public:
            virtual ~Client ( );

            bool connectTo ( const std::string & host, uint16_t port );

            inline ssize_t send ( const void * buf, size_t len )
            {
                return ::send ( msocket, ( char * ) buf, len, MSG_NOSIGNAL );
            }

            inline ssize_t recv ( void * buf, size_t len )
            {
                return ::recv ( msocket, ( char * ) buf, len, MSG_NOSIGNAL );
            }

        protected:
            Client ( ) = default;
            Client ( SOCKET sock, const InetAddress & address );
        };
    }
}

#endif
