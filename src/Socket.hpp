#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include "InetAddress.hpp"

namespace NetFlux
{
    class Socket
    {
    public:
        Socket ( int socket, const InetAddress & address );
        virtual ~Socket ( );

        inline operator bool ( ) const
        {
            return ( msocket != INVALID );
        }

        bool getAddress ( std::string & str );
        bool close ( );


    protected:
        Socket ( );

        int msocket;
        InetAddress maddress;

        static const int INVALID = -1;
    };
}

#endif
