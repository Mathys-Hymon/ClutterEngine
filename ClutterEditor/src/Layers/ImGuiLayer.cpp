#include <Layers/ImGuiLayer.h>

#include "clt/Core/Assets/IAssetManager.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Project/Project.h"
#include "EditorUI/Panels/ConsolePanel.h"
#include "EditorUI/Panels/ContentBrowserPanel.h"
#include "EditorUI/Panels/InspectorPanel.h"
#include "EditorUI/Panels/MenuBarPanel.h"
#include "EditorUI/Panels/OutlinerPanel.h"
#include "EditorUI/Panels/ThemePanel.h"
#include "EditorUI/Panels/ViewportPanel.h"

void editor::ImGuiLayer::OnAttach(const clt::engine::Context& context)
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
        std::make_shared<ViewportPanel>(mEditorCtx.get()),
    });

}

void editor::ImGuiLayer::LoadDefaultAssets() const
{
    const std::string absoluteFontPath = mContext->engineRootPath.string() + "/EditorContent/Resources/Font/";

    mEditorCtx->themes->SetFont(TextType::classic, (absoluteFontPath + "Rubik.ttf").c_str(), 15.0f);
    mEditorCtx->themes->SetFont(TextType::title, (absoluteFontPath + "Rubik.ttf").c_str(), 18.0f);
    mEditorCtx->themes->SetFont(TextType::console, (absoluteFontPath + "JetBrains.ttf").c_str(), 15.0f);

    mEditorCtx->themes->SetAssetIcon(AssetType::font,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/fontFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::mesh,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::script,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/scriptFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::shader,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/shaderFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::sound,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/audioFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::texture,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::level,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/levelFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(AssetType::unknown,
    mEditorCtx->engineContext->assets->LoadTexture(clt::PathType::engine, "Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));
}
