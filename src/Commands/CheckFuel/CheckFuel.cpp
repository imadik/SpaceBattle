#include "CheckFuel.h"
#include "Exceptions/CommandException.h"

namespace SpaceBattle
{
    CheckFuel::CheckFuel(IFuelCheckable& fuelCheckable) :
        mFuelCheckable(fuelCheckable)
    {
    }

    void CheckFuel::execute()
    {
        const auto availableFuel = mFuelCheckable.getAvailableFuel();
        const auto fuelConsumption = mFuelCheckable.getFuelConsumption();
        if (fuelConsumption > availableFuel)
        {
            throw CommandException();
        }
    }
}
