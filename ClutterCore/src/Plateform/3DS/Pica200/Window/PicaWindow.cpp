//
// Created by marty on 31/03/2026.
//

#include "PicaWindow.h"

#ifdef CLUTTER_PLATFORM_3DS

clt::IWindow* clt::IWindow::Create(const clt::WindowProps& props)
{
    return new PicaWindow(props);
}

#endif