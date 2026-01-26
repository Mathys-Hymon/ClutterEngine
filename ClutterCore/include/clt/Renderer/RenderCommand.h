#pragma once
#include "RendererAPI.h"

namespace clt
{
    namespace graphic
    {
        class RenderCommand
        {
            static RendererAPI* s_rendererAPI;

        public:
            static void Init();

            inline static void SetViewport(const uint32_t x,const uint32_t y,const uint32_t width,const uint32_t height)
            {
                if(s_rendererAPI) s_rendererAPI->SetViewport(x, y, width, height);
            }

            inline static void SetClearColor(const Color& color)
            {
                if(s_rendererAPI) s_rendererAPI->SetClearColor(color);
            }

            inline static void Clear()
            {
                if(s_rendererAPI) s_rendererAPI->Clear();
            }
        };
    }
}