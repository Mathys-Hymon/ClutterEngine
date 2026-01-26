#include <clt/Core/Application/Application.h>

#include <iostream>
#include <clt/Core/EngineContext.h>

#include <clt/Core/EngineContext.h>
#include <clt/Core/Debug/Log.h>
#include <clt/Core/IWindow.h>
#include <clt/Renderer/Renderer.h>

namespace clt
{
    Application::Application(const ApplicationCommandLineArgs& args)
    {
        Core::Log::Init();
        Timer::Initialize();

        graphic::Renderer::SetRendererAPI(graphic::RendererAPIType::OpenGL);

        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
    }

    void Application::Run()
    {
        CLT_CORE_INFO("Clutter Engine Started");

        while (mIsRunning)
        {
            float dt = Timer::ComputeDeltaTime();

            if (mWindow) mWindow->OnUpdate();

            for (Layer* layer : mLayerStack) layer->OnUpdate(dt);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);

        const EngineContext context(mWindow.get());
        layer->OnAttach(context);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        const EngineContext context(mWindow.get());
        overlay->OnAttach(context);
    }
}
