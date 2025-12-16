#pragma once

namespace clt
{
    class IWindow;

    struct EngineContext
    {
        IWindow* Window;

        EngineContext(IWindow* window) : Window(window) {}
    };
}