#include <clt/Core/Meta/ProjectSerializer.h>
#include <fstream>
#include "clt/Core/Debug/Log.h"


std::shared_ptr<clt::Project> clt::ProjectSerializer::Load(const std::filesystem::path& filePath)
{
    auto project = std::make_shared<clt::Project>();

    std::ifstream ifs(filePath);

    if(!ifs.is_open())
    {
        CLT_CORE_ERROR( "[PROJECT LOADER] Cannot open project: {}", filePath.string());
        return nullptr;
    }

    nlohmann::json data;

    try
    {
        ifs >> data;
    }catch(std::exception& e)
    {
        CLT_CORE_ERROR("[PROJECT LOADER] Failed to parse project: {}", e.what());
        return nullptr;
    }

    project->config = data.get<project::ProjectConfig>();
    project->projectDirectory = filePath.parent_path();

    ifs.close();

    return project;
}

void clt::ProjectSerializer::Save(const std::filesystem::path& filePath, const std::shared_ptr<Project>& project)
{
    std::ofstream ofs(filePath.string());

    if(!ofs.is_open())
    {
        CLT_CORE_ERROR( "[PROJECT SAVE] Cannot open project: {}", filePath.string());
        return;
    }

    const nlohmann::json data = project->config;

    try
    {
        ofs << data.dump(4);
    } catch(std::exception& e)
    {
        CLT_CORE_ERROR("[PROJECT SAVE] Failed to write project: {}", e.what());
    }

    ofs.close();
}
