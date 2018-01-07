#include "WindowApi.hpp"
#include "Util.hpp"

namespace cp
{
    bool WindowApi::init()
    {
        if (glfwInit() != GLFW_TRUE)
        {
            cout << "[GLFW] api failed" << endl;

            return false;
        }

        cout << "[GLFW] api succeed" << endl;

        ivec3 version;

        glfwGetVersion(&version.x, &version.y, &version.z);

        cout << "[GLFW] api version: " << version.x << "." 
                                            << version.y << " revision " 
                                            << version.z << endl;

        return true;
    }

    void WindowApi::release()
    {
        cout << "[GLFW] api released" << endl;

        glfwTerminate();
    }

    void WindowApi::enable_core_profile()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        cout << "[GLFW] opengl core profile (version >= 3.2)" << endl;
    }

    void WindowApi::enable_fixed_size()
    {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
}