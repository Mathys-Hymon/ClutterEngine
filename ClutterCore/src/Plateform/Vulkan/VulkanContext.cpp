#include "VulkanContext.h"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>

#include "clt/Core/Debug/Log.h"

namespace clt
{
    namespace graphic
    {
        VulkanContext::VulkanContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
        {
            if (!windowHandle) CLT_CORE_FATAL("Error in VulkanContext::VulkanContext()");
        }

        void VulkanContext::Init()
        {
            if (!glfwVulkanSupported())
            {
                CLT_CORE_FATAL("Vulkan Not Supported by GLFW!");
            }

            uint32_t extensionCount = 0;
            const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
            // Debug Info
            CLT_CORE_INFO("--- Vulkan Info ---");
            CLT_CORE_INFO("Vulkan Loader: Ready");
            CLT_CORE_INFO("Extensions required by GLFW: {0}", extensionCount);

            for (uint32_t i = 0; i < extensionCount; i++)
            {
                CLT_CORE_TRACE("  - {0}", extensions[i]);
            }

            CLT_CORE_INFO("--- Vulkan Info End ---");
        }

        void VulkanContext::SwapBuffers()
        {
        }
    }
}
