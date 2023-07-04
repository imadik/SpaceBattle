#include "Direction.h"

namespace SpaceBattle
{
    namespace
    {
        static constexpr int DIRECTION_NUM = 360;
    }

    Direction::Direction(int direction):
        mDirection(countPositiveDirection(direction))
    {
    }

    Direction Direction::getNext(int angularVelocity) const
    {
        return Direction(mDirection + angularVelocity);
    }

    bool Direction::operator==(const Direction& other) const
    {
        return mDirection == other.mDirection;
    }

    int Direction::countPositiveDirection(int direction) const
    {
        return (DIRECTION_NUM + (direction % DIRECTION_NUM)) % DIRECTION_NUM;
    }

} // SpaceBattle
