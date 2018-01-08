#include "TextureData.hpp"

namespace cp
{
    TextureData::TextureData(u32 size)
        : m_pixels(size)
    {
    }

    bool TextureData::is_empty() const
    { 
        return m_pixels.empty();
    }

    const vector<u8>& TextureData::get_pixels() const
    {
        return m_pixels;
    }

    u8* TextureData::get_ptr()
    {
        return m_pixels.data();
    }
        
    void TextureData::resize(u32 size)
    {
        m_pixels.resize(size);
    }

    void TextureData::clear()
    {
        m_pixels.clear();
    }

    ivec4 TextureData::get_pixel(i32 index, u32 elements) const
    {
        glm::ivec4 pixel;

        if (elements >= 1)
		{
		    pixel.r = m_pixels[index * elements];
        }

		if (elements >= 2)
		{
			pixel.g = m_pixels[index * elements + 1];
        }

        if (elements >= 3)
        {
			pixel.b = m_pixels[index * elements + 2];
		}

		if (elements == 4)
		{
			pixel.a = m_pixels[index * elements + 3];
		}

		return pixel;
    }
}