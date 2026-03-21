#ifndef CLUTTERENGINE_EDITORCONTEXT_H
#define CLUTTERENGINE_EDITORCONTEXT_H

#include <clt/Core/EngineContext.h>

namespace editor
{
    class PanelManager;
    class ThemeManager;
    struct EditorContext
    {
        const clt::engine::Context* engineContext = nullptr;
        PanelManager* panels = nullptr;
        ThemeManager* themes = nullptr;
    };
}

#endif //CLUTTERENGINE_EDITORCONTEXT_H