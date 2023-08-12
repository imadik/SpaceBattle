#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IRotable.h"

namespace SpaceBattle
{
    class Rotate : public ICommand
    {
    public:
        explicit Rotate(IRotable& rotable);
        Rotate(const Rotate&) = default;
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::ROTATE;
        }
    private:
        IRotable& mRotable;
    };
}
