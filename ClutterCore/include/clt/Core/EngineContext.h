#pragma once
#include <filesystem>

namespace clt
{
    class IAssetManager;
    class IWindow;

    namespace engine
    {
        struct Context
        {
            IWindow* window;
            IAssetManager* assets;

            std::filesystem::path engineRootPath;
        };
    }
}
