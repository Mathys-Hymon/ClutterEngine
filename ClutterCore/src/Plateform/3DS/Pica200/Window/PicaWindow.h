#ifndef CLUTTERENGINE_PICAWINDOW_H
#define CLUTTERENGINE_PICAWINDOW_H

#include <clt/Core/IWindow.h>
#include <clt/Renderer/GraphicContext.h>

#ifdef CLUTTER_PLATFORM_3DS

namespace clt
{
    class PicaWindow : public IWindow
    {
        std::unique_ptr<graphic::context> mContext;

    };
}

#endif //CLUTTERENGINE_PICAWINDOW_H
#endif