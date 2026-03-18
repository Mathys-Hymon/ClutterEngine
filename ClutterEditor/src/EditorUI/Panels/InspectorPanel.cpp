#include <EditorUI/Panels/InspectorPanel.h>

editor::InspectorPanel::InspectorPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* editor::InspectorPanel::GetName() const
{
    return "Inspector";
}

editor::DockPosition editor::InspectorPanel::GetDockingPosition() const
{
    return DockPosition::right;
}

void editor::InspectorPanel::Draw()
{
}
