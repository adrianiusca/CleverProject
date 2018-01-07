#include "Window.hpp"
#include "WindowApi.hpp"

namespace cp
{
    Window::Window(const string& title, const ivec2& size, bool is_fullscreen, bool is_core_profile)
        : m_is_core_profile(is_core_profile)
        , m_is_fullscreen(is_fullscreen)
        , m_ptr(nullptr)
        , m_title(title)
        , m_size(size)
    {
    }

    bool Window::create(bool is_resizable)
    {
        if (m_size == ivec2())
        {
            cout << "window size is zero" << endl;

            return false;
        }

        if (!WindowApi::init())
        {
            return false;
        }

        if (is_resizable)
        {
            WindowApi::enable_fixed_size();
        }

        if (m_is_core_profile)
        {
            WindowApi::enable_core_profile();
        }

        if (!create_ptr())
        {
            release();

            return false;
        }

        make_context_current();

        return true;
    }

    bool Window::create_ptr()
    {
        m_ptr = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), get_monitor(), nullptr);

        if (!m_ptr)
        {
            cout << "[GLFW] pointer is null" << endl;

            return false;
        }

        cout << "[GLFW] pointer is ok" << endl;

        return true;
    }

    void Window::make_context_current() const
    {
        cout << "[GLFW] set context as current" << endl;

        glfwMakeContextCurrent(m_ptr);
    }

    bool Window::is_closing() const
    {
        if (glfwWindowShouldClose(m_ptr) == GLFW_TRUE)
        {
            cout << "The Window is closing" << endl;

            return true;
        }

        return false;
    }

    void Window::set_size(const ivec2& size)
    {
        m_size = size;
    }

    const string& Window::get_title() const
    {
        return m_title;
    }

    const ivec2& Window::get_size() const
    {
        return m_size;
    }

    GLFWwindow* Window::get_ptr() const
    {
        return m_ptr;
    }

    GLFWmonitor* Window::get_monitor()
    {
        GLFWmonitor* monitor = nullptr;

        if (m_is_fullscreen)
        {
            monitor = glfwGetPrimaryMonitor();

            if (monitor)
            {
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                if (mode)
                {
                    m_size = ivec2(mode->width, mode->height);
                }
            }
        }

        return monitor;
    }

    void Window::update()
    {
        process_events();
        process_buffers();
    }

    bool Window::is_fullscreen() const
    {
        return m_is_fullscreen;
    }

    void Window::process_events() const
    {
        glfwPollEvents();
    }

    void Window::process_buffers() const
    {
        glfwSwapBuffers(m_ptr);
    }

    void Window::release()
    {
        glfwDestroyWindow(m_ptr);
    }

    void Window::set_info(const string& info)
    {
        glfwSetWindowTitle(m_ptr, (m_title + info).c_str());
    }

    void Window::close()
    {
        glfwSetWindowShouldClose(m_ptr, true);
    }
}