#pragma once

namespace cp
{
    class WindowApi
    {
    public:
        static bool init();
        static void release();

        static void enable_core_profile();
        static void enable_fixed_size();

    private:
        WindowApi() = delete;
        WindowApi(const WindowApi &) = delete;

        WindowApi &operator=(const WindowApi &) = delete;
    };
}