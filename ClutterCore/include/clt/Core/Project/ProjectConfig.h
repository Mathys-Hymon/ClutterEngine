#ifndef CLUTTERENGINE_PROJECTCONFIG_H
#define CLUTTERENGINE_PROJECTCONFIG_H
#include <string>
#include <json.hpp>

namespace clt::project
{
    struct GraphicsSettings
    {
        bool VSync = false;
        std::string RendererAPI = "OpenGL";
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GraphicsSettings, VSync, RendererAPI);

    struct PhysicsSettings
    {
        bool is2D = true;
        std::string PhysicAPI = "temp";
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PhysicsSettings, is2D, PhysicAPI);

    struct EditorSettings
    {
        std::string ContentPath = "";
        std::string EditorStartingLevel = "Scenes/Default.cltMap";
        std::string GameStartingLevel = "Scenes/Default.cltMap";
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EditorSettings, ContentPath, EditorStartingLevel, GameStartingLevel);

    struct ProjectConfig
    {
        std::string GameName = "Template Project";
        std::string EngineVersion = "0.0.1";
        std::string BuildTarget = "new3Ds";

        GraphicsSettings Graphics;
        PhysicsSettings Physics;
        EditorSettings Editor;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ProjectConfig, GameName, EngineVersion, BuildTarget, Graphics, Physics, Editor);
}

#endif //CLUTTERENGINE_PROJECTCONFIG_H