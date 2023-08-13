#include "Move.h"

namespace SpaceBattle
{
    Move::Move(IMovable& movable) :
        mMovable(movable)
    {
    }

    void Move::execute()
    {
        mMovable.setNewPosition(mMovable.getPosition() + mMovable.getVelocity());
    }
}
