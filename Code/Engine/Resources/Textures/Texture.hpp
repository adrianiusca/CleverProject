#pragma once

#include "TextureData.hpp"
#include "Engine/Resources/DynamicResource.hpp"

namespace cp
{
    class Texture : public DynamicResource
    {
    public:
        explicit Texture(u32 id, shared_ptr<File> file = nullptr);

        void bind();
        void use_mipmaps();
        void keep_pixels();

        void set_size(const ivec2& size);
        const ivec2& get_size() const;

        shared_ptr<TextureData> get_data() const;
       
        u32 get_pixel_elements() const;
        u32 get_bits_per_pixel() const;
        
        u32 get_texture_format() const;
        u32 get_texture_id() const;

        bool is_using_mimaps() const;
        bool is_keeping_pixels() const;

        static void activate(u32 index = 0);

    private:
        bool parse() override;

        bool create() override;
        bool release() override;

    private:
        shared_ptr<TextureData> m_data;
        ivec2 m_size;

        u32 m_bits_per_pixel;
        u32 m_texture_id;
        u32 m_format;
    };
}