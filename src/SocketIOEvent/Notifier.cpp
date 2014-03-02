#include "Notifier.hpp"
#include "Event.hpp"
#include "../Net/Socket.hpp"

#include <sys/select.h>

namespace NetFlux {
namespace SocketIOEvent
{
    Notifier::Notifier ( ) :
        mpfirst ( nullptr ), mplast ( nullptr ), mpcurrent ( nullptr ), running ( false )
    {
    }

    Notifier::~Notifier ( )
    {
        while ( mpfirst )
        {
            mplast = mpfirst;
            mpfirst = mpfirst -> next;
            mplast -> socket -> notifier = nullptr;
            delete mplast;
        }
    }

    void Notifier::startNotify ( )
    {
        running = true;

        while ( running )
        {
            timeval t;
            t.tv_sec = 1;
            t.tv_usec = 0;
            int maxfs = 0;
            fd_set readfds, writefds, exceptfds;
            FD_ZERO ( &readfds );
            FD_ZERO ( &writefds );
            FD_ZERO ( &exceptfds );

            for ( SocketList * current = mpfirst ; current != 0 ; current = current -> next )
            {
                if ( current -> socket -> msocket > maxfs )
                {
                    maxfs = current -> socket -> msocket;
                }

                Event event;
                current -> socket -> chooseSubscription ( event );

                if ( event.read )
                {
                    FD_SET ( current -> socket -> msocket, &readfds );
                }

                if ( event.write )
                {
                    FD_SET ( current -> socket -> msocket, &writefds );
                }

                if ( event.except )
                {
                    FD_SET ( current -> socket -> msocket, &exceptfds );
                }
            }

            int ret = select ( maxfs + 1, &readfds, &writefds, &exceptfds, &t );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::SocketIOEvent::Notifier::startNotify (select)" );
#endif
            }
            else if ( ret == 0 )
            {
                continue;
            }

            if ( ! running )
            {
                break;
            }

            SocketList * current = mpcurrent = mpfirst;
            while ( current )
            {
                if ( FD_ISSET ( current -> socket -> msocket, &readfds ) )
                {
                    current -> socket -> readEventAction ( );
                    if ( current != mpcurrent )
                    {
                        current = mpcurrent;
                        continue;
                    }
                }

                if ( FD_ISSET ( current -> socket -> msocket, &writefds ) )
                {
                    current -> socket -> writeEventAction ( );
                    if ( current != mpcurrent )
                    {
                        current = mpcurrent;
                        continue;
                    }
                }

                if ( FD_ISSET ( current -> socket -> msocket, &exceptfds ) )
                {
                    current -> socket -> exceptEventAction ( );
                    if ( current != mpcurrent )
                    {
                        current = mpcurrent;
                        continue;
                    }
                }

                current = mpcurrent = current -> next;
            }
        }
    }

    bool Notifier::subscribe ( Net::Socket * sock )
    {
        if ( sock -> msocket == Net::Socket::INVALID )
        {
            return false;
        }

        if ( sock -> notifier )
        {
            if ( sock -> notifier == this )
            {
                return true;
            }
            sock -> notifier -> unsubscribe ( sock );
        }

        SocketList * created = new SocketList;
        if ( mpfirst == nullptr )
        {
            mpfirst = created;
            mplast = mpfirst;
            mpfirst -> previous = nullptr;
        }
        else
        {
            mplast -> next = created;
            mplast -> next -> previous = mplast;
            mplast = mplast -> next;
        }

        mplast -> next = nullptr;
        sock -> notifier = this;
        created -> socket = sock;

        return true;
    }

    bool Notifier::unsubscribe ( Net::Socket * sock )
    {
        if ( sock -> notifier != this )
        {
            return false;
        }

        SocketList * current = mpfirst;

        while ( current )
        {
            if ( current -> socket != sock )
            {
                current = current -> next;
                continue;
            }

            if ( current -> previous )
            {
                current -> previous -> next = current -> next;
            }

            if ( current -> next )
            {
                current -> next -> previous = current -> previous;
            }

            if ( current == mpfirst )
            {
                mpfirst = current -> next;
            }

            if ( current == mplast )
            {
                mplast = current -> previous;
            }

            if ( current == mpcurrent )
            {
                mpcurrent = mpcurrent -> next;
            }

            sock -> notifier = nullptr;
            delete current;

            return true;
        }

        return false;
    }
} }
