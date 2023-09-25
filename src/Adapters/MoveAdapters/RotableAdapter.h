#pragma once

#include "Interfaces/IRotable.h"
#include "Interfaces/IUObject.h"

#include <string>

namespace SpaceBattle
{
    class RotableAdapter : public IRotable
    {
    public:
        explicit RotableAdapter(IUObject& object);
        ~RotableAdapter() = default;
        Direction getDirection() override;
        int getAngularVelocity() override;
        void setNewDirection(Direction newDirection) override;
    private:
        IUObject& mObject;
    };
} // SpaceBattle
