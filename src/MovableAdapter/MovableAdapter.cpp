#include "MovableAdapter.h"

namespace SpaceBattle
{
    MovableAdapter::MovableAdapter(IUObject& object) :
        mObject(object)
    {
    }

    PositionVector MovableAdapter::getPosition()
    {
        return std::any_cast<PositionVector>(mObject.getProperty("position"));
    }

    PositionVector MovableAdapter::getVelocity()
    {
        return std::any_cast<PositionVector>(mObject.getProperty("velocity"));
    }

    void MovableAdapter::setNewPosition(PositionVector newPosition)
    {
        mObject.setProperty("position", newPosition);
    }
}
