#ifndef CLUTTERENGINE_VULKAN_CONTEXT_H
#define CLUTTERENGINE_VULKAN_CONTEXT_H

#include <clt/Renderer/GraphicContext.h>

#ifdef CLUTTER_PLATFORM_WINDOWS

struct GLFWwindow;

namespace clt
{
    namespace graphic
    {
        class VulkanContext final : public Context
        {
            GLFWwindow* mWindowHandle;

        public:
            explicit VulkanContext(GLFWwindow* windowHandle);

            void Init() override;
            void SwapBuffers() override;
        };
    }
}

#endif
#endif