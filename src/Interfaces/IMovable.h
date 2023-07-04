#pragma once

#include "Types/Types.h"

namespace SpaceBattle
{
    class IMovable
    {
    public:
        virtual ~IMovable() = default;
        virtual PositionVector getPosition() = 0;
        virtual PositionVector getVelocity() = 0;
        virtual void setNewPosition(PositionVector newPosition) = 0;
    };
} // SpaceBattle
