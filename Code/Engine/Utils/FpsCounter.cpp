#include "FpsCounter.hpp"
#include "Engine/Common/Time.hpp"

namespace cp
{
    u32 FpsCounter::sm_frames;
	f32 FpsCounter::sm_frames_time;

    void FpsCounter::update()
    {
        ++sm_frames;

        sm_frames_time += Time::delta_time();

        if (sm_frames_time >= 1.0f)
        {
            print();

            sm_frames_time = 0.0f;
            sm_frames = 0;
        }
    }

    void FpsCounter::print()
    {
        cout << "fps: " << sm_frames << " delta: " << Time::delta_time() << endl;
    }

    u32 FpsCounter::get_frames()
    {
        return sm_frames;
    }
}