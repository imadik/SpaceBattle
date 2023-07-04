#pragma once

namespace SpaceBattle
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
    };
}
