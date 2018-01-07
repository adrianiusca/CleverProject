#pragma once

#include "Util.hpp"

namespace cp
{
    class TextureData
    {
    public:
        explicit TextureData(u32 size);
        
        ivec4 get_pixel(i32 index, u32 elements) const;
        const vector<u8>& get_pixels() const;

        u8* get_pointer();

        bool is_empty() const;

        void resize(u32 size);
        void clear();

    private:
        vector<u8> m_pixels;
    };
}