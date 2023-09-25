#pragma once

namespace SpaceBattle
{
    enum class CommandType : unsigned int
    {
        MOVE,
        ROTATE,
        LOG,
        REPEAT,
        CHECK_FUEL,
        BURN_FUEL,
        CHANGE_VELOCITY,
        MACRO_COMMAND,
    };

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
        virtual CommandType getType() const = 0;
    };
}
