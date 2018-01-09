#pragma once

#include "Shader.hpp"
#include "ShaderUniforms.hpp"
#include "Engine/Resources/DynamicResource.hpp"
#include "Engine/Resources/Meshes/VertexAttributes.hpp"

namespace cp
{
    typedef map<ShaderUniforms, i32> Uniforms;
    typedef map<VertexAttributes, i32> ShaderAttributes;

    typedef vector<shared_ptr<Shader>> Shaders;

    class Program : public DynamicResource
    {
    public:
        explicit Program(int id);

        void add_shader(shared_ptr<Shader> shader);
        void add_shaders(const Shaders& shaders);

        void remove_shader(int type);

        void add_uniform(ShaderUniforms uniform, const string& name);
        void add_attribute(VertexAttributes attribute, const string& name);

        void set_mat4(ShaderUniforms uniform, const mat4& matrix) const;
        void set_mat3(ShaderUniforms uniform, const mat3& matrix) const;

        void set_vec4(ShaderUniforms uniform, const vec4& vec) const;
        void set_vec3(ShaderUniforms uniform, const vec3& vec) const;
        void set_vec2(ShaderUniforms uniform, const vec2& vec) const;

        void set_float(ShaderUniforms uniform, float value) const;
        void set_int(ShaderUniforms uniform, int value) const;

        const Uniforms& get_uniforms() const;
        const ShaderAttributes& get_attributes() const;

        const Shaders& get_shaders() const;

        int get_uniform(ShaderUniforms uniform) const;
        int get_attribute(VertexAttributes attribute) const;

        int get_program_id() const;

        void use() const;

    private:
        void attach_shader(shared_ptr<Shader> shader) const;
        void detach_shader(shared_ptr<Shader> shader) const;

        int get_attribute_location(const string& name);
        int get_uniform_location(const string& name);

        bool create() override;
        bool release() override;

        bool linking_status() const;
        void link() const;

    private:
        Shaders m_shaders;

        Uniforms m_uniforms;
        ShaderAttributes m_attributes;

        int m_program_id;
    };
}