#pragma once

#include <any>
#include <string>

namespace SpaceBattle
{
    class IUObject
    {
    public:
        virtual ~IUObject() = default;
        virtual std::any getProperty(const std::string& key) = 0;
        virtual void setProperty(const std::string& key, std::any object) = 0;
    };
    

    
} // SpaceBattle
