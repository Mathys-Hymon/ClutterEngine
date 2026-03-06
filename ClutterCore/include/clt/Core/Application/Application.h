#pragma once

#include <iostream>
#include <memory>

#include "../Layers/LayerStack.h"
#include "../IWindow.h"
#include "clt/Core/Event/ApplicationEvent.h"

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

        bool OnWindowClose(WindowCloseEvent& e);

        public:

        explicit Application(const ApplicationCommandLineArgs& args = ApplicationCommandLineArgs());
        virtual ~Application() = default;

        void Run();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnEvent(Event& e);

        IWindow& GetWindow() const { return *mWindow; }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);

}
