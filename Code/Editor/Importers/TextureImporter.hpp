#pragma once

#include "Engine/Common/File.inl"

namespace cp
{
    class TextureImporter
    {
    public:
        explicit TextureImporter(const File& file);

        bool load();

    private:
        TextureImporter(const TextureImporter &) = delete;
        TextureImporter &operator=(const TextureImporter &) = delete;

        bool write();

    private:
        i32 m_bits_per_pixel;
        
        ivec2 m_size;

        File m_file;
        u8* m_data;
    };
}