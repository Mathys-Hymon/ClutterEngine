#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

class EditorLayer : public clt::Layer
{
public:
    EditorLayer() : Layer("EditorLayer") {}

    void OnAttach(const clt::EngineContext& context) override
    {
        if (context.Window)
        {
        }
        else
        {
            std::cout << "Window not initialized yet (Normal pour le test)" << std::endl;
        }
    }

    void OnUpdate(const float& dt) override
    {
        // std::cout << "Update..." << std::endl;
    }
};

class ClutterEditor : public clt::Application {
public:
    ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        PushLayer(new EditorLayer());
    }

    ~ClutterEditor() {}
};

clt::Application* clt::CreateApplication(clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}