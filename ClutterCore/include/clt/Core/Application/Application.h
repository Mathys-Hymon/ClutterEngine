#pragma once

#include <iostream>
#include <memory>

#include "../Layers/LayerStack.h"
#include "../IWindow.h"
#include "clt/Core/Event/ApplicationEvent.h"

namespace clt
{
    class IAssetManager;

    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
    };

    class Application
    {
        protected:

        std::unique_ptr<IWindow> mWindow;
        std::unique_ptr<IAssetManager> mAsset;
        LayerStack mLayerStack;
        bool mIsRunning{true};
        bool mNeedHotReload{false};
        float mLastTime{0.0f};

        engine::Context mContext;

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnProjectOpened(const ProjectLoadEvent& e);

        void OpenProject(const std::filesystem::path& path);

    protected:
        virtual IAssetManager* CreateAssetManager();

        public:

        explicit Application(const ApplicationCommandLineArgs& args = ApplicationCommandLineArgs());
        virtual ~Application() = default;

        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        virtual void OnProjectLoaded();

        virtual void OnEvent(Event& e);

        IWindow& GetWindow() const { return *mWindow; }
        engine::Context& GetContext() {return mContext; }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);

}
