#ifndef CLUTTERENGINE_CONTENTBROWSERPANEL_H
#define CLUTTERENGINE_CONTENTBROWSERPANEL_H

#include "EditorUI/EditorPanel.h"
#include "EditorUI/Managers/ThemeManager.h"

namespace editor
{
    struct ContentItem
    {
        std::string Name;
        std::filesystem::path Path;
        AssetType Type;
    };

    struct ContentFolder
    {
        std::string Name;
        std::filesystem::path Path;
        ContentFolder* Parent;
        std::vector<std::unique_ptr<ContentFolder>> Children;
        std::vector<ContentItem> Items;
    };

    class ContentBrowserPanel : public EditorPanel
    {
        ContentFolder mRootFolder;
        ContentFolder* mCurrentFolder;

        ImTextureID mOpenFolderIcon;
        ImTextureID mCloseFolderIcon;
        ImTextureID mFolderIcon;

        bool FolderHasChild(const ContentFolder* folder, ContentFolder* targetChild);

        void ScanFolderRecursive(ContentFolder& folder);

        void DrawFolderTree(ContentFolder* folder);
        void DrawContentItems();
        void ScanFolder();

    public:
        ContentBrowserPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;

        void Draw() override;
    };
}

#endif //CLUTTERENGINE_CONTENTBROWSERPANEL_H