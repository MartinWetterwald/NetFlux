#ifndef SOCKET_IO_EVENT_NOTIFIER_HPP_
#define SOCKET_IO_EVENT_NOTIFIER_HPP_

#include <cstdint>

namespace NetFlux
{
    namespace Net
    {
        class Socket;
    }

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
                uint64_t lastActive;
                uint64_t timeout;
                SocketList * next;
            };

            SocketList * mpfirst;
            SocketList * mplast;

            SocketList * mpcurrent;

            bool running;

        private:
            Notifier ( const Notifier & ) = delete;
            Notifier & operator= ( const Notifier & ) = delete;
        };
    }
}

#endif
