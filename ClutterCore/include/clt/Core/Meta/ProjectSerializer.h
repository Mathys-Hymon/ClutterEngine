#ifndef CLUTTERENGINE_PROJECTSERIALIZER_H
#define CLUTTERENGINE_PROJECTSERIALIZER_H
#include <filesystem>
#include <memory>
#include "../Project/Project.h"

namespace clt
{
    class ProjectSerializer
    {
        public:

        static std::shared_ptr<Project> Load(const std::filesystem::path& filePath);
        static void Save(const std::filesystem::path& filePath, const std::shared_ptr<Project>& project);
    };
}

#endif //CLUTTERENGINE_PROJECTSERIALIZER_H