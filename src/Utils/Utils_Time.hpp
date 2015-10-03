#ifndef UTILS_TIME_HPP_
#define UTILS_TIME_HPP_

#include <sys/time.h>
#include <cstdint>

namespace NetFlux
{
    namespace Utils
    {
        inline uint64_t getUtime ( )
        {
            timeval t;
            gettimeofday ( &t, nullptr );
            return uint64_t ( t.tv_sec * 1000000 ) + ( uint64_t ) t.tv_usec;
        }
    }
}

#endif
