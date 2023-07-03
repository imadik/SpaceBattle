#pragma once

#include "Interfaces/IUObject.h"
#include <gmock/gmock.h>

namespace SpaceBattleTest
{
    class MockUObject : public SpaceBattle::IUObject
    {
    public:
        MOCK_METHOD(std::any, getProperty, (const std::string&), (override));
        MOCK_METHOD(void, setProperty, (const std::string&, std::any), (override));
    };
}