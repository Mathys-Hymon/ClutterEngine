#include <filesystem>
#include <fstream>
#include <EditorUI/Panels/ProjectBrowser/ProjectsPanel.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "json.hpp"
#include "clt/Core/Debug/Log.h"
#include "EditorUI/Managers/ThemeManager.h"
#include "Utils/FileUtils.h"
#include <clt/Core/Project/ProjectConfig.h>

#include <windows.h>

static float BOTTOM_BAR_HEIGHT = 40.0f;

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
    LeftPanel();
    RightPanel();
    BottomPanel();
}

void editor::ProjectPanel::LeftPanel()
{
    ImGui::BeginChild("LeftPanel", ImVec2(250, -BOTTOM_BAR_HEIGHT), true);

    mContext->themes->BindFont(TextType::title);

    if (ImGui::Selectable("Recently Opened", mCurrentState == BrowserState::RecentProjects))
    {
        mCurrentState = BrowserState::RecentProjects;
        mSelectedIndex = -1;
    }

    ImGui::Separator();

    ImGui::TextDisabled("TEMPLATES");

    mContext->themes->BindFont(TextType::classic);

    for (int i = 0; i < 3; i++)
    {
        std::string templateName = "Template 3DS " + std::to_string(i);

        if (const bool isSelected = (mCurrentState == BrowserState::Templates && mSelectedIndex == i); ImGui::Selectable(templateName.c_str(), isSelected))
        {
            mCurrentState = BrowserState::Templates;
            mSelectedIndex = i;
        }
    }

    ImGui::EndChild();

    ImGui::SameLine();
}

void editor::ProjectPanel::RightPanel()
{
    ImGui::BeginChild("RightPanel", ImVec2(0, -BOTTOM_BAR_HEIGHT), true);

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

void editor::ProjectPanel::BottomPanel()
{
    ImGui::BeginChild("BottomBar", ImVec2(0, BOTTOM_BAR_HEIGHT), false);

    const bool isRecentMenu = (mCurrentState == BrowserState::RecentProjects);

    mContext->themes->BindFont(TextType::title);

    ImGui::BeginDisabled(true);

    ImGui::Text("PATH: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - (!isRecentMenu ? 450.f : 210.f));
    ImGui::InputTextWithHint("##Path","Project Path" ,mProjectPathBuffer, sizeof(mProjectPathBuffer));
    ImGui::SameLine();
    ImGui::EndDisabled();

    if (!isRecentMenu)
    {
        ImGui::SetNextItemWidth(230.f);
        ImGui::InputTextWithHint("##ProjectName", "Project Name", mProjectName, sizeof(mProjectName));
    }

    ImGui::BeginDisabled(isRecentMenu);

    ImGui::SameLine();
    if (ImGui::Button("Browse"))
    {
        if (auto path = utils::FileUtils::SelectFolder(); !path.empty())
        {
            std::strcpy(mProjectPathBuffer, path.c_str());

            CLUTTER_TRACE("Current Folder Path : {}", path);
        }
    }

    ImGui::EndDisabled();

    ImGui::SameLine();

    if (isRecentMenu)
    {
        if (ImGui::Button("Open Selected", ImVec2(120, 0))) { /* OpenProject */ }
    }
    else
    {

        const bool fileExist = std::filesystem::exists(mProjectPathBuffer);

        ImGui::BeginDisabled(strlen(mProjectName) == 0 || strlen(mProjectPathBuffer) == 0 || !fileExist);

        if (ImGui::Button("Create Project", ImVec2(120, 0))) { CreateNewProject(); }

        ImGui::EndDisabled();

        if (!fileExist && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        {
            mContext->themes->BindFont(TextType::classic);

            ImGui::BeginTooltip();
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "Project file does not exist, please select an existing path");
            ImGui::EndTooltip();

            mContext->themes->BindFont(TextType::title);
        }
    }

    ImGui::EndChild();
}


void editor::ProjectPanel::RenderRecentProjects()
{
}

void editor::ProjectPanel::RenderTemplateDetails()
{
}

void editor::ProjectPanel::CreateNewProject()
{
    const std::filesystem::path templatePath = mContext->engineContext->engineRootPath / "EditorContent/Templates/BlankProject";

    const std::filesystem::path projectPath = mProjectPathBuffer;
    const std::filesystem::path fullProjectPath = projectPath / mProjectName;

    const std::string newName = std::string(mProjectName) + ".cltProject";
    const std::filesystem::path templateOldName = fullProjectPath / "Template.cltProject";
    const std::filesystem::path templateNewName = fullProjectPath / newName;

    try
    {
        std::filesystem::create_directory(fullProjectPath);
        std::filesystem::copy(templatePath, fullProjectPath, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
        std::filesystem::rename(templateOldName, templateNewName);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::string errorMsg = "CLUTTER EDITOR CRASH : " + std::string(e.what()) +
                           "\nSource : " + templatePath.string() +
                           "\nDest : " + fullProjectPath.string();

        MessageBoxA(nullptr, errorMsg.c_str(), "[FATAL ERROR] Clutter Editor", MB_OK | MB_ICONERROR);
        return;
    }

    // Set up config

    clt::project::ProjectConfig config;

    config.GameName = mProjectName;
    config.Editor.ContentPath = fullProjectPath.string() + "/Content/";
    config.EngineVersion = "0.0.25";
    config.BuildTarget = "3ds";

    nlohmann::json json = config;

    std::ofstream out(templateNewName);
    out << json.dump(4);
    out.close();
}
