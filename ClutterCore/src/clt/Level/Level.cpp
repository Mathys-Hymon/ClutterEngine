#include "clt/Core/Level/Level.h"
#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"

void clt::Level::OnBeginPlay()
{
}

void clt::Level::UpdatePhysics(float dt)
{
}

void clt::Level::UpdateScripts(float dt)
{
}

void clt::Level::Render()
{
}

void clt::Level::OnEndPlay()
{
}

clt::Actor clt::Level::CreateActor(const std::string& name)
{
    auto tempActor = CreateActor();
    //tempActor.AddComponent<TagComponent>().tagName = name;

    return tempActor;
}

clt::Actor clt::Level::CreateActor()
{
    const auto actorID = mRegistry.create();
    return clt::Actor(actorID, this);
}
