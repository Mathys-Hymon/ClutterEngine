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

        virtual void OnUpdate(const float dt);

        Actor CreateActor();
        entt::registry& Registry() { return mRegistry; }

    };
}

#endif //CLUTTERENGINE_LEVEL_H