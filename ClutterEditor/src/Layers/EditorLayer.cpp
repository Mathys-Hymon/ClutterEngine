#include <Layers/EditorLayer.h>

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Level/Level.h"
#include "clt/Core/Meta/Serializer.h"
#include "Debug/ImGuiConsoleSink.h"


editor::EditorLayer::EditorLayer() : Layer("Editor Layer")
{
}

void editor::EditorLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    // const auto size = context.window->GetMonitorSize();
    //
    // const clt::Vector2 clampedSize = {std::clamp(size.x, 0.f, 1920.f), std::clamp(size.y, 0.f, 1080.f)};
    //
    // context.window->ResizeViewportCentered(clampedSize);

    context.window->ResizeViewportCentered({1536, 864});
    context.window->RenameViewport("Clutter Editor");
}

void editor::EditorLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);
}

void editor::EditorLayer::OnEvent(clt::Event& event)
{
    Layer::OnEvent(event);
}
