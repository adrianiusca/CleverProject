#pragma once

#include "Flag.hpp"

namespace cp
{
    class Object
    {
    public:
        explicit Object(int id);

        virtual ~Object();

        void set_flag(const Flag& flag);
        void set_id(i32 id);

        const Flag& get_flag() const;
        i32 get_id() const;

    protected:
        Flag m_flag;
        i32 m_id;
    };
}