#pragma once
#include  "Window/IWindow.h"

namespace clt
{
    struct EngineContext
    {
        IWindow* Window;

        EngineContext(IWindow* window) : Window(window) {}
    };
}