#ifndef CLUTTERENGINE_LEVEL_H
#define CLUTTERENGINE_LEVEL_H

#include <entt/entt.hpp>

namespace clt
{
    class Level
    {
        entt::registry& mRegistry;

        public:

        virtual void OnUpdate(float dt);



    };
}



#endif //CLUTTERENGINE_LEVEL_H