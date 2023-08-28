#include "CheckFuelAdapter.h"

namespace SpaceBattle
{
    CheckFuelAdapter::CheckFuelAdapter(IUObject& object) :
        mObject(object)
    {
    }

    unsigned CheckFuelAdapter::getAvailableFuel() const
    {
        return std::any_cast<unsigned>(mObject.getProperty("available_fuel"));
    }

    unsigned CheckFuelAdapter::getFuelConsumption() const
    {
        return std::any_cast<unsigned>(mObject.getProperty("fuel_consumption"));
    }
}
