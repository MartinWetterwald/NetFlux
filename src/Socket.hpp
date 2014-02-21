#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include "libs.hpp"

namespace NetFlux
{
    class Socket
    {
    public:
        Socket ( );
        Socket ( int socket, const struct sockaddr & sin );
        virtual ~Socket ( );

        inline operator bool ( ) const
        {
            return ( msocket != INVALID );
        }

        bool close ( );


    protected:
        int msocket;
        struct sockaddr msin;

        static const int INVALID = -1;
    };
}

#endif
