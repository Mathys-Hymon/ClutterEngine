#include <clt/Core/Application/Application.h>

#include <iostream>
#include <ranges>
#include <clt/Core/EngineContext.h>

#include <clt/Core/EngineContext.h>
#include <clt/Core/Debug/Log.h>
#include <clt/Core/IWindow.h>
#include <clt/Renderer/Renderer.h>

#include "clt/Core/Timer.h"
#include "clt/Core/Assets/AssetManager.h"
#include "clt/Core/Assets/IAssetManager.h"
#include "clt/Core/Meta/Reflection.h"

namespace clt
{
    Application::Application(const ApplicationCommandLineArgs& args)
    {
        core::Log::Init();
        Timer::Initialize();

        const std::filesystem::path root = args.Args[0];

        graphic::Renderer::SetRendererAPI(graphic::RendererAPIType::OpenGL);

        if (!mWindow) mWindow = std::unique_ptr<IWindow>(IWindow::Create());
        if (!mAsset) mAsset = std::unique_ptr<IAssetManager>(CreateAssetManager());

        mContext.window = mWindow.get();
        mContext.assets = mAsset.get();
        mContext.engineRootPath = root.parent_path();

        mWindow->SetEventCallback([this](Event& e) { this->OnEvent(e); });
        meta::Initialize();

        CLT_CORE_INFO("Clutter Engine Started");
    }

    bool Application::OnWindowClose(WindowCloseEvent&)
    {
        mIsRunning = false;
        return true;
    }

    IAssetManager* Application::CreateAssetManager()
    {
        return new AssetManager();
    }

    void Application::Run()
    {
        while (mIsRunning)
        {
             const double dt = Timer::ComputeDeltaTime();

            Timer::StartChrono("ApplicationUpdate");

            if (mWindow) mWindow->OnUpdate();

            for (Layer* layer : mLayerStack) layer->OnUpdate(dt);

            static double delay = Timer::StopChrono("ApplicationUpdate");

            Timer::DelayTime(1.f/144.f - delay);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);
        layer->OnAttach(mContext);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach(mContext);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return this->OnWindowClose(e); });

        for (const auto layer : std::ranges::reverse_view(mLayerStack))
        {
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
