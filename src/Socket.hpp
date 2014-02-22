#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include "libs.hpp"
#include "InetAddress.hpp"

namespace NetFlux
{
    class Socket
    {
    public:
        Socket ( );
        Socket ( int socket, const InetAddress & address );
        virtual ~Socket ( );

        inline operator bool ( ) const
        {
            return ( msocket != INVALID );
        }

        bool getAddressString ( std::string & str );
        bool close ( );


    protected:
        int msocket;
        InetAddress maddress;

        static const int INVALID = -1;
    };
}

#endif
