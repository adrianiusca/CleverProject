#include "Program.hpp"

namespace cp
{
    Program::Program(int id)
        : DynamicResource(id, ResourceTypes::PROGRAM)
        , m_program_id(0)
    {
    }

    void Program::add_shaders(const Shaders& shaders)
    {
        for (auto shader : shaders)
        {
            add_shader(shader);
        }
    }

    void Program::add_shader(std::shared_ptr<Shader> shader)
    {
        if (shader)
        {
            shader->load();

            m_shaders.push_back(shader);
        }
    }

    void Program::remove_shader(int type)
    {
        auto func = [type](auto shader)
        {
            return shader->get_shader_type() == type;
        };

        auto it = find_if(m_shaders.begin(), m_shaders.end(), func);

        if (it != m_shaders.end())
        {
            (*it)->unload();
            
            m_shaders.erase(it);
        }
    }

    void Program::add_uniform(ShaderUniforms uniform, const std::string& name)
    {
        int value = get_uniform_location(name);

        if (m_uniforms.find(uniform) == m_uniforms.end())
        {
            m_uniforms[uniform] = value;
        }
        else
        {
            cout << "uniform " << uniform << " already exists" << endl;
        }
    }

    void Program::add_attribute(VertexAttributes attribute, const std::string& name)
    {
        int value = get_attribute_location(name);

        if (m_attributes.find(attribute) == m_attributes.end())
        {
            m_attributes[attribute] = value;
        }
        else
        {
            cout << "attribute " << attribute << " already exists" << endl;
        }
    }

    void Program::set_mat4(ShaderUniforms uniform, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(m_uniforms.at(uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Program::set_mat3(ShaderUniforms uniform, const glm::mat3& matrix) const
    {
        glUniformMatrix3fv(m_uniforms.at(uniform), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Program::set_vec4(ShaderUniforms uniform, const glm::vec4& vec) const
    {
        glUniform4fv(m_uniforms.at(uniform), 1, glm::value_ptr(vec));
    }

    void Program::set_vec3(ShaderUniforms uniform, const glm::vec3& vec) const
    {
        glUniform3fv(m_uniforms.at(uniform), 1, glm::value_ptr(vec));
    }

    void Program::set_vec2(ShaderUniforms uniform, const glm::vec2& vec) const
    {
        glUniform2fv(m_uniforms.at(uniform), 1, glm::value_ptr(vec));
    }

    void Program::set_float(ShaderUniforms uniform, float value) const
    {
        glUniform1f(m_uniforms.at(uniform), value);    
    }

    void Program::set_int(ShaderUniforms uniform, int value) const
    {
        glUniform1i(m_uniforms.at(uniform), value);
    }

    const Uniforms& Program::get_uniforms() const
    {
        return m_uniforms;
    }

    const Attributes& Program::get_attributes() const
    {
        return m_attributes;
    }

    const Shaders& Program::get_shaders() const
    {
        return m_shaders;
    }

    int Program::get_uniform(ShaderUniforms uniform) const
    {
        return m_uniforms.at(uniform);
    }

    int Program::get_attribute(VertexAttributes attribute) const
    {
        return m_attributes.at(attribute);
    }

    int Program::get_program_id() const
    {
        return m_program_id;
    }

    void Program::use() const
    {
        glUseProgram(m_program_id);
    }

    void Program::attach_shader(std::shared_ptr<Shader> shader) const
    {
        glAttachShader(m_program_id, shader->get_shader_id());
    }

    void Program::detach_shader(std::shared_ptr<Shader> shader) const
    {
        glDetachShader(m_program_id, shader->get_shader_id());
    }

    int Program::get_attribute_location(const std::string& name)
    {
        return glGetAttribLocation(m_program_id, name.c_str());
    }

    int Program::get_uniform_location(const std::string& name)
    {
        return glGetUniformLocation(m_program_id, name.c_str());
    }

    void Program::link() const
    {
        glLinkProgram(m_program_id);
    }

    bool Program::create()
    {
        m_program_id = glCreateProgram();

        if (!m_program_id) 
        {
            return false;
        }

        for (auto shader : m_shaders)
        {
            if (shader->is_loaded())
            {
                attach_shader(shader);
            }
        }

        link();

        return linking_status();
    }

    bool Program::release()
    {
        if (!m_program_id)
        {
            return false;
        }
        
        for (auto shader : m_shaders)
        {
            if (shader->is_loaded())
            {
                detach_shader(shader);

                shader->unload();
            }
        }

        glDeleteProgram(m_program_id);

        m_uniforms.clear();
        m_attributes.clear();

        m_program_id = 0;

        return true;
    }

    bool Program::linking_status() const
    {
        int result;

        glGetProgramiv(m_program_id, GL_LINK_STATUS, &result);

        if (!result)
        {
            int length;

            glGetShaderiv(m_program_id, GL_INFO_LOG_LENGTH, &length);

            if (length)
            {
                std::vector<char> error(std::max(length, 1));
                glGetProgramInfoLog(m_program_id, length, nullptr, &error.front());

                cout << "program " << m_id << " has a problem:" << endl;

                fprintf(stdout, "%s\n", &error.front());
            }

            return false;
        }

        cout << "program " << m_id << " was linked successfully" << endl;
        
        return true;
    }
}