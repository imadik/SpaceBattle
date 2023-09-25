#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IVelocityChangeable.h"

namespace SpaceBattle
{
    class ChangeVelocity : public ICommand
    {
    public:
        explicit ChangeVelocity(IVelocityChangeable& velocityChangeable);
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::CHANGE_VELOCITY;
        }
    private:
        IVelocityChangeable& mVelocityChangeable;
    };
}
