#include "Rotate.h"

namespace SpaceBattle
{
    Rotate::Rotate(IRotable& rotable) :
        mRotable(rotable)
    {
    }

    void Rotate::execute()
    {
        mRotable.setNewDirection(mRotable.getDirection().getNext(mRotable.getAngularVelocity()));
    }
}
