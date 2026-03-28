#ifndef CLUTTERENGINE_EDITORCONTEXT_H
#define CLUTTERENGINE_EDITORCONTEXT_H

#include <clt/Core/EngineContext.h>

namespace clt
{
    class Actor;
}

namespace editor
{
    class PanelManager;
    class ThemeManager;
    struct EditorContext
    {
        const clt::engine::Context* engineContext = nullptr;
        PanelManager* panels = nullptr;
        ThemeManager* themes = nullptr;
        clt::Actor* selectedActor = nullptr;
    };
}

#endif //CLUTTERENGINE_EDITORCONTEXT_H