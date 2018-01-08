#include "Texture.hpp"
#include "TextureFlags.hpp"
#include "Engine/Common/File.inl"

namespace cp
{
    Texture::Texture(u32 id, shared_ptr<File> file)
        : DynamicResource(id, ResourceTypes::TEXTURE, file)
        , m_bits_per_pixel(0)
        , m_texture_id(0)
        , m_format(0)
    {
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }

    void Texture::use_mipmaps()
    {
        m_flag += Flag(TextureFlags::USE_MIPMAPS);
    }

    void Texture::keep_pixels()
    {
        m_flag += Flag(TextureFlags::KEEP_PIXELS);
    }

    void Texture::set_size(const ivec2& size)
    {
        m_size = size;
    }

    const ivec2& Texture::get_size() const
    {
        return m_size;
    }

    shared_ptr<TextureData> Texture::get_data() const
    {
        return m_data;
    }
    
    u32 Texture::get_texture_format() const
    {
        return m_format;
    }

    u32 Texture::get_texture_id() const
    {
        return m_texture_id;
    }

    u32 Texture::get_bits_per_pixel() const
    {
        return m_bits_per_pixel;
    }

    u32 Texture::get_pixel_elements() const
    {
        return m_bits_per_pixel / 8;
    }

    void Texture::activate(u32 index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    bool Texture::parse()
    {
        if (!m_file)
        {
            cout << "do not have a file for the texture " << m_id << endl;

            return false;
        }

        if (!m_file->open())
        {
            cout << "could not open the file for the texture " << m_id << endl;

            return false;
        }

        m_file->read<ivec2>(&m_size, sizeof(ivec2));
        m_file->read<u32>(&m_bits_per_pixel, sizeof(u32));
        m_file->read<u32>(&m_format, sizeof(u32));

        i32 image_size = m_size.x * 
                         m_size.y * get_pixel_elements();

        m_data = make_shared<TextureData>(image_size);

        m_file->read<u8>(m_data->get_ptr(), image_size);

        m_file->close();

        return true;
    }

    bool Texture::is_using_mimaps() const
    {
        return m_flag.contains(Flag(TextureFlags::USE_MIPMAPS));
    }

    bool Texture::is_keeping_pixels() const
    {
         return m_flag.contains(Flag(TextureFlags::KEEP_PIXELS));
    }

    bool Texture::create()
    {   
        if (m_file)
        {
            if (!parse())
            {
                cout << "file connot be parsed for texture id " << m_id << endl;

                return false;
            }

            cout << "file parsed correctly" << endl;
        }

        if (m_data->is_empty())
        {
            return false;
        }

        glGenTextures(1, &m_texture_id);

        if (!m_texture_id)
        {
            return false;
        }

        if (!m_format)
        {
            return false;
        }

        bind();

        if (is_using_mimaps())
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

        glTexImage2D(GL_TEXTURE_2D, 0, m_format, 
                                       m_size.x, 
                                       m_size.y, 0, 
                                       m_format, GL_UNSIGNED_BYTE, m_data->get_ptr());

        if (is_using_mimaps())
		{
			glGenerateMipmap(GL_TEXTURE_2D);
        }

        if (!is_keeping_pixels())
        {
            if (m_data)
            {
                m_data->clear();
                m_data = nullptr;
            }
        }

        return true;
    }

    bool Texture::release()
    {
        if (!m_texture_id)
        {
            return false;
        }

        glDeleteTextures(1, &m_texture_id);

        m_texture_id = 0;

        if (m_data)
        {
            m_data->clear();
            m_data = nullptr;
        }

        return true;
    }
}