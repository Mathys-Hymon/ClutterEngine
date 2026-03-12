#ifndef CLUTTERENGINE_REFLECTION_H
#define CLUTTERENGINE_REFLECTION_H

#include <entt/entt.hpp>
#include <entt/meta/factory.hpp>

namespace clt::meta
{
    template<typename T>
    class Reflector
    {

        public:

        explicit Reflector(const std::string_view name)
        {
            auto hashedString = entt::hashed_string{name.data(), name.size()};
            entt::meta_factory<T>{}.type(hashedString);
        }

        template<auto MemberPtr>
        Reflector& Data(const std::string_view name)
        {
            auto hashedString = entt::hashed_string{name.data(), name.size()};
            entt::meta_factory<T>{}.template data<MemberPtr>(hashedString);
            return *this;
        }
    };

    void SetName(std::string_view name);
    const std::string& GetName(uint32_t hash);

    template<typename T>
    Reflector<T> Reflect(std::string_view name)
    {
        return Reflector<T>(name);
    }

    void Initialize();
}

#endif //CLUTTERENGINE_REFLECTION_H