#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

#include "clt/Core/Debug/Log.h"

class EditorLayer : public clt::Layer
{
public:
    EditorLayer() : Layer("EditorLayer") {}

    void OnAttach(const clt::engine::Context& context) override
    {
        if (context.Window)
        {
        }
        else
        {
            CLT_CORE_WARN("Window not initialized yet (Normal pour le test)");
        }
    }

    void OnUpdate(const float /*dt*/) override
    {
        // std::cout << "Update..." << std::endl;
    }

    void OnEvent(clt::Event& /*e*/) override
    {

    }
};

class ClutterEditor : public clt::Application {
public:
    ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        PushLayer(new EditorLayer());
    }

    ~ClutterEditor() override {}
};

clt::Application* clt::CreateApplication(clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}