#include <EditorUI/Managers/ThemeManager.h>
#include <filesystem>
#include <fstream>

#include "json.hpp"
#include "clt/Core/Debug/Log.h"

editor::ThemeManager::ThemeManager()
{
    const char* appDataPath = std::getenv("APPDATA");
    std::filesystem::path rootPath;

    if (appDataPath) rootPath = appDataPath;
    else
    {
        const char* drive = std::getenv("SystemDrive");
        rootPath = drive ? drive : "C:\\Program Files";
    }

    std::filesystem::path fullpath = rootPath / std::filesystem::path("ClutterEngine/Editor/EditorAppearance.CltSettings");

    mFilePath = fullpath.string();
    CLT_CORE_INFO("[ThemeManager] Config path set to : {}", mFilePath);

    if (!LoadTheme()) ApplyDefaultTheme();
}


void editor::ThemeManager::ApplyDefaultTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Base palette
    ImVec4 bgColor(0.157f, 0.149f, 0.176f, 1.0f);
    ImVec4 textColor(0.682f, 0.651f, 0.647f, 1.0f);

    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_PopupBg] = bgColor;
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = ImVec4(textColor.x * 0.7f, textColor.y * 0.7f, textColor.z * 0.7f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(bgColor.x * 1.3f, bgColor.y * 1.3f, bgColor.z * 1.3f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(bgColor.x * 0.6f, bgColor.y * 0.6f, bgColor.z * 0.6f, 1.0f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_Tab] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_CheckMark] = textColor;
    colors[ImGuiCol_SliderGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);

    SaveTheme();
}

void editor::ThemeManager::SaveTheme()
{
    nlohmann::json root;
    const ImGuiStyle& style = ImGui::GetStyle();

    if (const std::filesystem::path path(mFilePath); path.has_parent_path())
    {
        try
        {
            std::filesystem::create_directories(path.parent_path());
        } catch (const std::exception& e)
        {
            CLT_CORE_ERROR("[ThemeManager::SaveTheme] Failed to create parent directory");
            return;
        }
    }

    for (size_t i = 0; i < ImGuiCol_COUNT; i++)
    {
        const ImVec4& col = style.Colors[i];
        root["colors"][i] = {col.x, col.y, col.z, col.w};
    }

    std::ofstream file(mFilePath);

    CLT_CORE_ASSERT(!file.is_open(), "[ThemeManager::SaveTheme] Failed to open file '{}'", mFilePath);

    try
    {
        file << root.dump(4);
    } catch (const std::exception& e)
    {
        CLT_CORE_ERROR("[ThemeManager::SaveTheme] JSON Write error : {}", e.what());
        return;
    }
    file.close();

    CLT_CORE_INFO("[ThemeManager::SaveTheme] Theme saved successfully to {}", mFilePath);

}

bool editor::ThemeManager::LoadTheme()
{
    nlohmann::json root;

    if (!std::filesystem::exists(mFilePath))
    {
        CLT_CORE_INFO("[ThemeManager::LoadTheme] No theme file found at '{}', applying default.", mFilePath);
        return false;
    }

    std::ifstream file(mFilePath);

    if (!file.is_open()) return false;

    try
    {
        file >> root;
    } catch (const nlohmann::json::parse_error& e)
    {
        CLT_CORE_ERROR("[ThemeManager::LoadTheme] JSON Parse error in {} : {}", mFilePath, e.what());
        return false;
    }

    file.close();

    ImGuiStyle& style = ImGui::GetStyle();

    if (root.contains("colors"))
    {
        for (size_t i = 0; i < ImGuiCol_COUNT; i++)
        {
            if (i < root["colors"].size())
            {
                if (auto colorArr = root["colors"][i]; colorArr.size() == 4)
                {
                    style.Colors[i] = ImVec4(
                        colorArr[0].get<float>(),
                        colorArr[1].get<float>(),
                        colorArr[2].get<float>(),
                        colorArr[3].get<float>()
                    );
                }
            }
        }
    }

    if (root.contains("fonts"))
    {
        for (size_t i = 0; i < ImGuiCol_COUNT; i++)
        {
            if (i < root["fonts"].size())
            {
                auto fontArr = root["fonts"][i];

                if (fontArr.size() == 4)
                {
                    style.Colors[i] = ImVec4(
                        fontArr[0].get<float>(),
                        fontArr[1].get<float>(),
                        fontArr[2].get<float>(),
                        fontArr[3].get<float>()
                    );
                }
            }
        }
    }

    CLT_CORE_INFO("[ThemeManager::LoadTheme] Theme loaded successfully.");
    return true;
}

void editor::ThemeManager::BindFont(const TextType type)
{
    ImGui::PopFont();
    ImGui::PushFont(mEditorFonts[type]);
}

void editor::ThemeManager::SetFont(const TextType type, const char* fontPath, float fontSize)
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    mEditorFonts[type] = io.Fonts->AddFontFromFileTTF(fontPath, fontSize);
}

clt::Color editor::ThemeManager::GetThemeData(const ImGuiCol_ data)
{
    const ImGuiStyle& style = ImGui::GetStyle();
    const ImVec4* colors = style.Colors;

    return clt::Color{colors[data].x, colors[data].y, colors[data].z, colors[data].w};
}

void editor::ThemeManager::SetAssetIcon(const AssetType type, clt::Texture* texture)
{
    mAssetIcons[type] = texture;
}

clt::Texture* editor::ThemeManager::GetAssetIcon(AssetType type)
{
    const auto temp = mAssetIcons[type];
    if (!temp) return nullptr;

    return temp;
}
