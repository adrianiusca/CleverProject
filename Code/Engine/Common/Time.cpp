#include "Time.hpp"

namespace cp
{
    f32 Time::sm_delta_time;
    f32 Time::NANOSECONDS = 1000000000.0f;

    Clock::time_point Time::sm_last_time;

    float Time::delta_time()
    {
        return sm_delta_time;
    }

    void Time::start()
    {
        cout << "time started" << endl;

        sm_last_time = Clock::now();
    }

    void Time::update()
    {
        Clock::time_point new_time = Clock::now();

        nanoseconds time_difference = duration_cast<nanoseconds>(new_time - sm_last_time);

        sm_delta_time = static_cast<f32>(time_difference.count()) / NANOSECONDS;
        sm_last_time = new_time;
    }
}