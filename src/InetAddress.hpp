#ifndef _INET_ADDRESS_HPP_
#define _INET_ADDRESS_HPP_

#include "libs.hpp"

#include <string>

namespace NetFlux
{
    class InetAddress : public sockaddr
    {
    public:
        InetAddress ( );
        InetAddress ( const sockaddr & saddr );
        InetAddress ( const sockaddr_in & sin );
        InetAddress ( const sockaddr_in6 & sin6 );

        bool ipToString ( std::string & str ) const;
    };
}

#endif
