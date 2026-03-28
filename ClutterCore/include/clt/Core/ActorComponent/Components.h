#ifndef CLUTTERENGINE_COMPONENTS_H
#define CLUTTERENGINE_COMPONENTS_H

#include <clt/Core/Math/Math.h>

namespace clt
{
    struct TagComponent
    {
        std::string tagName{"Default Actor"};
    };

    struct DisabledComponent {};

    struct Transform
    {
        Vector3 position{0.0f};
        Vector3 rotation{0.0f};
        Vector3 scale{1.0f};
    };

    // ----------- GRAPHIC ----------- //

    struct Sprite
    {
        std::string textureName;

        Color tint{0};
        uint32_t zIndex{0};
        bool flipX{false};
        bool flipY{false};
    };

    // ----------- HUD ----------- //

    struct ViewPortPosition
    {
        Vector2 position{0.0f};
        float rotation{0.0f};
        Vector2 scale{1.0f};
    };
}

#endif //CLUTTERENGINE_COMPONENTS_H