#include <fstream>
#include <Layers/EditorLayer.h>

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

#include "clt/Core/IWindow.h"
#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Level/Level.h"
#include "clt/Core/Meta/ProjectSerializer.h"
#include "clt/Core/Meta/Serializer.h"
#include "clt/Core/Project/Project.h"
#include "Debug/ImGuiConsoleSink.h"
#include "Project/EditorPreferences.h"
#include "Project/EditorSerializer.h"


editor::EditorLayer::EditorLayer() : Layer("Editor Layer")
{
}

void editor::EditorLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    const std::string viewPortName = "Clutter Editor | " + context.activeProject->config.GameName;

    context.window->ResizeViewportCentered({1536, 864});
    context.window->RenameViewport(viewPortName.c_str());

    EditorPreferences prefs;

    EditorSerializer::LoadPreferences(prefs, mContext->engineRootPath);

    const auto path = context.activeProject->projectDirectory / (context.activeProject->config.GameName + ".cltProject");

    const auto it = std::ranges::find(prefs.recentProjects, path.string());

    if (it != prefs.recentProjects.end())
    {
        prefs.recentProjects.erase(it);
    }

    if (prefs.recentProjects.size() > 10)
    {
        prefs.recentProjects.pop_back();
        prefs.recentProjects.push_front(path.string());
    }
    else
    {
        prefs.recentProjects.push_front(path.string());
    }

    std::vector<std::string> emptyProjects;

    for (auto& proj : prefs.recentProjects)
    {
        if (const auto loaded = clt::ProjectSerializer::Load(proj); !loaded) emptyProjects.push_back(proj);
    }

    for (auto& proj : emptyProjects)
    {
        const auto prjIt = std::ranges::find(prefs.recentProjects, proj);

        prefs.recentProjects.erase(prjIt);
    }

    EditorSerializer::SavePreferences(prefs, mContext->engineRootPath);
}

void editor::EditorLayer::OnUpdate(const double dt)
{
    Layer::OnUpdate(dt);
}

void editor::EditorLayer::OnEvent(clt::Event& event)
{
    Layer::OnEvent(event);
}
