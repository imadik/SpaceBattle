#include "Commands/LogException/LogException.h"
#include "Commands/RepeatCommand/RepeatCommand.h"
#include "MockObjects/MockObjects.h"
#include "Exceptions/ExceptionHandler.h"
#include <gtest/gtest.h>

namespace SpaceBattleTest
{
    using ::testing::_;
    using ::testing::Return;

    class ExceptionsTest : public ::testing::Test
    {
    public:
        ExceptionsTest() = default;
    };

    TEST_F(ExceptionsTest, 4_logger_command)
    {
        MockLogger mockLogger;
        EXPECT_CALL(mockLogger, log("Command: '0', Exception: '0'.")).Times(1);
        SpaceBattle::LogException logException(mockLogger, SpaceBattle::CommandType::MOVE, SpaceBattle::ExceptionType::FIRST);
        logException.execute();
    }

    TEST_F(ExceptionsTest, 5_logger_command_handler)
    {
        MockLogger mockLogger;
        MockCommandQueue mockCommandQueue;
        std::unique_ptr<MockCommand> command = std::make_unique<MockCommand>();
        MockException exception;
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::LOG);
            });
        EXPECT_CALL(*command, getType()).Times(1).WillOnce(Return(SpaceBattle::CommandType::MOVE));
        EXPECT_CALL(exception, getType()).Times(1).WillOnce(Return(SpaceBattle::ExceptionType::FIRST));
        SpaceBattle::ExceptionHandler exceptionHandler(mockCommandQueue, mockLogger);
        exceptionHandler.handle(std::move(command), exception);
    }

    TEST_F(ExceptionsTest, 6_repeat_command)
    {
        std::unique_ptr<MockCommand> command = std::make_unique<MockCommand>();
        EXPECT_CALL(*command, execute()).Times(1);
        SpaceBattle::RepeatCommand repeatCommand(std::move(command));
        repeatCommand.execute();
    }

    TEST_F(ExceptionsTest, 7_repeat_command_handler)
    {
        MockLogger mockLogger;
        MockCommandQueue mockCommandQueue;
        std::unique_ptr<MockCommand> command = std::make_unique<MockCommand>();
        EXPECT_CALL(*command, getType()).Times(2).WillRepeatedly(Return(SpaceBattle::CommandType::ROTATE));
        MockException exception;
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::ROTATE);
            });
        EXPECT_CALL(exception, getType()).Times(1).WillOnce(Return(SpaceBattle::ExceptionType::FIRST));
        SpaceBattle::ExceptionHandler exceptionHandler(mockCommandQueue, mockLogger);
        exceptionHandler.handle(std::move(command), exception);
    }

    TEST_F(ExceptionsTest, 8_repeat_and_log_command_handler)
    {
        MockLogger mockLogger;
        MockCommandQueue mockCommandQueue;
        std::unique_ptr<MockCommand> command = std::make_unique<MockCommand>();
        EXPECT_CALL(*command, getType()).Times(3).WillRepeatedly(Return(SpaceBattle::CommandType::MOVE));
        MockException exception;
        std::unique_ptr<SpaceBattle::ICommand> tempCmd;
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([&](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::MOVE);
                tempCmd = std::move(command);
            });
        EXPECT_CALL(exception, getType()).Times(2).WillRepeatedly(Return(SpaceBattle::ExceptionType::SECOND));
        SpaceBattle::ExceptionHandler exceptionHandler(mockCommandQueue, mockLogger);
        exceptionHandler.handle(std::move(command), exception);
        exception.repeat();
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::LOG);
            });
        exceptionHandler.handle(std::move(tempCmd), exception);
    }

    TEST_F(ExceptionsTest, 9_double_repeat_and_log_command_handler)
    {
        MockLogger mockLogger;
        MockCommandQueue mockCommandQueue;
        std::unique_ptr<MockCommand> command = std::make_unique<MockCommand>();
        EXPECT_CALL(*command, getType()).Times(5).WillRepeatedly(Return(SpaceBattle::CommandType::ROTATE));
        MockException exception;
        std::unique_ptr<SpaceBattle::ICommand> tempCmd;
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([&](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::ROTATE);
                tempCmd = std::move(command);
            });
        EXPECT_CALL(exception, getType()).Times(3).WillRepeatedly(Return(SpaceBattle::ExceptionType::SECOND));
        SpaceBattle::ExceptionHandler exceptionHandler(mockCommandQueue, mockLogger);
        exceptionHandler.handle(std::move(command), exception);
        std::unique_ptr<SpaceBattle::ICommand> tempCmd2;
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([&](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::ROTATE);
                tempCmd2 = std::move(command);
            });
        exception.repeat();
        exceptionHandler.handle(std::move(tempCmd), exception);
        exception.repeat();
        EXPECT_CALL(mockCommandQueue, push).Times(1).
            WillOnce([](std::unique_ptr<SpaceBattle::ICommand> command) {
                EXPECT_EQ(command->getType(), SpaceBattle::CommandType::LOG);
            });
        exceptionHandler.handle(std::move(tempCmd2), exception);
    }
}
