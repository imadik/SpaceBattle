#include "MacroCommand.h"
#include "Exceptions/CommandException.h"

namespace SpaceBattle
{
    MacroCommand::MacroCommand(std::vector<std::unique_ptr<ICommand>> commands) :
        mCommands(std::move(commands))
    {
    }

    void MacroCommand::execute()
    {
        try
        {
            for (auto& command : mCommands)
            {
                command->execute();
            }
        }
        catch(IException& e)
        {
            throw CommandException();
        }
    }
}
