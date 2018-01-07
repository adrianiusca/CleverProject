#pragma once

#include "Util.hpp"

namespace cp
{
    class Util
    {  
    public:
        inline static constexpr i32 to_bit(i32 value)
        {
            return 1 << value;
        }
    };
}