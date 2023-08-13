#pragma once

#include <string>

namespace SpaceBattle
{
    class ILogger
    {
    public:
        virtual void log(const std::string& str) = 0;
    };
}
