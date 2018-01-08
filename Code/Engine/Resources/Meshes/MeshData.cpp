#include "MeshData.hpp"

namespace cp
{
    MeshData::MeshData(u32 vertices, u32 indices)
    {
        if (vertices > 0)
        {
            reserve_vertices(vertices);
        }

        if (indices > 0)
        {
            reserve_indices(indices);
        }
    }
   
    void MeshData::add_vec2(const vec2& vec)
    {
        m_vertices.emplace_back(vec.x);
	    m_vertices.emplace_back(vec.y);
    }

    void MeshData::add_vec3(const vec3& vec)
    {
        m_vertices.emplace_back(vec.x);
        m_vertices.emplace_back(vec.y);
        m_vertices.emplace_back(vec.z);
    }

    void MeshData::add_point(u8 index)
    {
        m_indices.emplace_back(index);
    }

    void MeshData::add_line(u8 index_one, u8 index_two)
    {
        add_point(index_one);
        add_point(index_two);
    }

    void MeshData::add_triangle(u8 index_one, u8 index_two, u8 index_three)
    {
        add_point(index_one);
        add_point(index_two);
        add_point(index_three);
    }

    const vector<u8>& MeshData::get_indices() const
    {
        return m_indices;
    }

    const vector<f32>& MeshData::get_vertices() const
    {
        return m_vertices;
    }

    void MeshData::reserve_vertices(i32 size)
    {
        m_vertices.reserve(size);
    }

    void MeshData::reserve_indices(i32 size)
    {
        m_indices.reserve(size);
    }

    void MeshData::clear()
    {
        m_vertices.clear();
        m_indices.clear();
    }

    bool MeshData::is_empty() const
    {
        return m_vertices.empty() || 
               m_indices.empty();
    }

    u32 MeshData::get_vertices_size() const
    { 
        return m_vertices.size();
    }

    u32 MeshData::get_indices_size() const
    {  
        return m_indices.size();
    }

    u8* MeshData::get_indices_ptr()
    {
        return m_indices.data();
    }
    
    f32* MeshData::get_vertices_ptr()
    {
        return m_vertices.data();
    }
}