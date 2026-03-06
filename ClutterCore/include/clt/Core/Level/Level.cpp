#include "Level.h"
#include "clt/Core/ActorComponent/Actor.h"


void clt::Level::OnUpdate(float dt)
{
}

clt::Actor clt::Level::CreateActor()
{
    const auto actorID = mRegistry.create();
    return clt::Actor(actorID, this);
}
