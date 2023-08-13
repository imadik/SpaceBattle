#pragma once

#include "ICommand.h"
#include "IException.h"
#include <memory>

namespace SpaceBattle
{
    class IExceptionHandler
    {
    public:
        virtual void handle(std::unique_ptr<ICommand> command, IException& exception) = 0;
        virtual ~IExceptionHandler() = default;
    }; 
    
}
