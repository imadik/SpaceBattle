#include "ChangeVelocityAdapter.h"

namespace SpaceBattle
{
    ChangeVelocityAdapter::ChangeVelocityAdapter(IUObject& object) :
        mObject(object)
    {
    }

    PositionVector ChangeVelocityAdapter::getVelocity()
    {
        return std::any_cast<PositionVector>(mObject.getProperty("velocity"));
    }

    int ChangeVelocityAdapter::getAngularVelocity()
    {
        return std::any_cast<int>(mObject.getProperty("angular_velocity"));
    }

    void ChangeVelocityAdapter::setNewVelocity(PositionVector newVelocity)
    {
        mObject.setProperty("velocity", newVelocity);
    }
}
