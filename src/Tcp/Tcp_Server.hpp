#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "../Net/Net_Socket.hpp"

namespace NetFlux
{
    namespace Tcp
    {
        class Server : public Net::Socket
        {
        public:
            virtual ~Server ( );

            bool listen ( uint16_t port, int family = AF_UNSPEC, int backlog = 10 );

            template <class SERVERSTREAM> SERVERSTREAM * accept ( )
            {
                if ( ! * this )
                {
                    return nullptr;
                }

                sockaddr_storage address;
                socklen_t address_length = sizeof ( address );
                SOCKET sockfd = ::accept ( msocket,
                        reinterpret_cast <sockaddr *> ( &address ), &address_length );

                if ( sockfd == -1 )
                {
#ifdef DEBUG
                    perror ( "NetFlux::Tcp::Server::accept (accept)" );
#endif
                    return nullptr;
                }

                return new SERVERSTREAM ( sockfd, &address );
            }


        protected:
            Server ( ) = default;
            Server ( SOCKET sock, const InetAddress & address );

            bool timeoutEventAction ( );
        };
    }
}

#endif
