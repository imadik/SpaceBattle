#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IRotable.h"

namespace SpaceBattle
{
    class Rotate : public ICommand
    {
    public:
        explicit Rotate(IRotable& rotable);
        void execute();
    private:
        IRotable& mRotable;
    };
}
