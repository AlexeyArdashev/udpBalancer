#pragma once

#include <stdint.h>

class Limiter
{

public:
    explicit Limiter ( int limitInOneSec );
    bool isExceedingLimit () const;
    void msgWasSend();

private:
    const int _limitOneSec;
    int _counter;
    uint64_t _timeLastSend;
};

