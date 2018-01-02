#pragma once

#include "Engine/Common/File.hpp"

namespace cp
{
    class TextureImporter
    {
    public:
        bool load(const File& file);

    private:
        TextureImporter(const TextureImporter &) = delete;
        TextureImporter &operator=(const TextureImporter &) = delete;
    };
}