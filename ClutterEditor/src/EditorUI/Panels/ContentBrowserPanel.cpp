#include <EditorUI/Panels/ContentBrowserPanel.h>

editor::ContentBrowserPanel::ContentBrowserPanel(EditorContext* context) : EditorPanel(context)
{
}

bool editor::ContentBrowserPanel::FolderHasChild(ContentFolder* folder, ContentFolder* targetChild)
{
}

void editor::ContentBrowserPanel::ScanFolderRecursive(ContentFolder& folder)
{
}

void editor::ContentBrowserPanel::DrawFolderTree(ContentFolder* folder)
{
}

void editor::ContentBrowserPanel::DrawContentItems()
{
}

void editor::ContentBrowserPanel::ScanFolder()
{
}

const char* editor::ContentBrowserPanel::GetName() const
{
    return "Content Browser";
}

editor::DockPosition editor::ContentBrowserPanel::GetDockingPosition() const
{
    return DockPosition::bottom;
}

void editor::ContentBrowserPanel::Draw()
{
}
