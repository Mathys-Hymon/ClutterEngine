#include <EditorUI/Panels/ConsolePanel.h>

#include "imgui.h"
#include "Debug/LogHistory.h"

editor::ConsolePanel::ConsolePanel(EditorContext* context) : EditorPanel(context)
{}

const char* editor::ConsolePanel::GetName() const
{
    return "Console";
}

editor::DockPosition editor::ConsolePanel::GetDockingPosition() const
{
    return DockPosition::bottom;
}

void editor::ConsolePanel::Draw()
{
    constexpr ImVec4 infoColor(0.4f, 1.0f, 0.4f, 1.0f);
    constexpr ImVec4 traceColor(1.0f, 1.0f, 1.0f, 1.0f);
    constexpr ImVec4 warningColor(1.0f, 1.0f, 0.2f, 1.0f);
    constexpr ImVec4 errorColor(1.0f, 0.2f, 0.2f, 1.0f);
    constexpr ImVec4 criticalColor(1.0f, 0.2f, 0.2f, 1.0f);

    auto drawFilterButton = [](const char* label, bool& active, ImVec4 color)
    {
        auto baseColor = ImVec4(0.133f, 0.127f, 0.150f, 1.0f);
        if (active) baseColor = ImVec4(0.110f, 0.104f, 0.123f, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_Button, baseColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(baseColor.x + 0.1f, baseColor.y + 0.1f, baseColor.z + 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, baseColor);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 6));

        bool pushedColor = false;

        if (active)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, color);pushedColor = true;
        }

        if (ImGui::Button(label))active = !active;
        if (pushedColor)ImGui::PopStyleColor();

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
    };

    drawFilterButton("INFO", mShowInfo, infoColor);    ImGui::SameLine();
    drawFilterButton("LOG", mShowTrace, traceColor);     ImGui::SameLine();
    drawFilterButton("WARNING", mShowWarning, warningColor); ImGui::SameLine();
    drawFilterButton("ERROR", mShowError, errorColor); ImGui::SameLine();
    drawFilterButton("CRITICAL", mShowCritical, errorColor);

    ImGui::BeginChild("LogRegion", ImVec2(0, -30), true);

    const bool noFilterActive = !mShowInfo && !mShowTrace && !mShowWarning && !mShowError && !mShowCritical;

    for (const auto& [message, level] : log::LogHistory::GetEntry())
    {
        bool show = noFilterActive;

        if (!show)
        {
            switch (level)
            {
                case spdlog::level::level_enum::info:     show = mShowInfo;     break;
                case spdlog::level::level_enum::trace:    show = mShowTrace;    break;
                case spdlog::level::level_enum::warn:     show = mShowWarning;  break;
                case spdlog::level::level_enum::err:      show = mShowError;    break;
                case spdlog::level::level_enum::critical: show = mShowCritical; break;
                default:                                  show = true;          break;
            }
        }

        if (show)
        {
            ImVec4 color;
            switch (level)
            {
                case spdlog::level::level_enum::info:     color = infoColor;      break;
                case spdlog::level::level_enum::trace:    color = traceColor;     break;
                case spdlog::level::level_enum::warn:     color = warningColor;   break;
                case spdlog::level::level_enum::err:      color = errorColor;     break;
                case spdlog::level::level_enum::critical: color =  criticalColor; break;
                default:                                  color = traceColor;     break;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextWrapped("%s", message.c_str());
            ImGui::PopStyleColor();
        }
    }

    ImGui::EndChild();

    ImGui::SetCursorPosY(ImGui::GetWindowContentRegionMax().y - ImGui::GetFrameHeight());
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("Clear").x - ImGui::GetStyle().FramePadding.x * 2);

    if (ImGui::Button("Clear")) log::LogHistory::ClearLogs();
}
