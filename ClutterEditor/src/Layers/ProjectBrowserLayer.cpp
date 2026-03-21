#include <Layers/ProjectBrowserLayer.h>

#include "clt/Core/IWindow.h"
#include "EditorUI/Panels/ProjectBrowser/ProjectsPanel.h"

void editor::ProjectBrowserLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    mPanelManager = std::make_unique<PanelManager>();

    mEditorCtx = std::make_unique<EditorContext>();
    mEditorCtx->panels = mPanelManager.get();
    mEditorCtx->engineContext = &context;

    mImGuiService = std::make_unique<ImGuiContextService>(mEditorCtx.get(), "#version 460");
    mUIManager = std::make_unique<EditorUiManager>(mImGuiService.get(), mEditorCtx.get());

    LoadDefaultAssets();
    LoadDefaultPanels();
}

void editor::ProjectBrowserLayer::LoadDefaultAssets() const
{
    const std::string absoluteFontPath = mContext->EngineRootPath.string() + "/EditorContent/Resources/Font/";

    mEditorCtx->themes->SetFont(editor::TextType::classic, (absoluteFontPath + "Rubik.ttf").c_str(), 15.0f);
    mEditorCtx->themes->SetFont(editor::TextType::title, (absoluteFontPath + "Rubik.ttf").c_str(), 18.0f);
    mEditorCtx->themes->SetFont(editor::TextType::console, (absoluteFontPath + "JetBrains.ttf").c_str(), 15.0f);
}

void editor::ProjectBrowserLayer::LoadDefaultPanels() const
{
    mPanelManager->RegisterPanels(
{
        std::make_shared<ProjectPanel>(mEditorCtx.get()),
    });
}

editor::ProjectBrowserLayer::ProjectBrowserLayer(const clt::engine::Context& engineContext)  : Layer("Project Browser Layer"), mEngineContext(engineContext)
{
    engineContext.Window->ResizeViewportCentered(1000.0f, 650.0f);
    engineContext.Window->RenameViewport("Clutter Project Browser");
}

void editor::ProjectBrowserLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mUIManager->BeginFrame();

    mUIManager->Draw();

    mUIManager->EndFrame();
}
