#pragma once

#include "Util.hpp"
#include "Engine/Resources/Meshes/Mesh.hpp"

namespace cp
{
    class MeshImporter
    {
    public:
        explicit MeshImporter(const Flag& flag);

        bool write(const path& path, const aiMesh* mesh);

    private:
        MeshImporter(const MeshImporter &) = delete;
        MeshImporter &operator=(const MeshImporter &) = delete;

        void check_drawing_primitive(u32 indices);
        void check_vertex_size_and_offsets(const aiMesh* mesh);

    private:
        Offsets m_offsets;

        u32 m_drawing_primitive;
        u32 m_vertex_size;

        Flag m_flag;
    };
}