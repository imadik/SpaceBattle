#include "RepeatCommand.h"

namespace SpaceBattle
{
    RepeatCommand::RepeatCommand(std::unique_ptr<ICommand> command) :
        mCommand(std::move(command))
    {
    }

    void RepeatCommand::execute()
    {
        try
        {
            mCommand->execute();
        }
        catch(IException& e)
        {
            e.repeat();
            throw;
        }
    }
}
