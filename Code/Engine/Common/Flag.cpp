#include "Flag.hpp"

namespace cp
{
    Flag::Flag(i32 value)
        : m_value(value)
    {
    }

    Flag::Flag(const Flag& flag)
        : m_value(flag.m_value)
    {
    }

    Flag& Flag::operator=(const Flag& flag)
    {
        m_value = flag.m_value;

        return *this;
    }

    Flag& Flag::operator+=(const Flag& flag)
    {
        m_value |= flag.m_value;

        return *this;
    }

    Flag& Flag::operator-=(const Flag& flag)
    {
        m_value &= ~flag.m_value;

        return *this;
    }

    Flag Flag::operator+(const Flag& flag) const
    {
        return Flag(m_value | flag.m_value);
    }

    Flag Flag::operator-(const Flag& flag) const
    {
        return Flag(m_value & ~flag.m_value);
    }

    bool Flag::operator==(const Flag& flag) const
    {
        return m_value == flag.m_value;
    }

    bool Flag::contains(const Flag& flag) const
    {
        return (m_value & flag.m_value) == flag.m_value;
    }

    bool Flag::is_zero() const
    {
        return m_value == 0;
    }

    void Flag::reset()
    {
        m_value = 0;
    }

    i32 Flag::get_value() const
    {
        return m_value;
    }
}