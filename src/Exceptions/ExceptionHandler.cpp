#include "ExceptionHandler.h"
#include "Commands/LogException/LogException.h"
#include "Commands/RepeatCommand/RepeatCommand.h"
#include "Commands/Rotate/Rotate.h"


namespace SpaceBattle
{
    ExceptionHandler::ExceptionHandler(ICommandQueue& queue, ILogger& logger) :
        mQueue(queue),
        mLogger(logger)
    {
        mHandlers[CommandType::MOVE][ExceptionType::FIRST] = [&](std::unique_ptr<ICommand>, IException&) 
            {
                return std::make_unique<LogException>(
                    mLogger, CommandType::MOVE, ExceptionType::FIRST);
            };
        mHandlers[CommandType::MOVE][ExceptionType::SECOND] = [&](std::unique_ptr<ICommand> cmd, IException& e) -> 
            std::unique_ptr<ICommand>
            {
                if (e.count() == 0)
                {
                    return std::make_unique<RepeatCommand>(std::move(cmd));
                }
                else
                {
                    return std::make_unique<LogException>(
                        mLogger, CommandType::MOVE, ExceptionType::SECOND);
                }
            };
        mHandlers[CommandType::ROTATE][ExceptionType::FIRST] = [&](std::unique_ptr<ICommand> cmd, IException&) 
            {
                return std::make_unique<RepeatCommand>(std::move(cmd));
            };
        mHandlers[CommandType::ROTATE][ExceptionType::SECOND] = [&](std::unique_ptr<ICommand> cmd, IException& e) -> 
            std::unique_ptr<ICommand>
            {
                if (e.count() == 0)
                {
                    return std::make_unique<RepeatCommand>(std::move(cmd));
                }
                else if (e.count() == 1)
                {
                    return std::make_unique<RepeatCommand>(std::move(cmd));
                }
                else
                {
                    return std::make_unique<LogException>(
                        mLogger, CommandType::MOVE, ExceptionType::SECOND);
                }
            };
    }

    void ExceptionHandler::handle(std::unique_ptr<ICommand> command, IException& exception)
    {
        auto commandExceptions = mHandlers.find(command->getType());
        if (commandExceptions != mHandlers.end())
        {
            auto handler = commandExceptions->second.find(exception.getType());
            if (handler != commandExceptions->second.end())
            {
                mQueue.push(handler->second(std::move(command), exception));
            }
        }
    }
}
