#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "clt/Core/Debug/Log.h"

namespace clt::graphic
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
    {
        if (!windowHandle) std::cerr << "Error in OpenGLContext::OpenGLContext()" << std::endl;
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(mWindowHandle);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!status)
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
        }

        // Debug Info
        CLT_CORE_INFO("--- OpenGL Info ---");
        CLT_CORE_INFO("Vendor:   {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        CLT_CORE_INFO("Renderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
        CLT_CORE_INFO("Version:  {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        CLT_CORE_INFO("-------------------");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}
