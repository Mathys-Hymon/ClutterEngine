#ifndef CLUTTERENGINE_ENGINE_CONTEXT_H
#define CLUTTERENGINE_ENGINE_CONTEXT_H

#include <filesystem>
#include <functional>

namespace clt
{
    class Event;
    class LevelManager;
    class IAssetManager;
    class IWindow;
    struct Project;

    namespace engine
    {
        struct Context
        {
            IWindow* window;
            IAssetManager* assets;
            LevelManager* level;
            std::shared_ptr<Project> activeProject;
            std::function<void(Event&)> eventCallback;

            std::filesystem::path engineRootPath;
        };
    }
}

#endif