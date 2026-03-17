#ifndef CLUTTERENGINE_INSPECTORPANEL_H
#define CLUTTERENGINE_INSPECTORPANEL_H

#include <EditorUI/EditorPanel.h>

namespace editor
{
    class InspectorPanel : public EditorPanel
    {
    public:
        InspectorPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;
        void Draw() override;
    };
}

#endif //CLUTTERENGINE_INSPECTORPANEL_H