#pragma once

namespace SpaceBattle
{
    enum class CommandType : unsigned int
    {
        MOVE,
        ROTATE,
        LOG,
        REPEAT,
    };

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
        virtual CommandType getType() const = 0;
    };
}
