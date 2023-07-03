#pragma once

#include "Interfaces/IRotable.h"

namespace SpaceBattle
{
    class Rotate
    {
    public:
        explicit Rotate(IRotable& rotable);
        void execute();
    private:
        IRotable& mRotable;
    };
}
