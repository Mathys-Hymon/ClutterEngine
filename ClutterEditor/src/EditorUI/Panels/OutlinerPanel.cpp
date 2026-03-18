#include <EditorUI/Panels/OutlinerPanel.h>

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
}
