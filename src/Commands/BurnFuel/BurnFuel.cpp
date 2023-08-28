#include "BurnFuel.h"
#include "Exceptions/CommandException.h"

namespace SpaceBattle
{
    BurnFuel::BurnFuel(IFuelBurnable& fuelBurnable) :
        mFuelBurnable(fuelBurnable)
    {
    }

    void BurnFuel::execute()
    {
        const auto availableFuel = mFuelBurnable.getAvailableFuel();
        const auto fuelConsumption = mFuelBurnable.getFuelConsumption();
        if (fuelConsumption > availableFuel)
        {
            throw CommandException();
        }
        mFuelBurnable.setAvailableFuel(availableFuel - fuelConsumption);
    }
}
