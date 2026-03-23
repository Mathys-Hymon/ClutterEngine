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


editor::EditorLayer::EditorLayer(const clt::ApplicationCommandLineArgs& args) : Layer("Editor Layer")
{
    auto project = args.Args[1];
}

void editor::EditorLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    context.window->ResizeViewportCentered(1280.0f, 720.0f);
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
