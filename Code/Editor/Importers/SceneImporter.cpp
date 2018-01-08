#include "SceneImporter.hpp"
#include "MeshImporter.hpp"

namespace cp
{
    SceneImporter::SceneImporter(const File& file)
        : m_file(file)
    {
    }

    bool SceneImporter::load()
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(m_file.get_path(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

        if (!scene)
        {
            return false;
        }

        for (u32 i = 0; i < scene->mNumMeshes; i++)
        {
            const aiMesh* mesh = scene->mMeshes[i];

            if (mesh)
            {
                path mesh_file = "Assets/";

                mesh_file.replace_filename(mesh->mName.C_Str());
                mesh_file.replace_extension(".mesh");

               MeshImporter mesh_importer;
               mesh_importer.write(mesh_file, mesh);
            }
        }

        return true;
    }
}