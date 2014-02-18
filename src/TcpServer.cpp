#include "TcpServer.hpp"

namespace NetFlux
{
    TcpServer::TcpServer ( )
    {
    }

    TcpServer::~TcpServer ( )
    {
    }

    bool TcpServer::open ( uint16_t port, uint32_t interface, int backlog )
    {
        if ( msocket != INVALID )
        {
            return false;
        }

        msocket = socket ( AF_INET, SOCK_STREAM, 0 );
        if ( msocket == INVALID )
        {
            return false;
        }

        msin.sin_family = AF_INET;
        msin.sin_port = htons ( port );
        msin.sin_addr.s_addr = htonl ( interface );

        int ret;
        ret = bind ( msocket, ( struct sockaddr * ) &msin, sizeof ( msin ) );
        if ( ret == -1 )
        {
            close ( );
            return false;
        }

        ret = listen ( msocket, backlog );
        if ( ret == -1 )
        {
            close ( );
            return false;
        }

        return true;
    }
}
