#pragma once

#include "Util.hpp"

namespace cp
{
    typedef high_resolution_clock Clock;

    class Time
    {
    public:
        static void start();
        static void update();

        static f32 delta_time();

    private:
        static f32 NANOSECONDS;

        static Clock::time_point sm_last_time;
        static f32 sm_delta_time;
    };
}