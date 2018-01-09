#pragma once

#include "Util.hpp"

namespace cp
{
    class TransformData
    {
    public:
        TransformData();

        void set_orientation(const quat& orientation);
        void set_position(const vec3& position);
        void set_scale(const vec3& scale);

        const quat& get_orientation() const;
        const vec3& get_position() const;
        const vec3& get_scale() const;

    protected:
        void reset();

    protected:
        quat m_orientation;

        vec3 m_position;
        vec3 m_scale;
    };
}