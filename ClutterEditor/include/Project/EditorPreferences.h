#ifndef CLUTTERENGINE_EDITORPREFERENCES_H
#define CLUTTERENGINE_EDITORPREFERENCES_H

#include <deque>
#include <string>
#include <vector>
#include <json.hpp>

namespace editor
{
    struct EditorPreferences
    {
        std::deque<std::string> recentProjects;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EditorPreferences, recentProjects);

    struct ProjectTemplate
    {
        std::string name;
        std::string description;
        std::string iconPath;
        std::vector<std::string> images;
        std::vector<std::string> tags;
    };

}

#endif //CLUTTERENGINE_EDITORPREFERENCES_H