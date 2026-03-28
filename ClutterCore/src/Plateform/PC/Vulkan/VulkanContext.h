#pragma once
#include <clt/Renderer/GraphicContext.h>

struct GLFWwindow;

namespace clt
{
    namespace graphic
    {
        class VulkanContext final : public context
        {
            GLFWwindow* mWindowHandle;

        public:
            explicit VulkanContext(GLFWwindow* windowHandle);

            void Init() override;
            void SwapBuffers() override;
        };
    }
}
