#pragma once

#include "Engine/Common/File.hpp"

namespace cp
{
    class SceneImporter
    {
    public:
        explicit SceneImporter(const File& file);

        bool load();

    private:
        SceneImporter(const SceneImporter &) = delete;
        SceneImporter &operator=(const SceneImporter &) = delete;

    private:
        File m_file;
    };
}