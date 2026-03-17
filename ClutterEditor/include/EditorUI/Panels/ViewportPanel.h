#ifndef CLUTTERENGINE_VIEWPORTPANEL_H
#define CLUTTERENGINE_VIEWPORTPANEL_H

#include <EditorUI/EditorPanel.h>

namespace editor
{
    class ViewportPanel : public EditorPanel
    {
        uint32_t moveIconID;
        uint32_t moveIconActiveID;
        uint32_t rotateIconID;
        uint32_t rotateIconActiveID;
        uint32_t scaleIconID;
        uint32_t scaleIconActiveID;
    public:
        ViewportPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;
        void Draw() override;
    };
}

#endif //CLUTTERENGINE_VIEWPORTPANEL_H