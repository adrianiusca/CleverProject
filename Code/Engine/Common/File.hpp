#pragma once

#include "Util.hpp"

namespace cp
{
    class File
    {
    public:
        explicit File(const filesystem::path& path);

        bool open();
        void close();

        void set_path(const filesystem::path& path);
        const filesystem::path& get_path() const;

        filesystem::path get_extension() const;
        string get_data() const;

        template <class T> void read(T* value, int size) const;
        template <class T> void write(T* value, int size) const;

    private:
        filesystem::path m_path;
        FILE* m_ptr;
    };
}