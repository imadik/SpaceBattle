#pragma once

#include "Types/Types.h"

namespace SpaceBattle
{
    class IVelocityChangeable
    {
    public:
        virtual ~IVelocityChangeable() = default;
        virtual PositionVector getVelocity() = 0;
        virtual int getAngularVelocity() = 0;
        virtual void setNewVelocity(PositionVector newVeloctity) = 0;
    };
} // SpaceBattle
