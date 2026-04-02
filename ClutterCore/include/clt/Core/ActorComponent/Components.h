#ifndef CLUTTERENGINE_COMPONENTS_H
#define CLUTTERENGINE_COMPONENTS_H

#include <clt/Core/Math/Math.h>
#include <clt/Renderer/Framebuffer/Framebuffer.h>


namespace clt
{
    namespace graphic
    {
        class Framebuffer;
    }

    struct TexturePath { std::string path; };
    struct MeshPath { std::string path; };

    struct ClampedInt { int value, min, max; };
    struct ClampedFloat { float value, min, max; };

    struct Name
    {
        std::string name{"Default Actor"};
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
        TexturePath textureName;

        Color tint{0};
        uint32_t zIndex{0};
        bool flipX{false};
        bool flipY{false};
    };

    enum class CameraViewMode
    {
        Orthographic,
        Perspective
    };

    struct Camera
    {
        std::shared_ptr<graphic::Framebuffer> framebuffer{nullptr};
        CameraViewMode viewMode{CameraViewMode::Perspective};
        float aspectRatio{1.77f};
        float nearPlane{1.0f};
        float farPlane{1.0f};
        float fov{90.0f};
        bool isDirty{true};
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