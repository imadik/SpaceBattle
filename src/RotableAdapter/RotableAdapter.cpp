
#include "RotableAdapter.h"

namespace SpaceBattle
{
    RotableAdapter::RotableAdapter(IUObject& object) :
        mObject(object)
    {
    }

    Direction RotableAdapter::getDirection()
    {
        return std::any_cast<Direction>(mObject.getProperty("direction"));
    }

    int RotableAdapter::getAngularVelocity()
    {
        return std::any_cast<int>(mObject.getProperty("angular_velocity"));
    }

    void RotableAdapter::setNewDirection(Direction newDirection)
    {
        mObject.setProperty("direction", newDirection);
    }
}
