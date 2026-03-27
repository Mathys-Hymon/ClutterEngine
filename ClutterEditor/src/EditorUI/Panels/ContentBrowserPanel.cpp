#include <EditorUI/Panels/ContentBrowserPanel.h>

#include "clt/Core/Assets/IAssetManager.h"
#include "clt/Core/Assets/AssetType/Texture.h"
#include "clt/Core/Project/Project.h"

editor::ContentBrowserPanel::ContentBrowserPanel(EditorContext* context) : EditorPanel(context)
{
    mOpenFolderIcon = context->engineContext->assets->LoadTexture(
        clt::PathType::engine,
        "Resources/Textures/folderIconOpened.png",
        "folder Opened Icon",
        clt::TextureFilter::LINEAR, true, false)->GetID();

    mCloseFolderIcon = context->engineContext->assets->LoadTexture(clt::PathType::engine,
        "Resources/Textures/folderIconClosed.png",
        "folder Closed Icon",
        clt::TextureFilter::LINEAR, true, false)->GetID();

    mFolderIcon = context->engineContext->assets->LoadTexture(clt::PathType::engine,
        "Resources/Textures/folder.png", "folder Icon",
        clt::TextureFilter::LINEAR, true, false)->GetID();

    mRootFolder.Name = "ContentFolder";
    mRootFolder.Path = context->engineContext->activeProject->projectDirectory / "Content";
    mRootFolder.Parent = nullptr;

    mCurrentFolder = &mRootFolder;

    ScanFolder();
}

bool editor::ContentBrowserPanel::FolderHasChild(const ContentFolder* folder, ContentFolder* targetChild)
{
    if (!folder) return false;

    for (auto& child : folder->Children)
    {
        if (child.get() == targetChild) return true;

        if (FolderHasChild(child.get(), targetChild)) return true;
    }

    return false;
}

void editor::ContentBrowserPanel::ScanFolderRecursive(ContentFolder& folder)
{
    namespace fs = std::filesystem;

    for (auto& p : fs::directory_iterator(folder.Path))
    {
        if (p.is_directory())
        {
            auto child = std::make_unique<ContentFolder>();
            child->Name = p.path().filename().string();
            child->Path = p.path();
            child->Parent = &folder;

            ContentFolder* childPtr = child.get();

            folder.Children.push_back(std::move(child));
            ScanFolderRecursive(*childPtr);
        }
        else if (p.is_regular_file())
        {
            ContentItem item;
            item.Name = p.path().filename().string();
            item.Path = p.path();

            std::string ext;
            ext = p.path().extension().string();

            if (ext == ".png" || ext == ".jpg") item.Type = AssetType::texture;
            else if (ext == ".fbx" || ext == ".obj") item.Type = AssetType::mesh;
            else if (ext == ".ttf") item.Type = AssetType::font;
            else if (ext == ".wav" || ext == ".mp3" || ext == ".avi") item.Type = AssetType::sound;
            else if (ext == ".cltLevel") item.Type = AssetType::level;
            else if (ext == ".cpp" || ext == ".h") item.Type = AssetType::script;
            else if (ext == ".frag" || ext == ".tese" || ext == ".vert" || ext == ".tesc" || ext == ".CMaterial") item.Type = AssetType::shader;
            else item.Type = AssetType::unknown;

            if (item.Type == AssetType::texture) mContext->engineContext->assets->LoadTexture(clt::PathType::none, item.Path.string(), item.Name, clt::TextureFilter::LINEAR, true, false);
            folder.Items.push_back(item);
        }
    }
}

