#pragma once
#include "clt/Core/Math/Color.h"

namespace clt::graphic
{
        enum class RendererAPIType
        {
                None = 0,
                OpenGL = 1,
                Vulkan = 2,
        };

        class RendererAPI
        {
                static RendererAPIType s_API;

        public:
                virtual ~RendererAPI();

                virtual void Init() = 0;
                virtual void SetViewport(const uint32_t x,const uint32_t y,const uint32_t width,const uint32_t height) = 0;
                virtual void SetClearColor(const Color& color) = 0;
                virtual void Clear() = 0;

                inline static RendererAPIType& GetAPI() { return s_API; }
                inline static void SetAPI(const RendererAPIType api) { s_API = api; }
        };
}
