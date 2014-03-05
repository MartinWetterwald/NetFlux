#ifndef _TCP_CLIENT_HPP_
#define _TCP_CLIENT_HPP_

#include "../Net/Socket.hpp"

namespace NetFlux
{
    namespace Tcp
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
