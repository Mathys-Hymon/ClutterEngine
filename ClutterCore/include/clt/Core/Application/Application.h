#pragma once

#include <memory>

#include "../Layers/LayerStack.h"
#include "../IWindow.h"

namespace clt
{
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
    };

    class Application
    {
        std::unique_ptr<IWindow> mWindow;
        LayerStack mLayerStack;
        bool mIsRunning = true;
        float mLastTime = 0.0f;

        public:
        explicit Application(const ApplicationCommandLineArgs& args = ApplicationCommandLineArgs());
        virtual ~Application() = default;

        void Run();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        IWindow& GetWindow() { return *mWindow; }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);
}