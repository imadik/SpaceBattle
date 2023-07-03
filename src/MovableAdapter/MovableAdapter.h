#pragma once

#include "Interfaces/IMovable.h"
#include "Interfaces/IUObject.h"

#include <string>

namespace SpaceBattle
{
    class MovableAdapter : public IMovable
    {
    public:
        explicit MovableAdapter(IUObject& object);
        ~MovableAdapter() = default;
        PositionVector getPosition() override;
        PositionVector getVelocity() override;
        void setNewPosition(PositionVector newPosition) override;
    private:
        IUObject& mObject;
    };
} // SpaceBattle
