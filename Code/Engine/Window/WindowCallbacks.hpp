#pragma once

#include "Util.hpp"

namespace cp
{
    class WindowCallbacks
    {
    public:
        static void resize(GLFWwindow* ptr, i32 width, i32 height);

		static void keyboard_keys(GLFWwindow* ptr, i32 key, i32 code, i32 action, i32 mods);

		static void mouse_clicks(GLFWwindow* ptr, i32 button, i32 action, i32 mods);
		static void mouse_position(GLFWwindow* ptr, f64 x, f64 y);

    private:
        WindowCallbacks() = delete;
        WindowCallbacks(const WindowCallbacks &) = delete;

        WindowCallbacks &operator=(const WindowCallbacks &) = delete;
    };
}