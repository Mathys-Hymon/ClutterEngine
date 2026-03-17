#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <Layers/EditorLayer.h>

#include "Layers/ImGuiLayer.h"

class ClutterEditor : public clt::Application
{
public:
    ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        //PushLayer(new editor::EditorLayer());
        PushLayer(new editor::ImGuiLayer());
    }

    ~ClutterEditor() override {}
};


clt::Application* clt::CreateApplication(const clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}