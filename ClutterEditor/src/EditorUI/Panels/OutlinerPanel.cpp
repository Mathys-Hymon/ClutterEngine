#include <EditorUI/Panels/OutlinerPanel.h>

#include "imgui.h"
#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Level/LevelManager.h"

editor::OutlinerPanel::OutlinerPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* editor::OutlinerPanel::GetName() const
{
    return "Outliner";
}

editor::DockPosition editor::OutlinerPanel::GetDockingPosition() const
{
    return DockPosition::left;
}

void editor::OutlinerPanel::Draw()
{
    if (const auto manager = mContext->engineContext->level)
    {
        if (clt::Level* level = manager->GetCurrentLevel())
        {

            if (ImGui::InputTextWithHint( "##ActorNameSearchInput", "Actor Name", mFilterBuffer, sizeof(mFilterBuffer)))
            {
                mFilterName = std::string(mFilterBuffer);
            }

            ImGui::Separator();

            for (const auto entity : level->Registry().view<clt::Name>())
            {
                const bool isSelected = mContext->selectedActor != nullptr && mContext->selectedActor->GetID() == entity;

                auto& [tagName] = level->Registry().get<clt::Name>(entity);

                if (!mFilterName.empty())
                {
                    auto filterCopy = mFilterName;
                    auto tagCopy = tagName;

                    for (auto& c : filterCopy) c = static_cast<char>(std::tolower(c));
                    for (auto& c : tagCopy) c = static_cast<char>(std::tolower(c));

                    const auto find = tagCopy.find(filterCopy);
                    if (find == std::string::npos) continue;

                    // DRAW TEXT RECTANGLE

                    std::string prefix = tagName.substr(0, find);
                    const ImVec2 prefixSize = ImGui::CalcTextSize(prefix.c_str());

                    std::string matchText = tagName.substr(find, mFilterName.size());
                    const ImVec2 matchSize = ImGui::CalcTextSize(matchText.c_str());

                    const ImVec2 cursorPos = ImGui::GetCursorScreenPos();
                    auto rectMin = ImVec2(cursorPos.x + prefixSize.x, cursorPos.y);
                    auto rectMax = ImVec2(rectMin.x + matchSize.x, rectMin.y + matchSize.y);

                    ImGui::GetWindowDrawList()->AddRectFilled(rectMin, rectMax, IM_COL32(255, 255, 0, 100));
                }

                if (ImGui::Selectable(tagName.c_str(), isSelected))
                {
                    mContext->selectedActor = new clt::Actor(entity, level);
                    break;
                }

            }
        }
    }
}
