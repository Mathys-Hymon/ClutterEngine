#ifndef CLUTTERENGINE_ACTOR_H
#define CLUTTERENGINE_ACTOR_H
#include <cstdint>
#include <entt/entt.hpp>

#include "clt/Core/Debug/Log.h"
#include "clt/Core/Level/Level.h"

namespace clt
{
    class Actor
    {
        entt::entity mID{0};
        Level* mLevel;

    public:

        Actor() = delete;
        explicit Actor(const entt::entity id, Level* level) : mID(id), mLevel(level) {};

        virtual ~Actor() = default;

        entt::entity GetID();

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        template<typename T>
        T* GetComponent();

        template<typename T>
        bool HasComponent() const;
    };

    template <typename T, typename ... Args>
    T& Actor::AddComponent(Args&&... args)
    {
        CLT_CORE_ASSERT(mLevel, "Actor has no Level attached");

        auto& r = mLevel->Registry();

        auto& comp = r.emplace<T>(mID, std::forward<Args>(args)...);

        return comp;
    }

    template <typename T>
    T* Actor::GetComponent()
    {
        CLT_CORE_ASSERT(mLevel, "Actor has no Level attached");

        auto& r = mLevel->Registry();

        if(HasComponent<T>())
        {
            auto& comp = r.get<T>(mID);
            return &comp;
        }

        return nullptr;

    }

    template <typename T>
    bool Actor::HasComponent() const
    {
        CLT_CORE_ASSERT(mLevel, "Actor has no Level attached");

        auto& r = mLevel->Registry();

        return r.all_of<T>(mID);
    }
}
#endif //CLUTTERENGINE_ACTOR_H