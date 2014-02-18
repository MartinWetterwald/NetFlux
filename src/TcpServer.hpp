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

        bool open ( uint16_t port, uint32_t interface = INADDR_ANY, int backlog = 10 );
    };
}

#endif
