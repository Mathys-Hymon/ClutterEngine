#ifndef CLUTTERENGINE_PROJECTBROWSERLAYER_H
#define CLUTTERENGINE_PROJECTBROWSERLAYER_H

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <EditorUI/Managers/PanelManager.h>
#include "Services/ImGuiContextService.h"
#include <EditorUI/Managers/EditorUiManager.h>
#include <clt/Core/EngineContext.h>

#include <iostream>
#include <memory>

namespace editor
{
    class ProjectBrowserLayer : public clt::Layer
    {
        std::unique_ptr<PanelManager> mPanelManager;
        std::unique_ptr<ImGuiContextService> mImGuiService;
        std::unique_ptr<EditorUiManager> mUIManager;
        std::unique_ptr<EditorContext> mEditorCtx;

        void LoadDefaultAssets() const;
        void LoadDefaultPanels() const;

    public:
        ProjectBrowserLayer();

        void OnAttach(const clt::engine::Context& context) override;

        void OnUpdate(double dt) override;
    };
}

#endif //CLUTTERENGINE_PROJECTBROWSERLAYER_H