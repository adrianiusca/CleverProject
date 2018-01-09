#pragma once

#include "Util.inl"

namespace cp
{
    enum TransformFlags
    {
        NEW_POSITION = Util::to_bit(0),
        NEW_MATRIX = Util::to_bit(1),

        IS_DIRTY = Util::to_bit(2)
    };
}