#ifndef CLUTTERENGINE_THEMEMANAGER_H
#define CLUTTERENGINE_THEMEMANAGER_H

#pragma warning(disable: 4996)
#include <unordered_map>

#include <string>

#include "imgui.h"
#include "clt/Core/Math/Math.h"

enum ImGuiCol_;
struct ImFont;

namespace clt
{
class Texture;
}

namespace editor
{
    enum class TextType { classic, title, console};
    enum class AssetType { Texture, Mesh, Font, Sound, Shader, Script, Unknown };

    class ThemeManager
    {
        std::string mFilePath;

        std::unordered_map<AssetType, clt::Texture*> mAssetIcons;
        std::unordered_map<TextType, ImFont*> mEditorFonts;

    public:
        ThemeManager();
        ~ThemeManager() = default;

        void ApplyDefaultTheme();
        void SaveTheme();
        bool LoadTheme();

        void BindFont(TextType type);
        void SetFont(TextType type, const char* fontPath, float fontSize = 15.f);

        clt::Color GetThemeData(ImGuiCol_ data);

        void SetAssetIcon(AssetType type, clt::Texture* texture);
        clt::Texture* GetAssetIcon(AssetType type);

    };
}
#endif //CLUTTERENGINE_THEMEMANAGER_H