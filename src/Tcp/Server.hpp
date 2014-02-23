#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "../Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class Server : public Socket
        {
        public:
            static Server * Create ( uint16_t port );
            virtual ~Server ( );

            bool listen ( int backlog = 10 );

        protected:
            Server ( int sock, const InetAddress & address );
        };
    }
}

#endif
