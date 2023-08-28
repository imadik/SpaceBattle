#pragma once

#include "Interfaces/IFuelBurnable.h"
#include "Interfaces/IUObject.h"

namespace SpaceBattle
{
    class BurnFuelAdapter : public IFuelBurnable
    {
    public:
        explicit BurnFuelAdapter(IUObject& object);
        ~BurnFuelAdapter() = default;
        unsigned getAvailableFuel() const override;
        unsigned getFuelConsumption() const override;
        void setAvailableFuel(unsigned fuel) override;

    private:
        IUObject& mObject;
    };
} // SpaceBattle
