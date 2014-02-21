#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "Socket.hpp"

namespace NetFlux
{
    class TcpServer : public Socket
    {
    public:
        static TcpServer * Create ( uint16_t port );
        virtual ~TcpServer ( );

        bool listen ( int backlog = 10 );

    protected:
        TcpServer ( int sock, const struct sockaddr & sin );
    };
}

#endif
