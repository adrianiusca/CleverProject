#pragma once

#include "MeshData.hpp"
#include "MeshBuffers.hpp"
#include "VertexAttributes.hpp"
#include "Engine/Resources/DynamicResource.hpp"

namespace cp
{
    typedef array<u32, MeshBuffers::BUFFERS_SIZE> Buffers;
    typedef array<u32, VertexAttributes::ATTRIBUTES_SIZE> Attributes;

    class Mesh : public DynamicResource
    {
    public:
        explicit Mesh(i32 id, const shared_ptr<File>& file = nullptr);

        bool upload() override;
        void upload_attributes() const;

        void keep_data();

        void set_data(const shared_ptr<MeshData>& data);
        void set_offsets(const Attributes& offsets);

        void draw() const;

        void bind_vao() const;
        void bind_vbo() const;
        void bind_ibo() const;

        void set_drawing_primitive(int drawing_primitive);
        void set_drawing_type(int drawing_type);
        void set_vertex_size(int size);

        shared_ptr<MeshData> get_data();

        bool is_keeping_data() const;

        int get_drawing_type() const;
        int get_drawing_primitive() const;

        int get_vertex_size() const;
        int get_indices_size() const;

    private:
        bool parse() override;

        bool create() override;
        bool release() override;

    private:
        std::shared_ptr<MeshData> m_data;

        Buffers m_buffers;
        Attributes m_offsets;

        u32 m_vao_id;

        i32 m_drawing_type;
        i32 m_drawing_primitive;

        i32 m_indices_size;
        i32 m_vertex_size;
    };
}