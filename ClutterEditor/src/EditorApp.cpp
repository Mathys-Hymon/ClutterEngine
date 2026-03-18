#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <Layers/EditorLayer.h>

#include "Layers/ImGuiLayer.h"
#include "Layers/ProjectBrowserLayer.h"

class ClutterEditor : public clt::Application
{
public:
    explicit ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        if (args.Count > 0)
        {
            PushLayer(new editor::EditorLayer());
            PushLayer(new editor::ImGuiLayer());
        }
        else
        {
            PushLayer(new editor::ProjectBrowserLayer());
        }
    }

    ~ClutterEditor() override {}
};


clt::Application* clt::CreateApplication(const clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}