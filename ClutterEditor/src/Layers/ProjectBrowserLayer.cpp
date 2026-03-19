#include <Layers/ProjectBrowserLayer.h>

#include "clt/Core/IWindow.h"
#include "EditorUI/Panels/ProjectBrowser/ProjectsPanel.h"

void editor::ProjectBrowserLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    mImGuiService = std::make_unique<ImGuiContextService>(context, "#version 460");
    mPanelManager = std::make_unique<PanelManager>();

    mEditorCtx = std::make_unique<EditorContext>();
    mEditorCtx->panels = mPanelManager.get();

    mUIManager = std::make_unique<EditorUiManager>(mImGuiService.get(), mEditorCtx.get());

    LoadDefaultAssets();
    LoadDefaultPanels();
}

void editor::ProjectBrowserLayer::LoadDefaultAssets() const
{
    mEditorCtx->themes->SetFont(editor::TextType::classic, "EditorContent/Resources/Font/Rubik.ttf", 15.0f);
    mEditorCtx->themes->SetFont(editor::TextType::title, "EditorContent/Resources/Font/Rubik.ttf", 18.0f);
    mEditorCtx->themes->SetFont(editor::TextType::console, "EditorContent/Resources/Font/JetBrains.ttf", 15.0f);
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
    engineContext.Window->ResizeViewportCentered(1200.0f, 750.0f);
    engineContext.Window->RenameViewport("Clutter Project Browser");
}

void editor::ProjectBrowserLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mUIManager->BeginFrame();

    mUIManager->Draw();

    mUIManager->EndFrame();
}
