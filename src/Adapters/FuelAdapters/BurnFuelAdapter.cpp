#include "BurnFuelAdapter.h"

namespace SpaceBattle
{
    BurnFuelAdapter::BurnFuelAdapter(IUObject& object) :
        mObject(object)
    {
    }

    unsigned BurnFuelAdapter::getAvailableFuel() const
    {
        return std::any_cast<unsigned>(mObject.getProperty("available_fuel"));
    }

    unsigned BurnFuelAdapter::getFuelConsumption() const
    {
        return std::any_cast<unsigned>(mObject.getProperty("fuel_consumption"));
    }

    void BurnFuelAdapter::setAvailableFuel(unsigned fuel)
    {
        mObject.setProperty("available_fuel", fuel);
    }
}
