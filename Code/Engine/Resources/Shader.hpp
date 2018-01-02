#pragma once

#include "DynamicResource.hpp"

namespace cp
{
    class Shader : public DynamicResource
    {
    public:
        Shader(i32 id, const std::shared_ptr<File>& file, i32 type);

        i32 get_shader_type() const;
        i32 get_shader_id() const;

    private:
        bool create() override;
        bool release() override;

        bool compilation_status() const;
        void compile() const;

    private:
        int m_shader_id;
        int m_shader_type;
    };
}