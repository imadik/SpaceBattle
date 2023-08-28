#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IFuelCheckable.h"

namespace SpaceBattle
{
    class CheckFuel : public ICommand
    {
    public:
        explicit CheckFuel(IFuelCheckable& fuelCheckable);
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::CHECK_FUEL;
        }
    private:
        IFuelCheckable& mFuelCheckable;
    };
}
