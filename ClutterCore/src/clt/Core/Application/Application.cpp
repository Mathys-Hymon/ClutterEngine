#include <clt/Core/Application/Application.h>

#include <iostream>
#include <clt/Core/EngineContext.h>

#include <clt/Core/EngineContext.h>
#include <clt/Core/IWindow.h>

namespace clt
{
    IWindow* IWindow::Create(const WindowProps& props)
    {
        return nullptr;
    }


    Application::Application(const ApplicationCommandLineArgs& args)
    {
        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        std::cout << "Clutter Engine Started" << std::endl;

        while (mIsRunning)
        {
            float timestep = 0.016f;

            if (mWindow) mWindow->OnUpdate();

            for (Layer* layer : mLayerStack) layer->OnUpdate(timestep);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);

        EngineContext context(mWindow.get());
        layer->OnAttach(context);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        EngineContext context(mWindow.get());
        overlay->OnAttach(context);
    }

}
