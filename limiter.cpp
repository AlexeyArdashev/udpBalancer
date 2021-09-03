#include "limiter.hpp"

#include <ctime>
#include <iostream>

Limiter::Limiter( int limitInOneSec ) : _limitOneSec ( limitInOneSec ),
    _counter (0), _timeLastSend(0)
{

}

bool Limiter::isExceedingLimit() const
{
    uint64_t current = time(NULL);
    if (  (current - _timeLastSend) != 0 )
        return true;
    return _counter < _limitOneSec;
}

void Limiter::msgWasSend()
{
    uint64_t current = time(NULL);
    _timeLastSend = current;
    ++_counter;
}
