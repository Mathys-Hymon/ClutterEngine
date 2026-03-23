#pragma once
#include <filesystem>
#include <functional>

namespace clt
{
    class Event;
    class IAssetManager;
    class IWindow;
    struct Project;

    namespace engine
    {
        struct Context
        {
            IWindow* window;
            IAssetManager* assets;
            std::shared_ptr<Project> activeProject;
            std::function<void(clt::Event&)> eventCallback;

            std::filesystem::path engineRootPath;
            std::filesystem::path projectPath;
        };
    }
}
