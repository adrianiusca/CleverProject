#pragma once

#include "Util.hpp"

namespace cp
{
    class File
    {
    public:
        explicit File(const path& path);

        bool open(const string& mode = "rb");
        void close();

        void set_extension(const string& extension);
        void set_path(const path& path);
        const path& get_path() const;

        path get_filename() const;
        string get_extension() const;
        string get_data() const;

        template <class T> void read(T* value, int size) const;
        template <class T> void write(T* value, int size) const;

    private:
        path m_path;
        FILE* m_ptr;
    };
}