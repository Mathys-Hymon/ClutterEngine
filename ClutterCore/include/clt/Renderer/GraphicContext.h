#ifndef CLUTTERENGINE_GRAPHICCONTEXT_H
#define CLUTTERENGINE_GRAPHICCONTEXT_H

namespace clt::graphic
{
    class Context
    {
    public:
        virtual ~Context() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif
