#include "Object.hpp"

namespace cp
{
    Object::Object(int id)
    : m_id(id)
    {
    }

    Object::~Object()
    {
    }

    void Object::set_flag(const Flag& flag)
    {
        m_flag = flag;
    }

    void Object::set_id(int id)
    {
        m_id = id;
    }

    const Flag& Object::get_flag() const
    {
        return m_flag;
    }

    int Object::get_id() const
    {
        return m_id;
    }
}