#pragma once

#include "Util.inl"

namespace cp
{
    enum TextureFlags
    {
        USE_MIPMAPS = Util::to_bit(0),
        KEEP_PIXELS = Util::to_bit(1)
    };
}