#include "WindowsWindow.h"

#include <iostream>

#include "../../ClutterCore/src/Plateform/OpenGL/OpenGLContext.h"

clt::IWindow* clt::IWindow::Create(const clt::WindowProps& props)
{
    return new WindowsWindow(props);
}


clt::WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

clt::WindowsWindow::~WindowsWindow()
{
    Shutdown();
}

void clt::WindowsWindow::Init(const WindowProps& props)
{
    mData.Title = props.Title;
    mData.Width = props.Width;
    mData.Height = props.Height;

    std::cout << "Create window : " << props.Title << " (" << props.Width << ", " << props.Height << ")" << std::endl;

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "ERROR: Cant Initialize GLFW !" << std::endl;
        return;
    }

    glfwSetErrorCallback([](int error, const char* description)
    {
        std::cerr << "GLFW Error( "<< error << "): " << description << std::endl;
    });

    mWindowHandle = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), mData.Title.c_str(), nullptr, nullptr);

    mContext = std::make_unique<graphic::OpenGLContext>(mWindowHandle);
    mContext->Init();

    glfwSetWindowUserPointer(mWindowHandle, &mData);

    glfwSwapInterval(1); // VSync ON
}

void clt::WindowsWindow::Shutdown()
{
    glfwDestroyWindow(mWindowHandle);
    glfwTerminate();
}


void clt::WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    mContext->SwapBuffers();
}