#include "Resource.hpp"

namespace cp
{
    Resource::Resource(int id, ResourceTypes type, shared_ptr<File> file)
        : Object(id)
        , m_file(file)
        , m_type(type)
    {
    }

    bool Resource::upload()
    {
        cout << "empty upload function is called for resource " << m_id << endl;

        return true;
    }

    bool Resource::parse()
    {
        cout << "empty parse function is called for resource " << m_id << endl;

        return true;
    }

    void Resource::set_file(const shared_ptr<File>& file)
    {
        m_file = file;
    }

    shared_ptr<File> Resource::get_file() const
    {
        return m_file;
    }
}