#ifndef CLUTTERENGINE_REFLECTION_H
#define CLUTTERENGINE_REFLECTION_H

#include <entt/entt.hpp>
#include <entt/meta/factory.hpp>

namespace clt::meta
{
    void SetName(std::string_view name);
    const std::string& GetName(uint32_t hash);


    template<typename T>
    class Reflector
    {
        public:

        explicit Reflector(const std::string_view name, const bool isComponent = true)
        {
            SetName(name);
            auto hashedString = entt::hashed_string{name.data(), name.size()};

            auto factory = entt::meta_factory<T>{}.type(hashedString);

            if (isComponent)
            {
                factory.template func<&AttachComponent>(entt::hashed_string{"AttachComponent"})
                       .template func<&AddDefaultComponent>(entt::hashed_string{"AddDefaultComponent"})
                       .template func<&RemoveComponent>(entt::hashed_string{"RemoveComponent"});
            }
        }

        template<auto MemberPtr>
        Reflector& Data(const std::string_view name)
        {
            SetName(name);
            auto hashedString = entt::hashed_string{name.data(), name.size()};
            entt::meta_factory<T>{}.template data<MemberPtr>(hashedString);
            return *this;
        }

        static void AttachComponent(entt::registry* registry, entt::entity actor, T& component)
        {
            registry->emplace_or_replace<T>(actor, component);
        }

        static void AddDefaultComponent(entt::registry* registry, const entt::entity actor)
        {
            registry->emplace_or_replace<T>(actor);
        }

        static void RemoveComponent(entt::registry* registry, const entt::entity actor)
        {
            registry->remove<T>(actor);
        }
    };

    template<typename T>
    Reflector<T> Reflect(std::string_view name)
    {
        return Reflector<T>(name);
    }

    void Initialize();
}

#endif //CLUTTERENGINE_REFLECTION_H