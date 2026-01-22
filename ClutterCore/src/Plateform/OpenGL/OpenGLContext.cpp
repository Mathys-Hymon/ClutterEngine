#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "clt/Core/Debug/Log.h"

namespace clt::graphic
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
    {
        if (!windowHandle) CLT_CORE_FATAL("Error in OpenGLContext::OpenGLContext()");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(mWindowHandle);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!status)
        {
            CLT_CORE_FATAL("Failed to initialize OpenGL context");
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
