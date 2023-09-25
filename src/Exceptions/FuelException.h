#pragma once

#include "Interfaces/IException.h"

namespace SpaceBattle
{
    class FuelException: public IException
    {
    public:
        ExceptionType getType() const 
        {
            return ExceptionType::FUEL;
        };
    };
}