void editor::ContentBrowserPanel::DrawFolderTree(ContentFolder* folder)
{
    const bool isSelected = folder == mCurrentFolder;

    bool childSelected = false;
    for (auto& child : folder->Children)
    {
        if (FolderHasChild(child.get(), mCurrentFolder))
        {
            childSelected = true;
            break;
        }
    }

    if (childSelected || isSelected) ImGui::SetNextItemOpen(true, ImGuiCond_Always);

    ImGuiTreeNodeFlags flags = isSelected ? ImGuiTreeNodeFlags_Selected : 0;

    if (folder->Children.empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

        const std::string label = "##" + folder->Name;
        ImGui::TreeNodeEx(label.c_str(), flags);

        ImGui::SameLine();
        if (mCloseFolderIcon) ImGui::Image(isSelected ? mOpenFolderIcon : mCloseFolderIcon, ImVec2(16, 16));
        ImGui::SameLine();
        ImGui::Text("%s", folder->Name.c_str());

        if (ImGui::IsItemClicked(0)) mCurrentFolder = folder;
    }
    else
    {
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;

        const std::string label = "##" + folder->Name;
        const bool nodeOpen = ImGui::TreeNodeEx(label.c_str(), flags);

        ImGui::SameLine();
        if (const ImTextureID icon = nodeOpen || isSelected ? mOpenFolderIcon : mCloseFolderIcon) ImGui::Image(icon, ImVec2(16, 16));

        ImGui::SameLine();
        ImGui::Text("%s", folder->Name.c_str());

        if (ImGui::IsItemClicked(0)) mCurrentFolder = folder;

        if (nodeOpen)
        {
            for (auto& child : folder->Children) DrawFolderTree(child.get());

            ImGui::TreePop();
        }
    }
}

void editor::ContentBrowserPanel::DrawContentItems()
{
    if (!mCurrentFolder) { ImGui::EndChild(); ImGui::End(); return; }

    constexpr float cellSize = 74.0f;
    const ImVec2 availRegion = ImGui::GetContentRegionAvail();
    float x = 0.0f;

// --- Return Folder ---

clt::Color hoverColor = GetContext()->themes->GetThemeData(ImGuiCol_ButtonHovered);
hoverColor.a = 0.3f;

if (mCurrentFolder != &mRootFolder)
{
    ImGui::BeginGroup();
    if (mFolderIcon) ImGui::Image(mFolderIcon, ImVec2(64,64));

    if (ImGui::IsItemHovered())
    {
        const ImVec2 min = ImGui::GetItemRectMin();
        const ImVec2 max = ImGui::GetItemRectMax();

        const ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

        ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
    }

    if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
    {
        if (const auto parent = mCurrentFolder->Parent) mCurrentFolder = parent;
    }
    ImGui::TextWrapped("..");

    ImGui::EndGroup();
    ImGui::SameLine(0, 10);

    x += 74;
}

// Draw all child folder in folder ---

for (auto& childPtr : mCurrentFolder->Children)
{
    ContentFolder& child = *childPtr;

    if (x + cellSize > availRegion.x)
    {
        ImGui::NewLine();
        x = 0.0f;
    }

    ImGui::BeginGroup();

    ImVec2 folderSize(64, 64);

    if (mFolderIcon) ImGui::Image(mFolderIcon, folderSize);

    if (ImGui::IsItemHovered())
    {
        ImVec2 min = ImGui::GetItemRectMin();
        ImVec2 max = ImGui::GetItemRectMax();

        const ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

        ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
    }

    const ImVec2 textSize = ImGui::CalcTextSize(child.Name.c_str());
    const float textPosX = ImGui::GetCursorPosX() + (folderSize.x - textSize.x) * 0.5f;

    ImGui::SetCursorPosX(textPosX);
    ImGui::TextWrapped("%s", child.Name.c_str());

    ImGui::EndGroup();
    ImGui::SameLine(0, 10);
    x += 74;

    if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
    {
        mCurrentFolder = &child;
        break;
    }
}

// --- Draw all Items in the folder ---

for (auto& [Name, Path, Type] : mCurrentFolder->Items)
{
    if (x + cellSize > availRegion.x)
    {
        ImGui::NewLine();
        x = 0.0f;
    }

    ImGui::BeginGroup();
    ImTextureID icon = 0;

    const clt::Texture* tex = nullptr;
    ImVec2 texSize;

    switch (Type)
    {
    case AssetType::texture: // Use texture render for Icon if texture

        tex = mContext->engineContext->assets->GetTexture( clt::PathType::none, Path.string());

        if (tex)
        {
            const auto texID = tex->GetID();
            icon = static_cast<ImTextureID>(static_cast<intptr_t>(texID));

            texSize = ImVec2(64, 64);
            ImGui::Image(icon, texSize);

            if (ImGui::IsItemHovered())
            {
                ImVec2 min = ImGui::GetItemRectMin();
                ImVec2 max = ImGui::GetItemRectMax();

                const ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

                ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
            }
        }
        break;

    default:

        tex = GetContext()->themes->GetAssetIcon(Type);

        if (tex)
        {
            const auto texID = tex->GetID();
            icon = static_cast<ImTextureID>(static_cast<intptr_t>(texID));

            texSize = { 64, 64 };

            ImGui::Image(icon, texSize);

            if (ImGui::IsItemHovered())
            {
                ImVec2 min = ImGui::GetItemRectMin();
                ImVec2 max = ImGui::GetItemRectMax();

                const ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

                ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
            }
        }
        break;
    }

    const ImVec2 size = ImGui::CalcTextSize(Name.c_str());

    std::string displayName = Name;
    if (size.x > texSize.x)
    {
        unsigned long long chars = Name.size();
        while (chars > 0 && ImGui::CalcTextSize(displayName.c_str()).x > texSize.y)
        {
            chars--;
            displayName = Name.substr(0, chars) + "..";
        }
    }

    const float textPosX = ImGui::GetCursorPosX() + (texSize.x - ImGui::CalcTextSize(displayName.c_str()).x) * 0.5f;
    ImGui::SetCursorPosX(textPosX);
    ImGui::Text("%s", displayName.c_str());

    ImGui::EndGroup();
    ImGui::SameLine(0, 10);
    x += 74;

    //if (clt::JsonUtility::EndsWith(item.Name, ".CMaterial"))
    //{
    //    std::string path = mCurrentFolder->Path + item.Name + ".CMaterial";
    //
    //    materialGraphEditor->LoadGraphFromFile(path);
    //}
}
}

