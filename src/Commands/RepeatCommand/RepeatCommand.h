#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IException.h"
#include <memory>
#include <string>

namespace SpaceBattle
{
    class RepeatCommand : public ICommand
    {
    public:
        RepeatCommand(std::unique_ptr<ICommand> command);
        void execute() override;

        CommandType getType() const override
        {
            return mCommand->getType();
        }

    private:
        std::unique_ptr<ICommand> mCommand;
    };
}
