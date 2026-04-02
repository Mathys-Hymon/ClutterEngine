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

    namespace graphic
    {
        class Renderer;
    }

    namespace engine
    {
        struct Context
        {
            IWindow* window;
            IAssetManager* assets;
            LevelManager* level;
            graphic::Renderer* renderer;
            std::shared_ptr<Project> activeProject;
            std::function<void(Event&)> eventCallback;

            std::filesystem::path engineRootPath;
        };
    }
}

#endif