#ifndef CLUTTERENGINE_RENDERER2D_H
#define CLUTTERENGINE_RENDERER2D_H

namespace clt::graphic
{
    class RendererAPI;
    class Renderer2D
    {
        RendererAPI* mRenderer;

        public:
        explicit Renderer2D(RendererAPI* API);
    };
}

#endif //CLUTTERENGINE_RENDERER2D_H