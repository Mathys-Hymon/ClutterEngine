#include <Layers/ProjectBrowserLayer.h>

#include "clt/Core/IWindow.h"
#include "EditorUI/Panels/ProjectBrowser/ProjectsPanel.h"

void editor::ProjectBrowserLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    context.window->ResizeViewportCentered(900.0f, 650.0f);
    context.window->RenameViewport("Clutter Project Browser");

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
    const std::string absoluteFontPath = mContext->engineRootPath.string() + "/EditorContent/Resources/Font/";

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

editor::ProjectBrowserLayer::ProjectBrowserLayer()  : Layer("Project Browser Layer")
{

}

void editor::ProjectBrowserLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mUIManager->BeginFrame();

    mUIManager->Draw();

    mUIManager->EndFrame();
}
