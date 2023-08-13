#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IException.h"
#include "Interfaces/ILogger.h"
#include <string>

namespace SpaceBattle
{
    class LogException : public ICommand
    {
    public:
        explicit LogException(ILogger& logger, CommandType command, ExceptionType exception);
        void execute() override;
        CommandType getType() const override
        {
            return CommandType::LOG;
        }
    private:
        ILogger& mLogger;
        std::string mStr;
    };
}
