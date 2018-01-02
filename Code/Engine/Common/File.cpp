#include "File.inl"

namespace cp
{
    File::File(const filesystem::path& path)
        : m_path(path)
        , m_ptr(nullptr)
    {
    }

    bool File::open()
    {
        if (m_path.empty())
        {
            return false;
        }

        m_ptr = fopen(m_path.c_str(), "rb");

        if (!m_ptr)
        {
            return false;
        }

        return true;
    }

    void File::close()
    {
        if (m_ptr)
        {
            fclose(m_ptr);
        }

        m_ptr = nullptr;
    }

    void File::set_path(const filesystem::path& path)
    {
        m_path = path;
    }

    const filesystem::path& File::get_path() const
    {
        return m_path;
    }
        
    filesystem::path File::get_extension() const
    {
        return m_path.extension();
    }

    string File::get_data() const
    {
        std::string data;

        if (m_ptr)
        {
            cout << "The file " << m_path.filename() << " is already open for binary reading";

            return data;
        }

        if (!m_path.empty())
        {
            std::ifstream read(m_path.c_str(), std::ifstream::in);

            if (read.is_open())
            {
                std::stringstream stream;
                stream << read.rdbuf();

                data = stream.str();
                read.close();
            }
        }

        return data;
    }
}