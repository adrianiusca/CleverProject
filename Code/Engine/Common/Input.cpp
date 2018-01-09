#include "Input.hpp"

namespace cp
{
    array<bool, KEYS_SIZE> Input::sm_keys;
    array<bool, CLICKS_SIZE> Input::sm_clicks;

    vec2 Input::sm_mouse_position;

    bool Input::is_key_down(i32 key, bool is_one_time)
    {
        const bool is_down = sm_keys.at(key);

		if (is_down && is_one_time)
		{
			if (key != GLFW_KEY_ESCAPE &&
                key != GLFW_KEY_SPACE)
			{
				cout << "key " << glfwGetKeyName(key, 0) << " was pressed" << endl;
			}

			sm_keys.at(key) = false;
		}

		return is_down;
    }

    bool Input::is_click_down(i32 button, bool is_one_time)
    {
        const bool is_down = sm_clicks.at(button);

		if (is_down && is_one_time)
		{
			cout << "mouse button " << button << " was pressed at position " << static_cast<int>(sm_mouse_position.x) << " " 
																			 << static_cast<int>(sm_mouse_position.y) << endl;

			sm_clicks.at(button) = false;
		}

		return is_down;
    }

    void Input::set_key(i32 index, bool value)
    {
        sm_keys.at(index) = value;
    }

    void Input::set_click(i32 index, bool value)
    {
        sm_clicks.at(index) = value;
    }

    void Input::set_mouse_position(const vec2& position)
    {
        sm_mouse_position = position;
    }

    const vec2& Input::get_mouse_position()
    {
        return sm_mouse_position;
    }
}