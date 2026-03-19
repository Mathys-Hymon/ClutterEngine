#include <EditorUI/Panels/ProjectBrowser/ProjectsPanel.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "clt/Core/Debug/Log.h"
#include "EditorUI/Managers/ThemeManager.h"
#include "Utils/FileUtils.h"

editor::ProjectPanel::ProjectPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* editor::ProjectPanel::GetName() const
{
    return "Project Selector";
}

editor::DockPosition editor::ProjectPanel::GetDockingPosition() const
{
    return DockPosition::none;
}

int editor::ProjectPanel::GetFlags() const
{
    return ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
}

bool editor::ProjectPanel::Begin()
{
    ImGui::SetNextWindowPos(ImGui::GetWindowPos());
    ImGui::SetNextWindowSize(ImGui::GetWindowSize());

    return EditorPanel::Begin();
}

void editor::ProjectPanel::Draw()
{
    constexpr float bottomBarHeight = 40.0f;

    LeftPanel(bottomBarHeight);
    RigthPanel(bottomBarHeight);
    BottomPanel(bottomBarHeight);
}

void editor::ProjectPanel::LeftPanel(const float bottomBarHeight)
{
    ImGui::BeginChild("LeftPanel", ImVec2(250, -bottomBarHeight), true);

    ctx->themes->BindFont(TextType::title);

    if (ImGui::Selectable("Recently Opened", mCurrentState == BrowserState::RecentProjects))
    {
        mCurrentState = BrowserState::RecentProjects;
        mSelectedIndex = -1;
    }

    ImGui::Separator();

    ImGui::TextDisabled("TEMPLATES");

    ctx->themes->BindFont(TextType::classic);

    for (int i = 0; i < 3; i++)
    {
        std::string templateName = "Template 3DS " + std::to_string(i);
        bool isSelected = (mCurrentState == BrowserState::Templates && mSelectedIndex == i);

        if (ImGui::Selectable(templateName.c_str(), isSelected))
        {
            mCurrentState = BrowserState::Templates;
            mSelectedIndex = i;
        }
    }

    ImGui::EndChild();

    ImGui::SameLine();
}

void editor::ProjectPanel::RigthPanel(const float bottomBarHeight)
{
    ImGui::BeginChild("RightPanel", ImVec2(0, -bottomBarHeight), true);

    if (mCurrentState == BrowserState::RecentProjects)
    {
        RenderRecentProjects();
    }
    else if (mCurrentState == BrowserState::Templates)
    {
        RenderTemplateDetails();
    }

    ImGui::EndChild();

}

void editor::ProjectPanel::BottomPanel(const float bottomBarHeight)
{
    ImGui::BeginChild("BottomBar", ImVec2(0, bottomBarHeight), false);

    const bool isRecentMenu = (mCurrentState == BrowserState::RecentProjects);

    ImGui::BeginDisabled(isRecentMenu);

    ctx->themes->BindFont(TextType::title);

    ImGui::Text("PATH: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 200.0f);
    ImGui::InputText("##Path", mProjectPathBuffer, sizeof(mProjectPathBuffer));
    ImGui::SameLine();
    if (ImGui::Button("Browse"))
    {
        auto path = utils::FileUtils::SelectFolder();

        if (path != "")
        {
            CLUTTER_TRACE("Current Folder Path : {}", path);
        }

    }

    ImGui::EndDisabled();

    ImGui::SameLine();

    if (isRecentMenu)
    {
        if (ImGui::Button("Open Selected", ImVec2(120, 0))) { /* Logique d'ouverture */ }
    }
    else
    {
        if (ImGui::Button("Create Project", ImVec2(120, 0))) { /* Logique de création */ }
    }

    ImGui::EndChild();
}

void editor::ProjectPanel::RenderRecentProjects()
{
}

void editor::ProjectPanel::RenderTemplateDetails()
{
}
