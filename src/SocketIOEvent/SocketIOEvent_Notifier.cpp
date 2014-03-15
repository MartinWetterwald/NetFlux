#include "SocketIOEvent_Notifier.hpp"
#include "SocketIOEvent_Event.hpp"
#include "../Net/Net_Socket.hpp"
#include "../Utils/Utils_Time.hpp"

#if __unix__ || __posix__ || __linux__ || __APPLE__
#include <sys/select.h>
#endif

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
            int maxfs = 0;
            uint64_t smallestTimeout = 1000000;
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
                if ( event.mtimeout > 0 && event.mtimeout < smallestTimeout )
                {
                    smallestTimeout = event.mtimeout;
                }
                current -> timeout = event.mtimeout;

                if ( event.mread )
                {
                    FD_SET ( current -> socket -> msocket, &readfds );
                }

                if ( event.mwrite )
                {
                    FD_SET ( current -> socket -> msocket, &writefds );
                }

                if ( event.mexcept )
                {
                    FD_SET ( current -> socket -> msocket, &exceptfds );
                }
            }

			t.tv_sec = ( unsigned int ) ( smallestTimeout / 1000000 );
			t.tv_usec = ( unsigned int ) ( smallestTimeout - 1000000 * ( unsigned long ) t.tv_sec );

            int ret = select ( maxfs + 1, &readfds, &writefds, &exceptfds, &t );
            if ( ret == -1 )
            {
#ifdef DEBUG
                perror ( "NetFlux::SocketIOEvent::Notifier::startNotify (select)" );
#endif
            }

            if ( ! running )
            {
                break;
            }

            SocketList * current = mpcurrent = mpfirst;
            while ( current )
            {
                if ( current -> timeout )
                {
                    if ( Utils::getUtime ( ) > current -> lastActive + current -> timeout )
                    {
                        current -> socket -> timeoutEventAction ( );
                    }
                }

                if ( ret != 0 )
                {
                    if ( FD_ISSET ( current -> socket -> msocket, &readfds ) )
                    {
                        current -> socket -> readEventAction ( );
                        current -> lastActive = Utils::getUtime ( );
                        if ( current != mpcurrent )
                        {
                            current = mpcurrent;
                            continue;
                        }
                    }

                    if ( FD_ISSET ( current -> socket -> msocket, &writefds ) )
                    {
                        current -> socket -> writeEventAction ( );
                        current -> lastActive = Utils::getUtime ( );
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
        created -> lastActive = Utils::getUtime ( );

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
