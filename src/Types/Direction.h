#pragma once

namespace SpaceBattle
{
    class Direction
    {
    public:
        Direction(int direction);
        Direction getNext(int angularVelocity) const;
        bool operator==(const Direction& other) const;
    private:
        int countPositiveDirection(int direction) const;
        int mDirection{0};
    };
} // SpaceBattle
