#pragma once

#include "Resource.hpp"

namespace cp
{
    class DynamicResource : public Resource
    {
    public:
        bool load();
        bool unload();

        i32 get_counter() const;
        bool is_loaded() const;

    protected:
        explicit DynamicResource(int id, ResourceTypes type, shared_ptr<File> = nullptr);

        virtual ~DynamicResource() = default;

    private:
        virtual bool create() = 0;
        virtual bool release() = 0;

    private:
        bool m_is_loaded;
        int m_counter;
    };
}