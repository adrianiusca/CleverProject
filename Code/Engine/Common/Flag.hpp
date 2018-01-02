#pragma once

#include "Util.hpp"

namespace cp
{
    class Flag
    {
    public:
        explicit Flag(i32 value = 0);

        Flag(const Flag& flag);
        Flag& operator=(const Flag& flag);

        Flag& operator+=(const Flag& flag);
        Flag& operator-=(const Flag& flag);

        Flag operator+(const Flag& flag) const;
        Flag operator-(const Flag& flag) const;

        bool operator==(const Flag& flag) const;
        bool contains(const Flag& flag) const;

        i32 get_value() const;
        bool is_zero() const;

        void reset();

    private:
        i32 m_value;
    };
}