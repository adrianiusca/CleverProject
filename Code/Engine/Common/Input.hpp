#pragma once

#include "Util.hpp"

namespace cp
{
    #define CLICKS_SIZE 10
    #define KEYS_SIZE 350

    class Input
    {
    public:
        static bool is_key_down(i32 key, bool is_one_time = false);
		static bool is_click_down(i32 button, bool is_one_time = false);

		static void set_key(i32 index, bool value);
		static void set_click(i32 index, bool value);

		static void set_mouse_position(const vec2& position);
		static const vec2& get_mouse_position();

    private:
        static array<bool, KEYS_SIZE> sm_keys;
        static array<bool, CLICKS_SIZE> sm_clicks;

        static vec2 sm_mouse_position;   
    };
}