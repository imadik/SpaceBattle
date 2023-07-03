#pragma once

#include "Types/Direction.h"

namespace SpaceBattle
{
    class IRotable
    {
    public:
        virtual ~IRotable() = default;
        virtual Direction getDirection() = 0;
        virtual int getAngularVelocity() = 0;
        virtual void setNewDirection(Direction newDirection) = 0;
    };
} // SpaceBattle
