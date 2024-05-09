#pragma once
#include <sys/time.h>
#include <chrono>

class Time {
public:
    static time_t getTime() {
        timeval now;
        gettimeofday(&now, nullptr);
        time_t ms = now.tv_sec*1000 + now.tv_usec/1000;
        return ms;
    }
};