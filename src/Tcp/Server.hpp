#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "../Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class Server : public Socket
        {
        public:
            virtual ~Server ( );

            bool listen ( uint16_t port, int backlog = 10 );

            template <class SERVERSTREAM> SERVERSTREAM * accept ( )
            {
                if ( ! * this )
                {
                    return 0;
                }

                sockaddr address;
                socklen_t address_length = sizeof ( sockaddr );
                int sockfd = ::accept ( msocket, &address, &address_length );

                if ( sockfd == -1 )
                {
#ifdef DEBUG
                    perror ( "NetFlux::Tcp::Server::accept (accept)" );
#endif
                    return 0;
                }

                return new SERVERSTREAM ( sockfd, address );
            }

        protected:
            Server ( );
            Server ( int sock, const InetAddress & address );
        };
    }
}

#endif
