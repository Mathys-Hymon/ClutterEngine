#ifndef CLUTTERENGINE_RENDERER3D_H
#define CLUTTERENGINE_RENDERER3D_H

namespace clt::graphic
{
    class RendererAPI;
    class Renderer3D
    {
        RendererAPI* mRenderer;

        public:
        explicit Renderer3D(RendererAPI* api);
    };
}


#endif //CLUTTERENGINE_RENDERER3D_H