#include <fstream>
#include <Project/EditorSerializer.h>

#include "clt/Core/Debug/Log.h"
#include <Project/EditorPreferences.h>

bool editor::EditorSerializer::LoadPreferences(EditorPreferences& outPrefs, const std::filesystem::path& engineRootPath)
{
    const auto fullpath = engineRootPath / "Config/EditorPreferences.ini";

    std::ifstream ifs(fullpath);
    if (!ifs.is_open())
    {
        CLUTTER_WARN("Failed to open editor Preferences: {}", fullpath.string());
        return false;
    }

    nlohmann::json data;
    try
    {
        ifs >> data;
    } catch (std::exception& e)
    {
        CLUTTER_WARN("Failed to load editor Preferences: {}", e.what());
        return false;
    }

    outPrefs = data.get<EditorPreferences>();
    CLUTTER_TRACE("Editor Preferences loaded successfully at: {}", fullpath.string());

    return true;
}

void editor::EditorSerializer::SavePreferences(const EditorPreferences& prefs, const std::filesystem::path& engineRootPath)
{
    const auto fullpath = engineRootPath / "Config/EditorPreferences.ini";

    if (!std::filesystem::exists(fullpath.parent_path()))
    {
        std::filesystem::create_directories(fullpath.parent_path());
    }

    std::ofstream ofs(fullpath);

    if (!ofs.is_open())
    {
        CLUTTER_ERROR("Failed to open editor Preferences: {}", fullpath.string());
        return;
    }

    const nlohmann::json data(prefs);
    try
    {
        ofs << data.dump(4);
    } catch (std::exception& e)
    {
        CLUTTER_ERROR("Failed to save editor Preferences: {}", e.what());
    }

    CLUTTER_TRACE("Editor Preferences saved successfully at: {}", fullpath.string());
}