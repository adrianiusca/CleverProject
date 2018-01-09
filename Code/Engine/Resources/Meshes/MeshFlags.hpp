#pragma once

#include "Util.inl"

namespace cp
{
    enum MeshFlags
    {
        KEEP_DATA = Util::to_bit(0),
        
        USE_NORMALS  = Util::to_bit(1),
		USE_TEXTURES = Util::to_bit(2),
    };
}