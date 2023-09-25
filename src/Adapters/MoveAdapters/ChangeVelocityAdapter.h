#pragma once

#include "Interfaces/IVelocityChangeable.h"
#include "Interfaces/IUObject.h"

#include <string>

namespace SpaceBattle
{
    class ChangeVelocityAdapter : public IVelocityChangeable
    {
    public:
        explicit ChangeVelocityAdapter(IUObject& object);
        ~ChangeVelocityAdapter() = default;
        PositionVector getVelocity() override;
        int getAngularVelocity() override;
        void setNewVelocity(PositionVector newVelocity) override;
    private:
        IUObject& mObject;
    };
} // SpaceBattle
