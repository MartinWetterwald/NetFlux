#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "Socket.hpp"

namespace NetFlux
{
    class TcpServer : public Socket
    {
    public:
        TcpServer ( );
        virtual ~TcpServer ( );

        bool listen ( uint16_t port, int backlog = 10 );
    };
}

#endif
