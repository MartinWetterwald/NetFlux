#include "Notifier.hpp"

namespace NetFlux {
namespace SocketIOEvent
{
    Notifier::Notifier ( ) : first ( 0 ), last ( 0 ), running ( false ) { }

    Notifier::~Notifier ( )
    {
        while ( first )
        {
            SocketList * old = first;
            first = first -> next;
            delete old;
        }
    }

    void Notifier::startNotify ( )
    {
        running = true;

        while ( running )
        {
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

        if ( first == 0 )
        {
            first = new SocketList;
            last = first;
            first -> previous = 0;
        }
        else
        {
            last -> next = new SocketList;
            last -> next -> previous = last;
            last = last -> next;
        }

        last -> next = 0;
        sock -> notifier = this;

        return true;
    }

    bool Notifier::unsubscribe ( Net::Socket * sock )
    {
        if ( sock -> notifier != this )
        {
            return false;
        }

        SocketList * current = first;

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

            if ( current == first )
            {
                first = current -> next;
            }

            if ( current == last )
            {
                last = current -> previous;
            }

            delete current;

            return true;
        }

        return false;
    }
} }
