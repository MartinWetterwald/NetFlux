#include "TcpServer.hpp"

namespace NetFlux
{
    TcpServer::TcpServer ( )
    {
    }

    TcpServer::~TcpServer ( )
    {
    }

    bool TcpServer::open ( unsigned short port )
    {
        if ( msocket )
        {
            return false;
        }

        msocket = socket ( AF_INET, SOCK_DGRAM, 0 );
        if ( ! msocket )
        {
            return false;
        }

        struct sockaddr_in sin;
        sin.sin_family = AF_INET;
        sin.sin_port = htons ( port );
        sin.sin_addr.s_addr = htonl ( INADDR_ANY );

        int ret;
        ret = bind ( msocket, ( struct sockaddr * ) &sin, sizeof ( struct sockaddr_in ) );
        if ( ret == -1 )
        {
            close ( );
            return false;
        }

        ret = listen ( msocket, 10 );
        if ( ret == -1 )
        {
            close ( );
            return false;
        }

        return true;
    }
}
