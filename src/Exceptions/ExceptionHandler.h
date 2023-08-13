#pragma once

#include "Interfaces/IExceptionHandler.h"
#include "Interfaces/ICommandQueue.h"
#include "Interfaces/ICommand.h"
#include "Interfaces/IException.h"
#include "Interfaces/ILogger.h"
#include <map>
#include <memory>
#include <functional>

namespace SpaceBattle
{
    class ExceptionHandler : public IExceptionHandler
    {
    public:
        ExceptionHandler(ICommandQueue& queue, ILogger& logger);
        void handle(std::unique_ptr<ICommand> command, IException& exception) override;
    private:
        std::map<CommandType, std::map<ExceptionType, 
            std::function<std::unique_ptr<ICommand>(std::unique_ptr<ICommand>, IException&)>>> mHandlers; 
        ICommandQueue& mQueue;
        ILogger& mLogger;
    }; 
}
