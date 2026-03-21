#pragma once
#include <filesystem>

namespace clt
{
    class IWindow;

    namespace engine
    {
        struct Context
        {
            IWindow* Window;
            std::filesystem::path EngineRootPath;
        };
    }
}
