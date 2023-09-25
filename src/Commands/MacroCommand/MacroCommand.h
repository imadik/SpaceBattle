#pragma once

#include "Interfaces/ICommand.h"
#include "Interfaces/IException.h"
#include <memory>
#include <vector>

namespace SpaceBattle
{
    class MacroCommand : public ICommand
    {
    public:
        MacroCommand(std::vector<std::unique_ptr<ICommand>> commands);
        void execute() override;

        CommandType getType() const override
        {
            return CommandType::MACRO_COMMAND;
        }

    private:
        std::vector<std::unique_ptr<ICommand>> mCommands;
    };
}
