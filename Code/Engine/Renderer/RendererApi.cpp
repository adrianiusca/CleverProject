#include "RendererApi.hpp"

namespace cp
{
    ivec2 RendererApi::sm_version;

    bool RendererApi::init()
    {
        if (glewInit() != GLEW_OK)
        {
            cout << "[GLEW] api failed" << endl;

            return false;
        }

        cout << "[GLEW] api succeed" << endl;
        cout << "[GLEW] api Version: " << glewGetString(GLEW_VERSION) << endl;

        glGetIntegerv(GL_MAJOR_VERSION, &sm_version.x);
	    glGetIntegerv(GL_MINOR_VERSION, &sm_version.y);

        cout << "[GL] api version: " << sm_version.x << "."
                                     << sm_version.y << endl;

        cout << "[GLSL] api version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

        return true;
    }

    void RendererApi::enable_experimental()
    {
        glewExperimental = true;
    }

    const ivec2& RendererApi::get_version()
    {
        return sm_version;
    }
}