#pragma once

#include "IFuelCheckable.h"

namespace SpaceBattle
{
    class IFuelBurnable : public IFuelCheckable
    {
    public:
        virtual ~IFuelBurnable() = default;
        virtual void setAvailableFuel(unsigned fuel) = 0;
    };
} // SpaceBattle
