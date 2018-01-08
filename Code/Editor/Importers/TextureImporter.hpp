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
        
        void check_format();

    private:
        u32 m_bits_per_pixel;
        u32 m_format;

        ivec2 m_size;

        File m_file;
        u8* m_data;
    };
}