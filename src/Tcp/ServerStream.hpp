#ifndef _TCP_SERVER_STREAM_HPP_
#define _TCP_SERVER_STREAM_HPP_

#include "../Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class ServerStream : public Socket
        {
        public:
            virtual ~ServerStream ( );

        protected:
            ServerStream ( int sock, const InetAddress & address );
        };
    }
}

#endif

