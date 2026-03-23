#ifndef CLUTTERENGINE_PROJECT_H
#define CLUTTERENGINE_PROJECT_H
#include "ProjectConfig.h"
#include <filesystem>

namespace clt
{
    struct Project
    {
        clt::project::ProjectConfig config;
        std::filesystem::path projectDirectory;

        std::filesystem::path GetAssetDirectory() const { return projectDirectory / config.Game.ContentPath; };
    };
}

#endif //CLUTTERENGINE_PROJECT_H