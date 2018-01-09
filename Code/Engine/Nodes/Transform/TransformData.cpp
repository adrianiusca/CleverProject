#include "TransformData.hpp"

namespace cp
{
    TransformData::TransformData()
        : m_scale(1.0f)
    {
    }

    void TransformData::reset()
    {
        m_orientation = glm::quat();

        m_position = glm::vec3();
        m_scale = glm::vec3(1.0f);
    }

    void TransformData::set_orientation(const glm::quat& orientation)
    {
        m_orientation = orientation;
    }

    void TransformData::set_position(const glm::vec3& position)
    {
        m_position = position;
    }

    void TransformData::set_scale(const glm::vec3& scale)
    {
        m_scale = scale;
    }

    const glm::quat& TransformData::get_orientation() const
    {
        return m_orientation;
    }

    const glm::vec3& TransformData::get_position() const
    {
        return m_position;
    }

    const glm::vec3& TransformData::get_scale() const
    {
        return m_scale;
    }
}