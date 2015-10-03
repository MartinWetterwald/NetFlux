#ifndef SOCKET_IO_EVENT_SUBSCRIBER_HPP_
#define SOCKET_IO_EVENT_SUBSCRIBER_HPP_

#include "SocketIOEvent_Event.hpp"

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
            virtual bool readEventAction ( ) = 0;
            virtual bool writeEventAction ( ) = 0;
            virtual bool exceptEventAction ( ) = 0;
            virtual bool timeoutEventAction ( ) = 0;

            virtual void chooseSubscription ( Event & ) = 0;
        };
    }
}

#endif
