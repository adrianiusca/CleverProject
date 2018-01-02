#pragma once

#include "Util.hpp"

namespace cp
{
    class Window
    {
    public:
        explicit Window(const string& title, const ivec2& size, bool is_fullscreen = false, 
                                                                bool is_core_profile = true);

        bool create(bool is_resizable = true);

        void update();
        void release();
        
        void close();

        bool is_closing() const;
        bool is_fullscreen() const;
        bool is_core_profile() const;

        void set_size(const ivec2& size);
        void set_title(const string& title);
        void set_info(const string& info);

        const string& get_title() const;
        const ivec2& get_size() const;

        GLFWwindow* get_ptr() const;
        GLFWmonitor* get_monitor();
        
    private:
        void init_callbacks() const;

        void process_events() const;
        void process_buffers() const;

        void make_context_current() const;

        bool create_ptr();

    private:
        bool m_is_core_profile;
        bool m_is_fullscreen;

        GLFWwindow* m_ptr;

        string m_title;
        ivec2 m_size;
    };
}