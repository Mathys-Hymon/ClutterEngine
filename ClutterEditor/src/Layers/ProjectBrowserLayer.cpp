#include <Layers/ProjectBrowserLayer.h>

#include "clt/Core/IWindow.h"
#include "clt/Core/Assets/IAssetManager.h"
#include "EditorUI/Panels/ProjectBrowser/ProjectsPanel.h"

void editor::ProjectBrowserLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    context.window->ResizeViewportCentered(900.0f, 500.0f);
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

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::font,
        mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/fontFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::mesh,
        mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::script,
    mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/scriptFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::shader,
    mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/shaderFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::sound,
    mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/audioFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::texture,
        mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));

    mEditorCtx->themes->SetAssetIcon(editor::AssetType::unknown,
    mEditorCtx->engineContext->assets->LoadTexture(clt::pathType::engine, "/EditorContent/Resources/Textures/meshFile.png", "", clt::TextureFilter::NEAREST, true, false));


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
