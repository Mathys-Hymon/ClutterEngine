#ifndef CLUTTERENGINE_EDITORCONTEXT_H
#define CLUTTERENGINE_EDITORCONTEXT_H

namespace editor
{
    class PanelManager;
    class ThemeManager;
    struct EditorContext
    {
        PanelManager* panels = nullptr;
        ThemeManager* themes = nullptr;
    };
}

#endif //CLUTTERENGINE_EDITORCONTEXT_H