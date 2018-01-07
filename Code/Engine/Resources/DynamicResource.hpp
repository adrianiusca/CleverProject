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
        explicit DynamicResource(i32 id, ResourceTypes type, shared_ptr<File> = nullptr);

        virtual ~DynamicResource() = default;

    private:
        virtual bool create() = 0;
        virtual bool release() = 0;

    private:
        bool m_is_loaded;
        i32 m_counter;
    };
}