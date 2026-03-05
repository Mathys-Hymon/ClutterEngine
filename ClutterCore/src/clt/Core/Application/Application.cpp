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

        mWindow->SetEventCallback([this](Event& e) { this->OnEvent(e); });
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        mIsRunning = false;
        return true;
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

        const engine::Context context(mWindow.get());
        layer->OnAttach(context);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        const engine::Context context(mWindow.get());
        overlay->OnAttach(context);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return this->OnWindowClose(e); });

        for (auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it)
        {
            Layer* layer = *it;

            if (!layer)
            {
                CLT_CORE_ERROR("Layer is null");
                continue;
            }

            layer->OnEvent(e);

            if (e.Handled) break;
        }
    }
}
