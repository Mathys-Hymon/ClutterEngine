#include <EditorUI/Panels/MenuBarPanel.h>

#include "imgui.h"
#include "EditorUI/Managers/PanelManager.h"
#include "EditorUI/Managers/ThemeManager.h"

editor::MenuBarPanel::MenuBarPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* editor::MenuBarPanel::GetName() const
{
    return "Menu Bar";
}

editor::DockPosition editor::MenuBarPanel::GetDockingPosition() const
{
    return DockPosition::none;
}

void editor::MenuBarPanel::Draw()
{
    /* Example Menu Bar
     * TODO : Open, Edit & Save Projects
     */

    ctx->themes->BindFont(TextType::classic);

        if (ImGui::BeginMenu("File"))
        { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Project Settings")) {}
            if (ImGui::MenuItem("Appearances"))
            {
                if (const auto panel = ctx->panels->FindByID("Editor Appearance")) panel->Open();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                for (auto& panel : ctx->panels->GetPanels())
                {
                    if (ImGui::MenuItem(panel->GetName(), nullptr, panel->IsOpen()))
                    {
                        panel->Toggle();
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }
}

bool editor::MenuBarPanel::Begin()
{
    if (ImGui::BeginMenuBar()) return true;
    else return false;
}

void editor::MenuBarPanel::End()
{
    ImGui::EndMenuBar();
}
