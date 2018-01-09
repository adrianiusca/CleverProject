#pragma once

#include "Util.hpp"

namespace cp
{
    class MeshData
    {
    public:
        explicit MeshData(u32 vertices = 0, 
                          u32 indices = 0);
   
        void add_vec2(const vec2& vec);
        void add_vec3(const vec3& vec);

        void add_point(u16 index);
        void add_line(u16 index_one, u16 index_two);
        void add_triangle(u16 index_one, u16 index_two, u16 index_three);

        const vector<u16>& get_indices() const;
        const vector<f32>& get_vertices() const;

        u16* get_indices_ptr();
        f32* get_vertices_ptr();
    
        u32 get_vertices_size() const;
        u32 get_indices_size() const;

        void reserve_vertices(i32 size);
        void reserve_indices(i32 size);
        void clear();

        bool is_empty() const;
    
    private:
        vector<u16> m_indices;
        vector<f32> m_vertices;
    };
}