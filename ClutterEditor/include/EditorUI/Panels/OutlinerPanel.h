#ifndef CLUTTERENGINE_OUTLINERPANEL_H
#define CLUTTERENGINE_OUTLINERPANEL_H

#include <EditorUI/EditorPanel.h>

namespace editor
{
    class OutlinerPanel : public EditorPanel
    {
    public:
        OutlinerPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;
        void Draw() override;
    };
}

#endif //CLUTTERENGINE_OUTLINERPANEL_H