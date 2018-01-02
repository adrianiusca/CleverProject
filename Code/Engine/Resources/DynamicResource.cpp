#include "DynamicResource.hpp"

namespace cp
{
    DynamicResource::DynamicResource(int id, ResourceTypes type, shared_ptr<File> file)
        : Resource(id, type, file)
        , m_is_loaded(false)
        , m_counter(0)
    {
    }

    bool DynamicResource::load()
    {
        if (!m_counter)
        {
            if (!create())
            {
                cout << "could not create the resource " << m_id << endl;

                return false;
            }

            m_is_loaded = true;
        }

        m_counter++;

        return true;
    }

    bool DynamicResource::unload()
    {
        if (!m_counter)
        {
            cout << "no references for the resource " << m_id << endl;

            return false;
        }

        if (m_counter == 1)
        {
            if (!release())
            {
                cout << "could not release the resource " << m_id << endl;

                return false; 
            }

            m_is_loaded = false;
        }

        m_counter--;

        return true;
    }

    i32 DynamicResource::get_counter() const
    {
        return m_counter;
    }

    bool DynamicResource::is_loaded() const
    {
        return m_is_loaded;
    }
}