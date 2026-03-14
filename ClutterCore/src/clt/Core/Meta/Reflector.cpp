#include <clt/Core/Meta/Reflection.h>

#include "clt/Core/ActorComponent/Components.h"

namespace clt::meta
{
    static std::unordered_map<uint32_t, std::string> s_StringRegistry;

    void SetName(std::string_view name)
    {
        s_StringRegistry.emplace(entt::hashed_string{name.data(), name.size()}, name);
    }

    const std::string& GetName(const uint32_t hash)
    {
        return s_StringRegistry[hash];
    }

    void Initialize()
    {

            // ------ COMPONENTS ------


        // --- TRANSFORM ---

        Reflector<Transform>("Transform")
            .Data<&Transform::position>("position")
            .Data<&Transform::rotation>("rotation")
            .Data<&Transform::scale>("scale");


        Reflector<Sprite>("Sprite")
            .Data<&Sprite::textureName>("textureName")
            .Data<&Sprite::flipX>("flipX")
            .Data<&Sprite::flipY>("flipY")
            .Data<&Sprite::tint>("tint")
            .Data<&Sprite::zIndex>("zIndex");

        // ------ STD -------

        Reflector<std::string>("string");

        // ------ MATHS ------


        // --- VECTOR 3 ---

        Reflector<Vector3>("Vector3")
            .Data<&Vector3::x>("x")
            .Data<&Vector3::y>("y")
            .Data<&Vector3::z>("z");

        // --- VECTOR 2 ---

        Reflector<Vector2>("Vector2")
            .Data<&Vector2::x>("x")
            .Data<&Vector2::y>("y");

        // --- COLOR ---

        Reflector<Color>("Color")
            .Data<&Color::x>("r")
            .Data<&Color::y>("g")
            .Data<&Color::z>("b")
            .Data<&Color::w>("a");
    }
}
