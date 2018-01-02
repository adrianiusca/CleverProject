#include "File.inl"

namespace cp
{
    File::File(const path& path)
        : m_path(path)
        , m_ptr(nullptr)
    {
    }

    bool File::open(const string& mode)
    {
        if (m_path.empty())
        {
            cout << "file path is empty" << endl;

            return false;
        }

        m_ptr = fopen(m_path.c_str(), mode.c_str());

        if (!m_ptr)
        {
            cout << "file pointer is null" << endl;

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

    void File::set_path(const path& path)
    {
        m_path = path;
    }

    void File::set_extension(const string& extension)
    {
        m_path.replace_extension(extension);
    }

    const path& File::get_path() const
    {
        return m_path;
    }
        
    string File::get_extension() const
    {
        return m_path.extension();
    }

    path File::get_filename() const
    {
        return m_path.filename();
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