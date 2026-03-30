#ifndef CLUTTERENGINE_GRAPHICCONTEXT_H
#define CLUTTERENGINE_GRAPHICCONTEXT_H

namespace clt
{
    namespace graphic
    {
        class context
        {
        public:
            virtual ~context() = default;

            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
        };
    }
}

#endif
