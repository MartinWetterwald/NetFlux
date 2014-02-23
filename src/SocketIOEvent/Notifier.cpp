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

    void Notifier::subscribe ( Net::Socket * sock )
    {

        sock -> notifier = this;
    }

    void Notifier::unsubscribe ( Net::Socket * sock )
    {
        sock -> notifier = 0;
    }
} }
