#ifndef _TCP_SERVER_STREAM_HPP_
#define _TCP_SERVER_STREAM_HPP_

#include "../Net/Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class ServerStream : public Net::Socket
        {
        public:
            virtual ~ServerStream ( );

            inline size_t send ( const void * buf, size_t len )
            {
                return ( size_t ) ::send ( msocket, ( char * ) buf, len, 0 );
            }

            inline size_t recv ( void * buf, size_t len )
            {
                return ( size_t ) ::recv ( msocket, ( char * ) buf, len, 0 );
            }

        protected:
            ServerStream ( int sock, const InetAddress & address );

        private:
            ServerStream ( ) = delete;
        };
    }
}

#endif

