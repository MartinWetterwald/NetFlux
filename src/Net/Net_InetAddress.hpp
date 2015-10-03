#ifndef INET_ADDRESS_HPP_
#define INET_ADDRESS_HPP_

#include "../libs.hpp"

#include <string>
#include <cstring> // memcpy

namespace NetFlux
{
    namespace Net
    {
        class InetAddress
        {
        public:
            InetAddress ( ) = default;
            InetAddress ( const sockaddr * saddr );
            InetAddress ( const sockaddr_in * sin );
            InetAddress ( const sockaddr_in6 * sin6 );
            InetAddress ( const sockaddr_storage * sstorage );
            InetAddress ( const InetAddress & ) = default;
            virtual ~InetAddress ( ) = default;

            virtual void toString ( std::ostream & os ) const;


        protected:
            void fillAddress ( const sockaddr * psaddr );

            std::string mip;
            uint16_t mport;

            static const uint16_t PORT_LENGTH = 5;

        private:
            InetAddress & operator= ( const InetAddress & ) = delete;
        };
    }
}

std::ostream & operator<< ( std::ostream & os, const NetFlux::Net::InetAddress & addr );

#endif
