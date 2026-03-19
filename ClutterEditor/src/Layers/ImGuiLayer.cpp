#include <Layers/ImGuiLayer.h>

#include "clt/Core/Debug/Log.h"
#include "EditorUI/Panels/ConsolePanel.h"
#include "EditorUI/Panels/ContentBrowserPanel.h"
#include "EditorUI/Panels/InspectorPanel.h"
#include "EditorUI/Panels/MenuBarPanel.h"
#include "EditorUI/Panels/OutlinerPanel.h"
#include "EditorUI/Panels/ThemePanel.h"

void editor::ImGuiLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    mImGuiService = std::make_unique<ImGuiContextService>(context, "#version 460");
    mPanelManager = std::make_unique<PanelManager>();

    mEditorCtx = std::make_unique<EditorContext>();
    mEditorCtx->panels = mPanelManager.get();

    mUIManager = std::make_unique<EditorUiManager>(mImGuiService.get(), mEditorCtx.get());

    LoadDefaultPanels();
    LoadDefaultAssets();
}

void editor::ImGuiLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mUIManager->BeginFrame();

    mUIManager->Draw();

    mUIManager->EndFrame();
}

void editor::ImGuiLayer::LoadDefaultPanels() const
{
    mPanelManager->RegisterPanels({
        std::make_shared<MenuBarPanel>(mEditorCtx.get()),
        std::make_shared<InspectorPanel>(mEditorCtx.get()),
        std::make_shared<OutlinerPanel>(mEditorCtx.get()),
        std::make_shared<ThemePanel>(mEditorCtx.get()),
        std::make_shared<ContentBrowserPanel>(mEditorCtx.get()),
        std::make_shared<ConsolePanel>(mEditorCtx.get()),
    });

}

void editor::ImGuiLayer::LoadDefaultAssets() const
{
    mEditorCtx->themes->SetFont(editor::TextType::classic, "EditorContent/Resources/Font/Rubik.ttf", 15.0f);
    mEditorCtx->themes->SetFont(editor::TextType::title, "EditorContent/Resources/Font/Rubik.ttf", 18.0f);
    mEditorCtx->themes->SetFont(editor::TextType::console, "EditorContent/Resources/Font/JetBrains.ttf", 15.0f);
}
