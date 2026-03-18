#include <EditorUI/Managers/EditorUiManager.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "EditorUI/EditorPanel.h"
#include "EditorUI/Managers/PanelManager.h"
#include "EditorUI/Managers/ThemeManager.h"

editor::EditorUiManager::EditorUiManager(ImGuiContextService* imgui, EditorContext* ctx) : mImGui(imgui), mEditorContext(ctx)
{
    mTheme = std::make_unique<ThemeManager>();
    ctx->themes = mTheme.get();
}

void editor::EditorUiManager::BeginFrame()
{
    if (mImGui) mImGui->NewFrame();
}

void editor::EditorUiManager::Draw()
{
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

    ImGui::Begin("DockSpace_Main", nullptr, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiID dockSpaceID = ImGui::GetID("DockSpace_Main");
    ImGui::DockSpace(dockSpaceID, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);

    if (!mDockInitialized)
    {
        mDockInitialized = true;

        ImGui::DockBuilderRemoveNode(dockSpaceID);
        ImGui::DockBuilderAddNode(dockSpaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);

        ImGuiID dock_main_id   = dockSpaceID;

        std::unordered_map<DockPosition, ImGuiID> dockingPos;
        dockingPos[DockPosition::bottom] = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
        dockingPos[DockPosition::top]   = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.07f, nullptr, &dock_main_id);
        dockingPos[DockPosition::left]   = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
        dockingPos[DockPosition::right] = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
        dockingPos[DockPosition::center] = dock_main_id;

        for (const auto& panel : mEditorContext->panels->GetPanels())
        {
            auto dock = panel->GetDockingPosition();
            if (dock == DockPosition::none) continue;

            ImGui::DockBuilderDockWindow(panel->GetName(), dockingPos[dock]);
        }

        ImGui::DockBuilderGetNode(dockingPos[DockPosition::top])->LocalFlags |= ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dockingPos[DockPosition::top])->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        ImGui::DockBuilderFinish(dockSpaceID);
    }

    for (const auto& ptr : mEditorContext->panels->GetPanels())
    {
        EditorPanel* panel = ptr.get();
        if (!panel) continue;

        if (panel->Begin())
        {
        panel->Draw();
        }
        panel->End();
    }

    ImGui::End();
}

void editor::EditorUiManager::EndFrame()
{
    if (mImGui) mImGui->Render();
}
