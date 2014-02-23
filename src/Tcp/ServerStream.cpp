#include "ServerStream.hpp"

namespace NetFlux {
namespace Tcp
{
    ServerStream::~ServerStream ( ) { }


    ServerStream::ServerStream ( int socket, const InetAddress & address )
        : Socket ( socket, address ) { }

} }
