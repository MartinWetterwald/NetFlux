#ifndef _SOCKET_IO_EVENT_SUBSCRIBER_HPP_
#define _SOCKET_IO_EVENT_SUBSCRIBER_HPP_

#include "Event.hpp"

namespace NetFlux
{
    namespace SocketIOEvent
    {
        class Subscriber
        {
        public:
            Subscriber ( ) = default;
            virtual ~Subscriber ( );

        protected:
            virtual void readEventAction ( ) = 0;
            virtual void writeEventAction ( ) = 0;
            virtual void exceptEventAction ( ) = 0;

            virtual void chooseSubscription ( Event & ) = 0;
        };
    }
}

#endif
