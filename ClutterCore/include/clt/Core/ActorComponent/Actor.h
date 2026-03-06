#ifndef CLUTTERENGINE_ACTOR_H
#define CLUTTERENGINE_ACTOR_H
#include <cstdint>
#include <entt/entt.hpp>

namespace clt
{
    class Level;
    class Actor
    {
        entt::entity mID{0};
        Level* mLevel;

        public:

        Actor() = delete;
        explicit Actor(const entt::entity id, Level* level) : mID(id), mLevel(level) {};

        virtual ~Actor() {}

        entt::entity GetID();

        template<typename T, typename... Args>
        T* AddComponent(Args&&... args);
    };
}
#endif //CLUTTERENGINE_ACTOR_H