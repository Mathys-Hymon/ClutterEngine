#include "WindowsWindow.h"

#include <iostream>
#include "../../ClutterCore/src/Plateform/OpenGL/OpenGLContext.h"
#include "../../ClutterCore/src/Plateform/Vulkan/VulkanContext.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Event/ApplicationEvent.h"
#include "clt/Renderer/Renderer.h"
#include "glad/glad.h"

clt::IWindow* clt::IWindow::Create(const clt::WindowProps& props)
{
    return new WindowsWindow(props);
}

void clt::WindowsWindow::ResizeViewport(const uint32_t startWidth,const uint32_t startHeight,const uint32_t width,const uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    glfwSetWindowSize(mWindowHandle, width, height);
}

void clt::WindowsWindow::ResizeViewportCentered(const uint32_t width,const uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    const int xpos = (mode->width - width) * 0.5f;
    const int ypos = (mode->height - height) * 0.5f;

    glfwSetWindowSize(mWindowHandle, mData.Width, height);
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

    CLT_CORE_INFO("Create window : {0} ( {1}, {2} )", props.Title, props.Width, props.Height);

    if (glfwInit() == GLFW_FALSE)
    {
        CLT_CORE_ERROR("Failed to initialize GLFW!");
        return;
    }

    graphic::RendererAPIType api = graphic::Renderer::GetRendererAPI();

    if (api == graphic::RendererAPIType::OpenGL)
    {
        CLT_CORE_INFO("Backend API : OpenGL");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    else if (api == graphic::RendererAPIType::Vulkan)
    {
        CLT_CORE_INFO("Backend API : Vulkan");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    glfwSetErrorCallback([](int error, const char* description)
    {
        CLT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    });

    mWindowHandle = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), mData.Title.c_str(), nullptr, nullptr);

    if (api == graphic::RendererAPIType::OpenGL) mContext = std::make_unique<graphic::OpenGLContext>(mWindowHandle);
    else if (api == graphic::RendererAPIType::Vulkan) mContext = std::make_unique<graphic::VulkanContext>(mWindowHandle);

    mContext->Init();

    glfwSetWindowUserPointer(mWindowHandle, &mData);

    glfwSwapInterval(mData.VSync); // VSync ON

    glfwSetWindowCloseCallback(mWindowHandle, [](GLFWwindow* window)
    {
        const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.EventCallback(event);
    });

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
