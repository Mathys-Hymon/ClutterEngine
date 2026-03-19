#ifndef CLUTTERENGINE_EDITORPREFERENCES_H
#define CLUTTERENGINE_EDITORPREFERENCES_H

#include <string>
#include <vector>
#include <json.hpp>

namespace editor
{
    struct EditorPreferences
    {
        std::vector<std::string> RecentProjects;
    };

    struct ProjectTemplate
    {
        std::string Name;
        std::string Description;
        std::string IconPath;
        std::vector<std::string> Images;
        std::vector<std::string> Tags;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EditorPreferences, RecentProjects);
}

#endif //CLUTTERENGINE_EDITORPREFERENCES_H