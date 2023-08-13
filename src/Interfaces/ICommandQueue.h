#pragma once

#include "ICommand.h"
#include <memory>

namespace SpaceBattle
{
    class ICommandQueue
    {
    public:
        virtual std::unique_ptr<ICommand> pop() = 0;
        virtual void push(std::unique_ptr<ICommand> command) = 0;
    };
}
