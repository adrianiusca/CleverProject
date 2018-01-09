#include "Object.hpp"

namespace cp
{
    Object::Object(i32 id)
    : m_id(id)
    {
    }

    void Object::set_flag(const Flag& flag)
    {
        m_flag = flag;
    }

    void Object::set_id(i32 id)
    {
        m_id = id;
    }

    const Flag& Object::get_flag() const
    {
        return m_flag;
    }

    i32 Object::get_id() const
    {
        return m_id;
    }
}