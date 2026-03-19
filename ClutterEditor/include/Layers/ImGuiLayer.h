#ifndef CLUTTERENGINE_IMGUILAYER_H
#define CLUTTERENGINE_IMGUILAYER_H

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <EditorUI/Managers/PanelManager.h>
#include "Services/ImGuiContextService.h"
#include <EditorUI/Managers/EditorUiManager.h>

#include <iostream>
#include <memory>

namespace editor
{
    class ImGuiLayer : public clt::Layer
    {
        std::unique_ptr<PanelManager> mPanelManager;
        std::unique_ptr<ImGuiContextService> mImGuiService;
        std::unique_ptr<EditorUiManager> mUIManager;
        std::unique_ptr<EditorContext> mEditorCtx;

        void LoadDefaultPanels() const;
        void LoadDefaultAssets() const;

    public:
        ImGuiLayer() : Layer("ImGui Layer") {}

        void OnAttach(const clt::engine::Context& context) override;

        void OnUpdate(double dt) override;
    };
}

#endif //CLUTTERENGINE_IMGUILAYER_H