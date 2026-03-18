#ifndef CLUTTERENGINE_PROJECTBROWSERLAYER_H
#define CLUTTERENGINE_PROJECTBROWSERLAYER_H

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <EditorUI/Managers/PanelManager.h>
#include "Services/ImGuiContextService.h"
#include <EditorUI/Managers/EditorUiManager.h>

#include <iostream>
#include <memory>

namespace editor
{
    class ProjectBrowserLayer : public clt::Layer
    {
        std::unique_ptr<PanelManager> mPanelManager;
        std::unique_ptr<ImGuiContextService> mImGuiService;

    public:
        ProjectBrowserLayer() : Layer("Project Browser Layer") {}

        void OnAttach(const clt::engine::Context& context) override;

        void OnUpdate(double dt) override;
    };
}

#endif //CLUTTERENGINE_PROJECTBROWSERLAYER_H