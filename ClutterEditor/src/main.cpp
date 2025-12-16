#include <../../ClutterCore/src/Application/Application.h>
#include <../../ClutterCore/src/Application/EntryPoint.h>
#include <../../ClutterCore/src/Application/Layers/Layer.h>
#include <../../ClutterCore/src/Core/EngineContext.h>
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