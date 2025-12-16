#pragma once
#include <clt/Renderer/GraphicsContext.h>

struct GLFWwindow;

namespace clt
{
    class OpenGLContext : public GraphicsContext
    {
        GLFWwindow* mWindowHandle;
        public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    };
}