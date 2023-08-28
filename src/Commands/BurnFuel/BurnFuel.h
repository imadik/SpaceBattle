#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IFuelBurnable.h"

namespace SpaceBattle
{
    class BurnFuel : public ICommand
    {
    public:
        explicit BurnFuel(IFuelBurnable& fuelBurnable);
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::BURN_FUEL;
        }
    private:
        IFuelBurnable& mFuelBurnable;
    };
}
