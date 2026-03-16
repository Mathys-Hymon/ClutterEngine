#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <Layers/EditorLayer.h>

class ClutterEditor : public clt::Application
{
public:
    ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        PushLayer(new editor::EditorLayer());
    }

    ~ClutterEditor() override {}
};


clt::Application* clt::CreateApplication(const clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}