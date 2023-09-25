#include "ChangeVelocity.h"
#include "Types/Direction.h"
#include <cmath>
#include <numbers>

namespace
{
    double degreesToRadians(int degrees)
    {
        return double(degrees) * (std::numbers::pi / 180);
    }
}

namespace SpaceBattle
{
    ChangeVelocity::ChangeVelocity(IVelocityChangeable& velocityChangeable) :
        mVelocityChangeable(velocityChangeable)
    {
    }

    void ChangeVelocity::execute()
    {
        const auto velocity = mVelocityChangeable.getVelocity();
        const auto angularVelocity = mVelocityChangeable.getAngularVelocity();
        Direction direction(0);
        const auto newDirection = direction.getNext(angularVelocity);
        const double cosA = std::cos(degreesToRadians(newDirection.getDirection()));
        const double sinA = std::sin(degreesToRadians(newDirection.getDirection()));
        double x = double(velocity.x) * cosA - double(velocity.y) * sinA;
        double y = double(velocity.x) * sinA + double(velocity.y) * cosA;
        PositionVector newVelocity{int(std::round(x)), int(std::round(y))};
        mVelocityChangeable.setNewVelocity(newVelocity);
    }
}
