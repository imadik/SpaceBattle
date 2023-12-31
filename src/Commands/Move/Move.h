#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IMovable.h"

namespace SpaceBattle
{
    class Move : public ICommand
    {
    public:
        explicit Move(IMovable& movable);
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::MOVE;
        }
    private:
        IMovable& mMovable;
    };
}
