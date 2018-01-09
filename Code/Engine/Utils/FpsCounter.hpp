#pragma once

#include "Util.hpp"

namespace cp
{
    class FpsCounter
    {
    public:
        static void update();
        static void print();

        static u32 get_frames();

    private:
        FpsCounter() = delete;
        FpsCounter(const FpsCounter &) = delete;

        FpsCounter &operator=(const FpsCounter &) = delete;

    private:
        static f32 sm_frames_time;
        static u32 sm_frames;
    };
}