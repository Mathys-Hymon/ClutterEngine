#include "WindowsWindow.h"

#include <iostream>
#include "../../ClutterCore/src/Plateform/OpenGL/OpenGLContext.h"
#include "clt/Core/Debug/Log.h"
#include "glad/glad.h"

clt::IWindow* clt::IWindow::Create(const clt::WindowProps& props)
{
    return new WindowsWindow(props);
}

void clt::WindowsWindow::ResizeViewport(uint32_t startWidth, uint32_t startHeight, uint32_t width, uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    glfwSetWindowSize(mWindowHandle, width, height);
    glViewport(startWidth, startHeight, width, height);
}

void clt::WindowsWindow::ResizeViewportCentered(uint32_t width, uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    int xpos = (mode->width - width) / 2;
    int ypos = (mode->height - height) / 2;

    glfwSetWindowSize(mWindowHandle, width, height);
    glfwSetWindowPos(mWindowHandle, xpos, ypos);

    glfwMakeContextCurrent(mWindowHandle);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

void clt::WindowsWindow::RenameViewport(const char* name)
{
    glfwSetWindowTitle(mWindowHandle, name);
}

void clt::WindowsWindow::SetVSync(const bool enabled)
{
    mData.VSync = enabled;
}

void clt::WindowsWindow::Init(const WindowProps& props)
{
    mData.Title = props.Title;
    mData.Width = props.Width;
    mData.Height = props.Height;

    std::cout << "Create window : " << props.Title << " (" << props.Width << ", " << props.Height << ")" << std::endl;

    if (glfwInit() == GLFW_FALSE)
    {
        CLT_CORE_ERROR("Failed to initialize GLFW!");
        return;
    }

    glfwSetErrorCallback([](int error, const char* description)
    {
        CLT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    });

    mWindowHandle = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), mData.Title.c_str(), nullptr, nullptr);

    mContext = std::make_unique<graphic::OpenGLContext>(mWindowHandle);
    mContext->Init();

    glfwSetWindowUserPointer(mWindowHandle, &mData);

    glfwSwapInterval(mData.VSync); // VSync ON
}

void clt::WindowsWindow::Shutdown()
{
    if (mWindowHandle)
    {
        glfwDestroyWindow(mWindowHandle);
        glfwTerminate();
        mWindowHandle = nullptr;
    }
}

clt::WindowsWindow::WindowsWindow(const WindowProps& props)
{
    WindowsWindow::Init(props);
}

clt::WindowsWindow::~WindowsWindow()
{
    WindowsWindow::Shutdown();
}

void clt::WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    mContext->SwapBuffers();
}
