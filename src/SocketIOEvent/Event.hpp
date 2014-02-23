#ifndef _SOCKET_IO_EVENT_EVENT_HPP_
#define _SOCKET_IO_EVENT_EVENT_HPP_

#include "../Net/Socket.hpp"

namespace NetFlux
{
    namespace SocketIOEvent
    {
        class Event
        {
        public:
            Event ( ) : read ( false ), write ( false ), except ( false ) { }

            inline void setRead ( )
            {
                read = true;
            }

            inline void setWrite ( )
            {
                write = true;
            }

            inline void setExcept ( )
            {
                except = true;
            }

        protected:
            bool read;
            bool write;
            bool except;

            friend class Notifier;
        };
    }
}
#endif
