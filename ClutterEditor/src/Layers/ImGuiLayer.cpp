#include <Layers/ImGuiLayer.h>

#include "clt/Core/Debug/Log.h"
#include "EditorUI/Panels/ConsolePanel.h"

void editor::ImGuiLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    mImGuiService = std::make_unique<ImGuiContextService>(context, "#version 460");
    mPanelManager = std::make_unique<PanelManager>();

    mEditorCtx = std::make_unique<EditorContext>();
    mEditorCtx->panels = mPanelManager.get();

    RegisterDefaultPanels();

    mUIManager = std::make_unique<EditorUiManager>(mImGuiService.get(), mEditorCtx.get());
}

void editor::ImGuiLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mUIManager->BeginFrame();

    mUIManager->Draw();

    mUIManager->EndFrame();
}

void editor::ImGuiLayer::RegisterDefaultPanels() const
{
    mPanelManager->RegisterPanel(
        std::make_shared<ConsolePanel>(mEditorCtx.get())
    );
}

void editor::ImGuiLayer::SetUpDefaultAssets() const
{
    mEditorCtx->themes->SetFont(editor::TextType::classic, "../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 15.0f);
    mEditorCtx->themes->SetFont(editor::TextType::title, "../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 18.0f);
    mEditorCtx->themes->SetFont(editor::TextType::console, "../ClutterEngine/EngineContent/Resources/Font/JetBrains.ttf", 15.0f);
}
