#ifndef _UDP_CLIENT_HPP_
#define _UDP_CLIENT_HPP_

#include "../Net/Net_Socket.hpp"

namespace NetFlux
{
    namespace Udp
    {
        class Client : public Net::Socket
        {
        public:
            virtual ~Client ( );

            bool connectTo ( const std::string & host, uint16_t port );

        protected:
            Client ( ) = default;
            Client ( SOCKET sock, const InetAddress & address );
        };
    }
}

#endif

