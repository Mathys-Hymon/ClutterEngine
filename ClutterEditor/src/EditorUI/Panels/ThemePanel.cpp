#include <EditorUI/Panels/ThemePanel.h>

#include "imgui.h"
#include "clt/Core/Debug/Log.h"
#include "EditorUI/Managers/ThemeManager.h"

editor::ThemePanel::ThemePanel(EditorContext* context) : EditorPanel(context)
{
    Close();
}

const char* editor::ThemePanel::GetName() const
{
    return "Editor Appearance";
}

void editor::ThemePanel::Draw()
{
    if (!mContext || !mContext->themes)
    {
        ImGui::Text("ERROR : Theme Manager not initialized in current Context.");
        CLT_CORE_ERROR("Theme Manager not initialized in current Context.");
        return;
    }

    ImGui::Text("Editor Theme Settings:");
    ImGui::Separator();

    if (ImGui::Button("Save"))
    {
        mContext->themes->SaveTheme();
    }
    ImGui::SameLine();

    if (ImGui::Button("Reset to Default"))
    {
        mContext->themes->ApplyDefaultTheme();
    }
    ImGui::Separator();
    ImGui::Spacing();

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::BeginChild("ColorsList");
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        const char* name = ImGui::GetStyleColorName(i);
        ImGui::PushID(i);
        ImGui::ColorEdit4(name, reinterpret_cast<float*>(&style.Colors[i]), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview);
        ImGui::PopID();
    }
    ImGui::EndChild();
}
