#pragma once

#include "ResourceTypes.hpp"
#include "Engine/Common/Object.hpp"
#include "Engine/Common/File/File.hpp"

namespace cp
{
    class Resource : public Object
    {
    public:
        virtual bool upload();
        virtual bool parse();

        void set_file(const shared_ptr<File>& file);
        
        shared_ptr<File> get_file() const;
        ResourceTypes get_type() const;
    
    protected:
        explicit Resource(i32 id, ResourceTypes type, shared_ptr<File> file = nullptr);

        virtual ~Resource() = default;
    
    protected:
        shared_ptr<File> m_file;

    private:
        ResourceTypes m_type;
    };
}