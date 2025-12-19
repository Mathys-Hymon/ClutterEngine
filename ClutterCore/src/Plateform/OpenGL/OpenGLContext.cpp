#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace clt
{
    namespace graphic
    {
        OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
        {
            if (!windowHandle) std::cerr << "Error in OpenGLContext::OpenGLContext()" << std::endl;
        }

        void OpenGLContext::Init()
        {
            glfwMakeContextCurrent(mWindowHandle);

            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!status)
            {
                std::cout << "Failed to initialize OpenGL context" << std::endl;
            }

            // Debug Info
            std::cout << "--- OpenGL Info ---" << std::endl;
            std::cout << " Vendor:   " << glGetString(GL_VENDOR) << std::endl;
            std::cout << " Renderer: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << " Version:  " << glGetString(GL_VERSION) << std::endl;
            std::cout << "-------------------" << std::endl;
        }

        void OpenGLContext::SwapBuffers()
        {
            glfwSwapBuffers(mWindowHandle);
        }
    }
}
