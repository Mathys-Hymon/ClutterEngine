#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <Layers/EditorLayer.h>

#include "Assets/EditorAssetManager.h"
#include "clt/Core/Debug/Log.h"
#include "Layers/ImGuiLayer.h"
#include "Layers/ProjectBrowserLayer.h"
#include "Utils/FileUtils.h"

namespace editor
{

    class ClutterEditor : public clt::Application
    {

        clt::Layer* mProjectBrowserLayer{nullptr};
        clt::Layer* mEditorLayer{nullptr};
        clt::Layer* mImGuiLayer{nullptr};

    public:
        explicit ClutterEditor(const clt::ApplicationCommandLineArgs& args)
            : Application(args)
        {
            utils::FileUtils::Initialize();

            if (args.Count <= 1)
            {
                mProjectBrowserLayer = new ProjectBrowserLayer();
                PushLayer(mProjectBrowserLayer);
            }
        }

        clt::IAssetManager* CreateAssetManager() override
        {
            return new EditorAssetManager;
        }

        void OnProjectLoaded() override
        {
            PopLayer(mProjectBrowserLayer);

            if (mEditorLayer) PopLayer(mEditorLayer);
            if (mImGuiLayer) PopLayer(mImGuiLayer);

            mEditorLayer = new EditorLayer();
            mImGuiLayer = new ImGuiLayer();

            PushLayer(mEditorLayer);
            PushLayer(mImGuiLayer);

            CLUTTER_INFO("Editor Hot-Reload finished !");
        }

        ~ClutterEditor() override {}
    };

}

clt::Application* clt::CreateApplication(const clt::ApplicationCommandLineArgs args)
{
    return new editor::ClutterEditor(args);
}