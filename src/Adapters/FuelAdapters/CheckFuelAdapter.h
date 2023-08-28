#pragma once

#include "Interfaces/IFuelCheckable.h"
#include "Interfaces/IUObject.h"

namespace SpaceBattle
{
    class CheckFuelAdapter : public IFuelCheckable
    {
    public:
        explicit CheckFuelAdapter(IUObject& object);
        ~CheckFuelAdapter() = default;
        unsigned getAvailableFuel() const override;
        unsigned getFuelConsumption() const override;
    private:
        IUObject& mObject;
    };
} // SpaceBattle
