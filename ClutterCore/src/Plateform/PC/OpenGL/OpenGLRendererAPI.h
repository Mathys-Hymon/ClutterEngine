#ifndef CLUTTERENGINE_OPENGL_RENDERER_API_H
#define CLUTTERENGINE_OPENGL_RENDERER_API_H

#include <clt/Renderer/RendererAPI.h>

#ifdef CLUTTER_PLATFORM_WINDOWS

namespace clt::graphic
{
    class OpenGLRendererAPI final : public RendererAPI
    {
    public:
        void Init() override;
        void SetViewport(glm::uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void DrawIndexed(uint32_t indexCount);
        void SetClearColor(const Color& color) override;
        void Clear() override;
    };
}

#endif
#endif