void editor::ContentBrowserPanel::ScanFolder()
{
    mRootFolder.Children.clear();
    mRootFolder.Items.clear();

    ScanFolderRecursive(*mCurrentFolder);
}

const char* editor::ContentBrowserPanel::GetName() const
{
    return "Content Browser";
}

editor::DockPosition editor::ContentBrowserPanel::GetDockingPosition() const {return DockPosition::bottom;}

void editor::ContentBrowserPanel::Draw()
{
    static float mHierarchyWidth = 250.0f;

    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 12.0f);

    ImGui::BeginChild("Hierarchy", ImVec2(mHierarchyWidth, 0), true);
    DrawFolderTree(&mRootFolder);
    ImGui::EndChild();

    ImGui::PopStyleVar();

    ImGui::SameLine();

    ImGui::InvisibleButton("Splitter", ImVec2(5.0f, -1.0f));

    if (ImGui::IsItemActive())
    {
        mHierarchyWidth += ImGui::GetIO().MouseDelta.x;
        if (mHierarchyWidth < 150.0f) mHierarchyWidth = 150.0f;   // min width
        if (mHierarchyWidth > 800.0f) mHierarchyWidth = 800.0f;  // max width
    }
    ImGui::SameLine();

    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    // ---- Top Breadcrumb ----

    ContentFolder* folder = mCurrentFolder;
    std::vector<ContentFolder*> hierarchy;

    while (folder)
    {
        hierarchy.push_back(folder);
        folder = folder->Parent;
    }

    std::ranges::reverse(hierarchy);

    for (size_t i = 0; i < hierarchy.size(); i++)
    {
        if (ContentFolder* f = hierarchy[i]; ImGui::SmallButton(f->Name.c_str()))
        {
            mCurrentFolder = f;
        }

        if (i < hierarchy.size() - 1)
        {
            ImGui::SameLine(0, 5);
            ImGui::Text(">");
            ImGui::SameLine();
        }
    }

    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 2.0f));

    DrawContentItems();

    ImGui::NewLine();
    ImGui::EndChild();
}
