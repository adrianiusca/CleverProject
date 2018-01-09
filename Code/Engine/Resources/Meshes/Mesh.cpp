#include "Mesh.hpp"
#include "MeshFlags.hpp"

namespace cp
{
    Mesh::Mesh(i32 id, const shared_ptr<File>& file)
        : DynamicResource(id, ResourceTypes::MESH, file)
        , m_vao_id(0)
        , m_drawing_type(GL_STATIC_DRAW)
        , m_drawing_primitive(GL_TRIANGLES)
        , m_indices_size(0)
        , m_vertex_size(sizeof(glm::vec3))
    {
    }

    bool Mesh::upload()
    {
        if (!m_data)
        {
            return false;
        }

        if (m_data->is_empty())
        {
            return false;
        }

        bind_vao();
        
        bind_vbo();
        glBufferData(GL_ARRAY_BUFFER, m_data->get_vertices_size() * sizeof(f32), 
                                      &m_data->get_vertices().front(), m_drawing_type);

        bind_ibo();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data->get_indices_size() * sizeof(u8), 
                                              &m_data->get_indices().front(), m_drawing_type);

        upload_attributes();

        m_indices_size = m_data->get_indices_size();

        return true;
    }

    void Mesh::upload_attributes() const
    {
        i32 index = 0;

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, m_vertex_size, static_cast<const void*>(0));

        i32 normal_offset = m_offsets[VertexAttributes::ATTRIBUTE_NORMAL];
        i32 texture_offset = m_offsets[VertexAttributes::ATTRIBUTE_TEXTURE];

        if (normal_offset > 0)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, m_vertex_size, reinterpret_cast<const void*>(normal_offset));
        }

        if (texture_offset > 0)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index++, 2, GL_FLOAT, GL_FALSE, m_vertex_size, reinterpret_cast<const void*>(texture_offset));
        }
    }
    
    void Mesh::keep_data()
    {
        m_flag += Flag(MeshFlags::KEEP_DATA);
    }

    void Mesh::set_data(const shared_ptr<MeshData>& data)
    {
        m_data = data;
    }

    void Mesh::set_offsets(const Attributes& offsets)
    {
        m_offsets = offsets;
    }

    void Mesh::draw() const
    {
        glDrawElements(m_drawing_primitive, m_indices_size, GL_UNSIGNED_SHORT, static_cast<const void*>(0));
    }

    void Mesh::bind_vao() const
    {
        glBindVertexArray(m_vao_id);
    }

    void Mesh::bind_vbo() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[MeshBuffers::BUFFER_VBO]);
    }

    void Mesh::bind_ibo() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[MeshBuffers::BUFFER_IBO]);
    }

    void Mesh::set_drawing_primitive(int drawing_primitive)
    {
        if (drawing_primitive != GL_POINTS && 
            drawing_primitive != GL_LINES && 
            drawing_primitive != GL_TRIANGLES)
        {
            cout << "did not pass the correct drawing primitive for mesh " << m_id << endl;
        }

        m_drawing_primitive = drawing_primitive;
    }

    void Mesh::set_drawing_type(int drawing_type)
    {
        if (drawing_type != GL_STATIC_DRAW && 
            drawing_type != GL_DYNAMIC_DRAW)
        {
            cout << "did not pass the correct drawing type for mesh " << m_id << endl;
        }

        m_drawing_type = drawing_type;
    }    

    void Mesh::set_vertex_size(int size)
    {
        m_vertex_size = size;
    }

    shared_ptr<MeshData> Mesh::get_data()
    {
        return m_data;
    }

    bool Mesh::is_keeping_data() const
    {
        return m_flag.contains(Flag(MeshFlags::KEEP_DATA));
    }

    int Mesh::get_drawing_type() const
    {
        return m_drawing_type;
    }

    int Mesh::get_drawing_primitive() const
    {
        return m_drawing_primitive;
    }

    int Mesh::get_vertex_size() const
    {
        return m_vertex_size;
    }

    int Mesh::get_indices_size() const
    {
        return m_indices_size;
    }

    bool Mesh::parse()
    {
        const std::string& data = m_file->get_data();

        if (data.empty())
        {
            cout << "data for mesh file " << m_file->get_filename() << " is empty" << endl;

            return false;
        }

        std::stringstream reader(data);

        int vertices_size = 0;
        int indices_size  = 0;

        reader >> m_drawing_primitive;
        reader >> m_vertex_size;

        for (i32 i = 0; i < VertexAttributes::ATTRIBUTES_SIZE; i++)
        {
            reader >> m_offsets[i];
        }

        reader >> vertices_size;
        
        i32 elements = m_vertex_size / sizeof(f32);

        m_data = make_shared<MeshData>();
        m_data->reserve_vertices(vertices_size * elements);

        for (i32 i = 0; i < vertices_size; i++)
        {
            vec3 position;

            reader >> position.x >> position.y >> position.z;
            m_data->add_vec3(position);

            if (m_offsets[VertexAttributes::ATTRIBUTE_NORMAL] > 0)
            {
                vec3 normal;

                reader >> normal.x >> normal.y >> normal.z;
                m_data->add_vec3(normal);
            }

            if (m_offsets[VertexAttributes::ATTRIBUTE_TEXTURE] > 0)
            {
                vec2 texture;

                reader >> texture.x >> texture.y;
                m_data->add_vec2(texture);
            }
        }

        reader >> indices_size;
        m_data->reserve_indices(indices_size);

        for (i32 i = 0; i < indices_size; i++)
        {
            u8 index;

            reader >> index;
            m_data->add_point(index);
        }

        return true;
    }

    bool Mesh::create()
    {
        glGenVertexArrays(1, &m_vao_id);

        if (!m_vao_id)
        {
            cout << "vao connot be created for mesh id " << m_id << endl;

            return false;
        }

        glGenBuffers(MeshBuffers::BUFFERS_SIZE, &m_buffers.front());

        if (!m_buffers[MeshBuffers::BUFFER_VBO] ||
            !m_buffers[MeshBuffers::BUFFER_IBO])
        {
            cout << "vbo or ibo connot be created for mesh id " << m_id << endl;

            return false;
        }

        if (m_file)
        {
            if (!parse())
            {
                cout << "file connot be parsed for mesh id " << m_id << endl;

                return false;
            }

            cout << "file parsed correctly" << endl;
        }

        if (!upload())
        {
            return false;
        }

        if (!is_keeping_data())
        {
            if (m_data)
            {
                m_data->clear();
                m_data = nullptr;
            }
        }

        cout << "mesh created with success" << endl;

        return true;
    }

    bool Mesh::release()
    {
        if (!m_vao_id)
        {
            return false;
        }

        if (!m_buffers[MeshBuffers::BUFFER_VBO] || 
            !m_buffers[MeshBuffers::BUFFER_IBO])
        {
            return false;
        }

        if (m_data)
        {
            m_data->clear();
            m_data = nullptr;
        }

        glDeleteBuffers(MeshBuffers::BUFFERS_SIZE, m_buffers.data());
        glDeleteVertexArrays(1, &m_vao_id);

        m_buffers.fill(0);
        m_vao_id = 0;

        return true;
    }
}