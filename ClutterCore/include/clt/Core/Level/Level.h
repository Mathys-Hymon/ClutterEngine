#ifndef CLUTTERENGINE_LEVEL_H
#define CLUTTERENGINE_LEVEL_H

#include <entt/entt.hpp>

namespace clt
{
    class Actor;
    class Level
    {
        entt::registry mRegistry;

    public:
        Level() = default;
        ~Level() = default;

        virtual void OnUpdate(float dt);

        Actor CreateActor();

    };
}



#endif //CLUTTERENGINE_LEVEL_H