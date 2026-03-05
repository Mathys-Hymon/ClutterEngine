#pragma once

namespace clt
{
    class IWindow;

    namespace engine
    {
        struct Context
        {
            IWindow* Window;

            Context(IWindow* window) : Window(window) {}
        };
    }
}