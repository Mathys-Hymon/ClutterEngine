#ifndef CLUTTERENGINE_OPENGLCONTEXT_H
#define CLUTTERENGINE_OPENGLCONTEXT_H

#include <clt/Renderer/GraphicContext.h>

#ifdef CLUTTER_PLATFORM_WINDOWS

struct GLFWwindow;

namespace clt::graphic
{
    class OpenGLContext final : public context
    {
        GLFWwindow* mWindowHandle;

    public:
        explicit OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    };
}

#endif
#endif
