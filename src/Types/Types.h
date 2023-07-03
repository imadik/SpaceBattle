#pragma once

namespace SpaceBattle
{
    struct PositionVector
    {
        int x;
        int y;
    };

    inline PositionVector operator+(const PositionVector& left, const PositionVector& right)
    {
        return {left.x + right.x, left.y + right.y};
    }

    inline bool operator==(const PositionVector& left, const PositionVector& right)
    {
        return (left.x == right.x && left.y == right.y);
    }
} // SpaceBattle
