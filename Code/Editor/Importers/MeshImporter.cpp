#include "MeshImporter.hpp"
#include "Engine/Resources/Meshes/MeshFlags.hpp"

namespace cp
{
    MeshImporter::MeshImporter(const Flag& flag)
        : m_drawing_primitive(0)
        , m_vertex_size(sizeof(vec3))
        , m_flag(flag)
    {
    }

    bool MeshImporter::write(const path& path, const aiMesh* mesh)
    {
         std::ofstream writer;

        writer.setf(ios::fixed, ios::floatfield);
        writer.open(path, ios::out);

        if (!writer.is_open())
        {
            return false;
        }

        u32 indices = mesh->mFaces[0].mNumIndices;

        check_drawing_primitive(indices);
        check_vertex_size_and_offsets(mesh);

        writer << m_drawing_primitive << endl;
        writer << m_vertex_size << endl;

        for (i32 i = 0; i < VertexAttributes::ATTRIBUTES_SIZE; i++)
        {
            writer << m_offsets.at(i);

            if (i < VertexAttributes::ATTRIBUTES_SIZE - 1)
            {
                writer << " ";
            }
        }

        writer << std::endl;
        writer << mesh->mNumVertices << std::endl;

        for (u32 v = 0; v < mesh->mNumVertices; ++v)
        {
            const aiVector3D& position = mesh->mVertices[v];
            writer << position.x << " " << position.y << " " << position.z;

            if (m_flag.contains(Flag(MeshFlags::USE_NORMALS)))
            {
                if (mesh->HasNormals())
                {
                    const aiVector3D& normal = mesh->mNormals[v];
                    writer << " " << normal.x << " " << normal.y << " " << normal.z;
                }
            }

            if (m_flag.contains(Flag(MeshFlags::USE_TEXTURES)))
            {
                if (mesh->HasTextureCoords(0))
                {
                    const aiVector3D& texture = mesh->mTextureCoords[0][v];
                    writer << " " << texture.x << " " << texture.y;
                }
            }

            writer << endl;
        }

        writer << mesh->mNumFaces * indices << std::endl;

        for (u32 f = 0; f < mesh->mNumFaces; ++f)
        {
            const aiFace& face = mesh->mFaces[f];

            for (u32 i = 0; i < indices; ++i)
            {
                writer << face.mIndices[i];

                if (i < indices - 1)
                {
                    writer << " ";
                }
            }

            writer << endl;
        }

        writer.close();

        return true;
    }

    void MeshImporter::check_vertex_size_and_offsets(const aiMesh* mesh)
    {
        m_offsets.fill(0);

        if (m_flag.contains(Flag(MeshFlags::USE_NORMALS)))
        {
            if (mesh->HasNormals())
            {
                m_offsets[VertexAttributes::ATTRIBUTE_NORMAL] = m_vertex_size;
                m_vertex_size += sizeof(vec3);
            }
        }

        if (m_flag.contains(Flag(MeshFlags::USE_TEXTURES)))
        {
            if (mesh->HasTextureCoords(0))
            {
                m_offsets[VertexAttributes::ATTRIBUTE_TEXTURE] = m_vertex_size;
                m_vertex_size += sizeof(vec2);
            }
        }
    }

    void MeshImporter::check_drawing_primitive(u32 indices)
    {
        if (indices == 1)
        {
            m_drawing_primitive = GL_POINTS;
        }
        else if (indices == 2)
        {
            m_drawing_primitive = GL_LINES;
        }
        else if (indices == 3)
        {
            m_drawing_primitive = GL_TRIANGLES;
        }
    }
}