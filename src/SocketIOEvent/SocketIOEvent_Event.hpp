#ifndef _SOCKET_IO_EVENT_EVENT_HPP_
#define _SOCKET_IO_EVENT_EVENT_HPP_

#include <cstdint>
#include <ctime>

namespace NetFlux
{
    namespace SocketIOEvent
    {
        class Event
        {
        public:
            Event ( ) :
                mread ( false ),
                mwrite ( false ),
                mexcept ( false ),
                mtimeout ( 0 ) { }

            inline void setRead ( )
            {
                mread = true;
            }

            inline void setWrite ( )
            {
                mwrite = true;
            }

            inline void setExcept ( )
            {
                mexcept = true;
            }

            inline void setTimeout ( uint64_t timeout )
            {
                mtimeout = timeout;
            }


        protected:
            bool mread;
            bool mwrite;
            bool mexcept;
            uint64_t mtimeout;

            static const uint32_t DEFAULT_TIMEOUT = 1000000;

            friend class Notifier;
        };
    }
}
#endif
