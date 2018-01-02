#include "WindowApi.hpp"
#include "Util.hpp"

namespace cp
{
    bool WindowApi::init()
    {
        if (glfwInit() != GLFW_TRUE)
        {
            std::cout << "[GLFW] api failed" << std::endl;

            return false;
        }

        std::cout << "[GLFW] api succeed" << std::endl;

        ivec3 version;

        glfwGetVersion(&version.x, &version.y, &version.z);

        std::cout << "[GLFW] api version: " << version.x << "." 
                                            << version.y << " revision " 
                                            << version.z << std::endl;

        return true;
    }

    void WindowApi::release()
    {
        std::cout << "[GLFW] api released" << std::endl;

        glfwTerminate();
    }

    void WindowApi::enable_core_profile()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        std::cout << "[GLFW] opengl core profile (version >= 3.2)" << std::endl;
    }

    void WindowApi::enable_fixed_size()
    {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
}