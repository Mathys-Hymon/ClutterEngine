#pragma once
#include <clt/Renderer/GraphicContext.h>

struct GLFWwindow;

namespace clt
{
    namespace graphic
    {
        class OpenGLContext : public context
        {
            GLFWwindow* mWindowHandle;

        public:
            OpenGLContext(GLFWwindow* windowHandle);

            void Init() override;
            void SwapBuffers() override;
        };
    }
}