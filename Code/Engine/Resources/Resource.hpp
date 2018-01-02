#pragma once

#include "ResourceTypes.hpp"
#include "Engine/Common/File.hpp"
#include "Engine/Common/Object.hpp"

namespace cp
{
    class Resource : public Object
    {
    public:
        virtual bool upload();
        virtual bool parse();

        void set_file(const shared_ptr<File>& file);
        shared_ptr<File> get_file() const;
    
    protected:
        explicit Resource(int id, ResourceTypes type, shared_ptr<File> file = nullptr);

        virtual ~Resource() = default;
    
    protected:
        shared_ptr<File> m_file;

    private:
        ResourceTypes m_type;
    };
}