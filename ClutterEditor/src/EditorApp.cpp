#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <Layers/EditorLayer.h>

#include "Layers/ImGuiLayer.h"
#include "Layers/ProjectBrowserLayer.h"
#include "Utils/FileUtils.h"

namespace editor
{

    class ClutterEditor : public clt::Application
    {
    public:
        explicit ClutterEditor(const clt::ApplicationCommandLineArgs& args)
            : Application(args)
        {
            utils::FileUtils::Initialize();

            if (args.Count > 1)
            {
                PushLayer(new EditorLayer(args));
                PushLayer(new ImGuiLayer());
            }
            else
            {
                PushLayer(new ProjectBrowserLayer(GetContext()));
            }
        }

        void CreateAssetsLoaders() override;

        ~ClutterEditor() override {}
    };

    void ClutterEditor::CreateAssetsLoaders()
    {
    }
}

clt::Application* clt::CreateApplication(const clt::ApplicationCommandLineArgs args)
{
    return new editor::ClutterEditor(args);
}