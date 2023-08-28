#pragma once

namespace SpaceBattle
{
    class IFuelCheckable
    {
    public:
        virtual ~IFuelCheckable() = default;
        virtual unsigned getAvailableFuel() const = 0;
        virtual unsigned getFuelConsumption() const = 0;
    };
} // SpaceBattle
