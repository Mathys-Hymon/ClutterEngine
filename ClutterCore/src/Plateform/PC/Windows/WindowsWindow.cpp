#include "WindowsWindow.h"

#ifdef CLUTTER_PLATFORM_WINDOWS

#include <iostream>
#include "../../ClutterCore/src/Plateform/PC/OpenGL/OpenGLContext.h"
#include "../../ClutterCore/src/Plateform/PC/Vulkan/VulkanContext.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Event/ApplicationEvent.h"
#include "clt/Renderer/Renderer.h"
#include "glad/glad.h"

clt::IWindow* clt::IWindow::Create(const clt::WindowProps& props)
{
    return new WindowsWindow(props);
}

void clt::WindowsWindow::ResizeViewport(UVector2 pos, UVector2 size)
{
    ResizeViewport(pos.x, pos.y, size.x, size.y);
}

void clt::WindowsWindow::ResizeViewport(const uint32_t /*startWidth*/,const uint32_t /*startHeight*/,const uint32_t width,const uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    glfwSetWindowSize(mWindowHandle, static_cast<int>(width), static_cast<int>(height));
}

void clt::WindowsWindow::ResizeViewportCentered(const UVector2 size)
{
    ResizeViewportCentered(size.x, size.y);
}

void clt::WindowsWindow::ResizeViewportCentered(const uint32_t width,const uint32_t height)
{
    mData.Width = width;
    mData.Height = height;

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    const int xpos = static_cast<int>(static_cast<float>(static_cast<uint32_t>(mode->width) - width) * 0.5f);
    const int ypos = static_cast<int>(static_cast<float>(static_cast<uint32_t>(mode->height) - height) * 0.5f);

    glfwSetWindowSize(mWindowHandle, static_cast<int>(width), static_cast<int>(height));
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
    mData.VSync = false;

    CLT_CORE_INFO("Create window : {0} ( {1}, {2} )", props.Title, props.Width, props.Height);

    if (glfwInit() == GLFW_FALSE)
    {
        CLT_CORE_ERROR("Failed to initialize GLFW!");
        return;
    }

    const graphic::RendererAPIType api = graphic::RendererAPI::GetAPI();

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

clt::UVector2 clt::WindowsWindow::GetMonitorSize() const
{
    GLFWmonitor* return_struct = nullptr;

    glfwGetVideoMode( return_struct );

    int width, height;

    glfwGetMonitorPhysicalSize(return_struct, &width, &height);

    return UVector2{width, height};
}

#endif