#pragma once
#include <memory>

#include "RendererAPI.h"

namespace clt::graphic
{
    class Renderer2D;
    class Renderer3D;

    class Renderer
    {
        std::unique_ptr<RendererAPI> mRendererAPI{nullptr};

        std::unique_ptr<Renderer2D> mRenderer2D{nullptr};
        std::unique_ptr<Renderer3D> mRenderer3D{nullptr};

    public:
        Renderer() = default;
        ~Renderer() = default;

        void Init();
    };
}