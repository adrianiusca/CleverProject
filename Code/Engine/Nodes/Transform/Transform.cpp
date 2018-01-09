#include "Transform.hpp"
#include "TransformFlags.hpp"

namespace cp
{
    Transform::Transform()
        : m_is_uniform(true)
        , m_flag(TransformFlags::NEW_MATRIX)
    {
    }

    void Transform::update()
    {
        m_flag -= Flag(TransformFlags::IS_DIRTY);

        if (m_flag.contains(Flag(TransformFlags::NEW_MATRIX)))
        {
            m_local_matrix = glm::mat4();

            m_local_matrix[0].x = m_scale.x;
            m_local_matrix[1].y = m_scale.y;
            m_local_matrix[2].z = m_scale.z;

            m_local_matrix = glm::mat4_cast(m_orientation) * m_local_matrix;

            m_flag -= Flag(TransformFlags::NEW_MATRIX);
            m_flag += Flag(TransformFlags::NEW_POSITION);
        }

        if (m_flag.contains(Flag(TransformFlags::NEW_POSITION)))
        {
            m_local_matrix[3].x = m_position.x;
            m_local_matrix[3].y = m_position.y;
            m_local_matrix[3].z = m_position.z;

            m_flag -= Flag(TransformFlags::NEW_POSITION);
            m_flag += Flag(TransformFlags::IS_DIRTY);
        }

        if (m_parent)
        {
            if (m_parent->is_dirty() || is_dirty())
            {
                m_world_matrix = m_parent->get_matrix() * m_local_matrix;

                m_flag += Flag(TransformFlags::IS_DIRTY);
            }
        }
    }

    void Transform::identity()
    {
        m_flag += Flag(TransformFlags::NEW_MATRIX);

        reset();
    }

    void Transform::move(const glm::vec3& position)
    {
        m_position = position;

        m_flag += Flag(TransformFlags::NEW_POSITION);
    }

    void Transform::translate(const glm::vec3& amount)
    {
        m_position += amount;

        m_flag += Flag(TransformFlags::NEW_POSITION);
    }

    void Transform::translate_forward(f32 amount)
    {
        if (glm::abs(amount) > 0)
        {
            translate(glm::vec3(0.0f, 0.0f, -1.0f) * glm::inverse(m_orientation) * amount);
        }
    }

    void Transform::rotate(const glm::vec3& axis, float angle)
    {
        m_orientation = glm::angleAxis(glm::radians(angle), axis);

        m_flag += Flag(TransformFlags::NEW_MATRIX);
    }

    void Transform::rotate(const glm::vec3& angles)
    {
        m_orientation = glm::quat(glm::radians(angles));

        m_flag += Flag(TransformFlags::NEW_MATRIX);
    }

    void Transform::rotate_on_x(float angle)
    {
        rotate(glm::vec3(1.0f, 0.0f, 0.0f), angle);
    }

    void Transform::rotate_on_y(float angle)
    {
        rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle);
    }

    void Transform::rotate_on_z(float angle)
    {
        rotate(glm::vec3(0.0f, 0.0f, 1.0f), angle);
    }

    void Transform::scale(const glm::vec3& scale)
    {
        m_is_uniform = glm::abs(m_scale.x - m_scale.y) <= glm::epsilon<float>() &&
                       glm::abs(m_scale.y - m_scale.z) <= glm::epsilon<float>();

        m_flag += Flag(TransformFlags::NEW_MATRIX);

        m_scale = scale;
    }

    void Transform::set_parent(const std::shared_ptr<Transform>& transform)
    {
        m_parent = transform;
    }

    std::shared_ptr<Transform> Transform::get_parent() const
    {
        return m_parent;
    }

    const glm::mat4& Transform::get_matrix() const
    {
        return (m_parent) ? m_world_matrix : m_local_matrix;
    }

    glm::vec3 Transform::get_global_position() const
    {
        return glm::vec3(m_world_matrix[3].x, 
                         m_world_matrix[3].y, 
                         m_world_matrix[3].z);
    }

    glm::vec3 Transform::get_global_scale() const
    {
        return glm::vec3(m_world_matrix[0].x, 
                         m_world_matrix[1].y, 
                         m_world_matrix[2].z);
    }

    glm::mat3 Transform::get_normal_matrix() const
    {
        return is_uniform() ? m_world_matrix : glm::transpose(glm::inverse(m_world_matrix));
    }

    bool Transform::is_uniform() const
    {
        return m_is_uniform;
    }

    bool Transform::is_dirty() const
    {
        return m_flag.contains(Flag(TransformFlags::IS_DIRTY));
    }
}
