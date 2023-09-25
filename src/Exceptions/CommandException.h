#pragma once

#include "Interfaces/IException.h"

namespace SpaceBattle
{
    class CommandException: public IException
    {
    public:
        ExceptionType getType() const 
        {
            return ExceptionType::MACRO_COMMAND;
        };
    };
}
