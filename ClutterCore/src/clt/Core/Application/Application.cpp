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
#include "clt/Core/Meta/ProjectSerializer.h"
#include "clt/Core/Meta/Reflection.h"

namespace clt
{
    Application::Application(const ApplicationCommandLineArgs& args)
    {
        core::Log::Init();
        Timer::Initialize();

        graphic::Renderer::SetRendererAPI(graphic::RendererAPIType::OpenGL);

        if (!mWindow) mWindow = std::unique_ptr<IWindow>(IWindow::Create());
        if (!mAsset) mAsset = std::unique_ptr<IAssetManager>(CreateAssetManager());

        mContext.window = mWindow.get();
        mContext.assets = mAsset.get();

        mWindow->SetEventCallback([this](Event& e) { this->OnEvent(e); });
        mContext.eventCallback = [this](Event& e) { this->OnEvent(e); };

        meta::Initialize();

        CLT_CORE_INFO("Clutter Engine Started");

        const std::filesystem::path root = args.Args[0];
        mContext.engineRootPath = root.parent_path();

        if (args.Count > 1) OpenProject(args.Args[1]);
    }

    bool Application::OnWindowClose(WindowCloseEvent&)
    {
        mIsRunning = false;
        return true;
    }

    bool Application::OnProjectOpened(const ProjectLoadEvent& e)
    {
        OpenProject(e.GetPath());
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

            if (mNeedHotReload)
            {
                mNeedHotReload = false;
                OnProjectLoaded();
            }

            static double delay = Timer::StopChrono("ApplicationUpdate");

            Timer::DelayTime(1.f/144.f - delay);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        if (!layer) return;

        mLayerStack.PushLayer(layer);
        layer->OnAttach(mContext);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        if (!overlay) return;

        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach(mContext);
    }

    void Application::PopLayer(Layer* layer)
    {
        if (! layer) return;
        mLayerStack.PopLayer(layer);
        delete layer;
        layer = nullptr;
    }

    void Application::PopOverlay(Layer* overlay)
    {
        if (!overlay) return;
        mLayerStack.PopLayer(overlay);
        delete overlay;
        overlay = nullptr;
    }

    void Application::OnProjectLoaded()
    {

    }

    void Application::OpenProject(const std::filesystem::path& path)
    {
        if (const auto loadedProject = ProjectSerializer::Load(path))
        {
            mContext.activeProject = loadedProject;
            mNeedHotReload = true;
        }
        else
        {
            CLT_CORE_ERROR("Unable to load project: {}", path.string());
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return this->OnWindowClose(e); });
        dispatcher.Dispatch<ProjectLoadEvent>([this](const ProjectLoadEvent& e) { return this->OnProjectOpened(e); });

        for (const auto layer : std::ranges::reverse_view(mLayerStack))
        {
            if (!layer)
            {
                continue;
            }

            layer->OnEvent(e);

            if (e.Handled) break;
        }
    }
}

