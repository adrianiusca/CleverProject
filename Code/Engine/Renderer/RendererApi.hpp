#pragma once

#include "Util.hpp"

namespace cp
{
    class RendererApi
    {
    public:
        static bool init();
        static void enable_experimental();

        static const ivec2& get_version();

    private:    
        RendererApi() = delete;
        RendererApi(const RendererApi &) = delete;

        RendererApi &operator=(const RendererApi &) = delete;

    private:
        static ivec2 sm_version;
    };
}