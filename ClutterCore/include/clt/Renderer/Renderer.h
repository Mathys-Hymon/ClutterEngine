#pragma once
#include "RendererAPI.h"

namespace clt::graphic
{
    class Renderer
    {
        static RendererAPIType s_RendererAPI;

    public:
        inline static RendererAPIType GetRendererAPI() { return s_RendererAPI; }
        inline static void SetRendererAPI(const RendererAPIType api) { s_RendererAPI = api; }
    };
}