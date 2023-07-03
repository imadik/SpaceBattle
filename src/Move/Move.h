#pragma once

#include "Interfaces/IMovable.h"

namespace SpaceBattle
{
    class Move
    {
    public:
        explicit Move(IMovable& movable);
        void execute();
    private:
        IMovable& mMovable;
    };
}
