#ifndef _SOCKET_IO_EVENT_NOTIFIER_HPP_
#define _SOCKET_IO_EVENT_NOTIFIER_HPP_

#include "../Net/Socket.hpp"

namespace NetFlux
{
    namespace SocketIOEvent
    {
        class Notifier
        {
        public:
            Notifier ( );
            virtual ~Notifier ( );

            bool subscribe ( Net::Socket * sock );
            bool unsubscribe ( Net::Socket * sock );

            void startNotify ( );

            inline void stopNotify ( )
            {
                running = false;
            }

        protected:
            struct SocketList
            {
                SocketList * previous;
                Net::Socket * socket;
                SocketList * next;
            };

            SocketList * first;
            SocketList * last;

            bool running;
        };
    }
}

#endif
