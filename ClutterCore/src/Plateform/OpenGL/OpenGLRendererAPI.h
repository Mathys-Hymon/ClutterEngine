#pragma once
#include <clt/Renderer/RendererAPI.h>

namespace clt
{
    namespace graphic
    {
        class OpenGLRendererAPI final : public RendererAPI
        {
        public:
            void Init() override;
            void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
            void SetClearColor(const Color& color) override;
            void Clear() override;
        };
    }
}