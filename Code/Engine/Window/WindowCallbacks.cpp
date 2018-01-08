#include "WindowCallbacks.hpp"
#include "Engine/Common/Input.hpp"

namespace cp
{
    void WindowCallbacks::resize(GLFWwindow* ptr, i32 width, i32 height)
    {
    }

    void WindowCallbacks::keyboard_keys(GLFWwindow* ptr, i32 key, i32 code, i32 action, i32 mods)
    {
        if (action == GLFW_PRESS)
		{
			Input::set_key(key, true);
		}
		else if (action == GLFW_RELEASE)
		{
			Input::set_key(key, false);
		}
    }

    void WindowCallbacks::mouse_clicks(GLFWwindow* ptr, i32 button, i32 action, i32 mods)
    {
        if (action == GLFW_PRESS)
		{
			Input::set_click(button, true);
		}
		else if (action == GLFW_RELEASE)
		{
			Input::set_click(button, false);
		}
    }

    void WindowCallbacks::mouse_position(GLFWwindow* ptr, f64 x, f64 y)
    {
        Input::set_mouse_position(vec2(x, y));
    }
}