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
            for (const auto entity : level->Registry().view<clt::TagComponent>())
            {
                const bool isSelected = mContext->selectedActor != nullptr && mContext->selectedActor->GetID() == entity;

                auto [tagName] = level->Registry().get<clt::TagComponent>(entity);

                if (ImGui::Selectable(tagName.c_str(), isSelected))
                {
                    mContext->selectedActor = new clt::Actor(entity, level);
                    break;
                }
            }
        }
    }
}
