#include "LogException.h"

namespace SpaceBattle
{
    LogException::LogException(ILogger& logger, CommandType command, ExceptionType exception) :
        mLogger(logger)
    {
        mStr = "Command: '" + std::to_string(static_cast<unsigned int>(command)) + 
            "', Exception: '" + std::to_string(static_cast<unsigned int>(exception)) + "'.";
    }

    void LogException::execute()
    {
        mLogger.log(mStr);
    }
}
