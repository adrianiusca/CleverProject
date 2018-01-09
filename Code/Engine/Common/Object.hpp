#pragma once

#include "Flag.hpp"

namespace cp
{
    class Object
    {
    public:
        void set_flag(const Flag& flag);
        void set_id(i32 id);

        const Flag& get_flag() const;
        i32 get_id() const;

    protected:
        explicit Object(i32 id);
        
        virtual ~Object() = default;

    protected:
        Flag m_flag;
        i32 m_id;
    };
}