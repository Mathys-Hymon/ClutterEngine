#include <filesystem>
#include <fstream>
#include <EditorUI/Panels/ProjectBrowser/ProjectsPanel.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "json.hpp"
#include "clt/Core/Debug/Log.h"
#include "EditorUI/Managers/ThemeManager.h"
#include "Utils/FileUtils.h"
#include <../../../../../ClutterCore/include/clt/Core/Project/ProjectConfig.h>

#include "clt/Core/Event/ApplicationEvent.h"
#include "clt/Core/Meta/ProjectSerializer.h"
#include "clt/Core/Project/Project.h"
#include "Project/EditorPreferences.h"
#include "Project/EditorSerializer.h"

static float BOTTOM_BAR_HEIGHT = 40.0f;

editor::ProjectPanel::ProjectPanel(EditorContext* context) : EditorPanel(context)
{
     EditorSerializer::LoadPreferences(mPreferences, mContext->engineContext->engineRootPath);
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
        mProjectPathBuffer[0] = '\0';
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
            mProjectPathBuffer[0] = '\0';
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

    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled) && strlen(mProjectPathBuffer) != 0)
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", mProjectPathBuffer);
        ImGui::EndTooltip();
    }

    ImGui::SameLine();
    ImGui::EndDisabled();

    if (!isRecentMenu)
    {
        ImGui::SetNextItemWidth(230.f);
        ImGui::InputTextWithHint("##ProjectName", "Project Name", mProjectName, sizeof(mProjectName));
    }

    ImGui::SameLine();
    if (ImGui::Button("Browse"))
    {
        if (isRecentMenu)
        {
            if (auto path = utils::FileUtils::SelectFile("Clutter Editor", "cltProject"); !path.empty())
            {
                std::strcpy(mProjectPathBuffer, path.c_str());

                CLUTTER_TRACE("Current Folder Path : {}", path);
            }
        }
        else
        {
            if (auto path = utils::FileUtils::SelectFolder(); !path.empty())
            {
                std::strcpy(mProjectPathBuffer, path.c_str());

                CLUTTER_TRACE("Current Folder Path : {}", path);
            }
        }
    }

    ImGui::SameLine();

    if (isRecentMenu)
    {
        const bool fileExist = std::filesystem::exists(mProjectPathBuffer);

        ImGui::BeginDisabled(strlen(mProjectPathBuffer) == 0 || !fileExist);

        if (ImGui::Button("Open Selected", ImVec2(120, 0))) { OpenRecentProject(); }

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
    mContext->themes->BindFont(TextType::title);

    for (auto& proj : mPreferences.recentProjects)
    {
        std::filesystem::path p(proj);

        const std::string projectName = p.stem().string();
        const std::string buttonLabel = projectName + "##" + proj;

        if (ImGui::Button(buttonLabel.c_str()))
        {
            std::strncpy(mProjectPathBuffer, proj.c_str(), sizeof(mProjectPathBuffer) - 1);
            mProjectPathBuffer[sizeof(mProjectPathBuffer) - 1] = '\0';
        }
    }
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
        std::filesystem::copy(templatePath, fullProjectPath, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
        std::filesystem::rename(templateOldName, templateNewName);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        CLT_CORE_FATAL("[PROJECT CREATION] Unable to create new project based on template: {}", e.what());
        return;
    }

    const auto newProject = std::make_shared<clt::Project>();
    newProject->config.GameName = mProjectName;
    newProject->projectDirectory = projectPath;

    clt::ProjectSerializer::Save(templateNewName, newProject);

    clt::ProjectLoadEvent event(templateNewName);
    mContext->engineContext->eventCallback(event);
}

void editor::ProjectPanel::OpenRecentProject()
{
    clt::ProjectLoadEvent event(mProjectPathBuffer);
    mContext->engineContext->eventCallback(event);
}
