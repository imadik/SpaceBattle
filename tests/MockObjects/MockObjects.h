#pragma once

#include "Interfaces/IUObject.h"
#include "Interfaces/ILogger.h"
#include "Interfaces/ICommandQueue.h"
#include "Interfaces/ICommand.h"
#include "Interfaces/IException.h"
#include <gmock/gmock.h>

namespace SpaceBattleTest
{
    class MockUObject : public SpaceBattle::IUObject
    {
    public:
        MOCK_METHOD(std::any, getProperty, (const std::string&), (override));
        MOCK_METHOD(void, setProperty, (const std::string&, std::any), (override));
    };

    class MockLogger : public SpaceBattle::ILogger
    {
    public:
        MOCK_METHOD(void, log, (const std::string& str), (override));
    };

    class MockCommandQueue : public SpaceBattle::ICommandQueue
    {
    public:
        MOCK_METHOD(void, push, (std::unique_ptr<SpaceBattle::ICommand> command), (override));
        MOCK_METHOD(std::unique_ptr<SpaceBattle::ICommand>, pop, (), (override));
    };

    class MockCommand : public SpaceBattle::ICommand
    {
    public:
        MOCK_METHOD(void, execute, (), (override));
        MOCK_METHOD(SpaceBattle::CommandType, getType, (), (const, override));
    };

    class MockException : public SpaceBattle::IException
    {
    public:
        MOCK_METHOD(SpaceBattle::ExceptionType, getType, (), (const, override));
    };
}