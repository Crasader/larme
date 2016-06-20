#include <cassert>

#pragma once

namespace larme {
namespace time {
    
    long timestamp() {
        return std::time(nullptr);
    }
    
    float msec() {
        struct timeval myTime;
        gettimeofday(&myTime, NULL);
        return (myTime.tv_usec * 0.000001);
    }
    
    float getRangedSecond(int range) {
        assert(range > 0);
        return (larme::time::timestamp() % range) + larme::time::msec();
    }
}
}
