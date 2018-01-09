#pragma once

#include "TransformData.hpp"
#include "Engine/Common/Flag.hpp"

namespace cp
{
    class Transform : public TransformData
    {
    public:
        Transform();

        void update();
        void identity();

        void move(const glm::vec3& position);
        void scale(const glm::vec3& scale);

        void translate(const glm::vec3& amount);
        void translate_forward(float amount);

        void rotate(const glm::vec3& axis, float angle);
        void rotate(const glm::vec3& angles);

        void rotate_on_x(float angle);
        void rotate_on_y(float angle);
        void rotate_on_z(float angle);

        void set_parent(const std::shared_ptr<Transform>& transform);

        std::shared_ptr<Transform> get_parent() const;
        const glm::mat4& get_matrix() const;

        glm::vec3 get_global_position() const;
        glm::vec3 get_global_scale() const;
        glm::mat3 get_normal_matrix() const;

        bool is_uniform() const;
        bool is_dirty() const;

    private:
        std::shared_ptr<Transform> m_parent;

        glm::mat4 m_world_matrix;
        glm::mat4 m_local_matrix;

        bool m_is_uniform;
        Flag m_flag;
    };
}