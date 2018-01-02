#include "TextureImporter.hpp"

namespace cp
{   
    TextureImporter::TextureImporter(const File& file)
        : m_bits_per_pixel(0)
        , m_file(file)
        , m_data(nullptr)
    {
    }

    bool TextureImporter::load()
    {   
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(m_file.get_path().c_str(), 0);

        if (format == -1)
        {
            cout << "could not find image: " << m_file.get_filename() << endl;

            return false;
        }
        
        if (format == FIF_UNKNOWN)
        {
            cout << "could not determine file format" << endl;

            format = FreeImage_GetFIFFromFilename(m_file.get_path().c_str());

            if (!FreeImage_FIFSupportsReading(format))
            {
                cout << "detected image format cannot be read" << endl;

                return false;
            }
        }

        FIBITMAP* bitmap = FreeImage_Load(format, m_file.get_path().c_str());

        if (!bitmap)
        {
            return false;
        }

        m_bits_per_pixel = FreeImage_GetBPP(bitmap);
        m_size = ivec2(FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));

        cout << "image bpp: " << m_bits_per_pixel << endl;
        cout << "image size: " << m_size.x << " " << m_size.y << endl;        

        m_data = FreeImage_GetBits(bitmap);

        if (!m_data)
        {
            cout << "cannot read the data from the texture" << endl;

            return false;
        }

        if (!write())
        {
            return false;
        }
  
        FreeImage_Unload(bitmap);
        m_data = nullptr;

        return true;
    }

    bool TextureImporter::write()
    {
        m_file.set_extension(".texture");  

        if (!m_file.open("wb"))
        {
            return false;
        }

        m_file.write<ivec2>(&m_size, sizeof(ivec2));
        
        m_file.write<i32>(&m_bits_per_pixel, sizeof(i32));

        i32 image_size = m_size.x * 
                         m_size.y * (m_bits_per_pixel / 8);

        m_file.write<u8>(m_data, image_size);

        m_file.close();

        return true;
    }
}