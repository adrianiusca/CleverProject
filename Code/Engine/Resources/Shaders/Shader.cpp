#include "Shader.hpp"

namespace cp
{
    Shader::Shader(i32 id, const shared_ptr<File>& file, i32 type)
        : DynamicResource(id, ResourceTypes::SHADER, file)
        , m_shader_id(0)
        , m_shader_type(type)
    {
    }

    i32 Shader::get_shader_type() const
    {
        return m_shader_type;
    }

    i32 Shader::get_shader_id() const
    {
        return m_shader_id;
    }

    bool Shader::create()
    {
        assert(m_shader_type == GL_VERTEX_SHADER ||
               m_shader_type == GL_FRAGMENT_SHADER);

        if (!m_file)
        {
            cout << "do not have a file for the shader " << m_id << endl;

            return false;
        }

        m_shader_id = glCreateShader(m_shader_type);

        if (!m_shader_id)
        {
            return false;
        }

        const string& source = m_file->get_data();
        const char* code = source.c_str();

        glShaderSource(m_shader_id, 1, &code, nullptr);

        compile();

        return compilation_status();
    }

    bool Shader::release()
    {
        if (!m_shader_id)
        {
            return false;
        }

        glDeleteShader(m_shader_id);

        m_shader_id = 0;

        return true;
    }

    bool Shader::compilation_status() const
    {
        int result;

        glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &result);

        if (!result)
        {
            int length;

            glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &length);

            if (length)
            {
                vector<char> error(length);
                glGetShaderInfoLog(m_shader_id, length, nullptr, error.data());

                cout << "shader " << m_file->get_filename() << " has a problem:" << endl;

                fprintf(stdout, "%s\n", error.data());
            }

            return false;
        }

        cout << "shader " << m_file->get_filename() << " was compiled successfully" << endl;

        return true;
    }

    void Shader::compile() const
    {
        glCompileShader(m_shader_id);
    }
}