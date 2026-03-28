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
        virtual ~Level() = default;

        void OnBeginPlay();

        void UpdatePhysics(float dt);
        void UpdateScripts(float dt);
        void Render();

        void OnEndPlay();

        Actor CreateActor(const std::string& name );
        Actor CreateActor();
        entt::registry& Registry() { return mRegistry; }

    };
}

#endif //CLUTTERENGINE_LEVEL_H