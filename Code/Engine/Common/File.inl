#pragma once

#include "File.hpp"

namespace cp
{
    template <class T> void File::read(T* value, int size) const
    {
        fread(value, size, 1, m_ptr);
    }

    template <class T> void File::write(T* value, int size) const
    {
        fwrite(value, size, 1, m_ptr);
    }
}