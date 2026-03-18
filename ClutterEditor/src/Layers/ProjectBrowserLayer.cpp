#include <Layers/ProjectBrowserLayer.h>

void editor::ProjectBrowserLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    mImGuiService = std::make_unique<ImGuiContextService>(context, "#version 460");
    mPanelManager = std::make_unique<PanelManager>();
}

void editor::ProjectBrowserLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);

    mImGuiService->NewFrame();
}
