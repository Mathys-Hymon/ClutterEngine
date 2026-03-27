#ifndef CLUTTERENGINE_VIEWPORTPANEL_H
#define CLUTTERENGINE_VIEWPORTPANEL_H

#include <EditorUI/EditorPanel.h>

namespace editor
{
    class ViewportPanel : public EditorPanel
    {
        uint32_t moveIconID{0};
        uint32_t moveIconActiveID{0};
        uint32_t rotateIconID{0};
        uint32_t rotateIconActiveID{0};
        uint32_t scaleIconID{0};
        uint32_t scaleIconActiveID{0};
    public:
        explicit ViewportPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;
        void Draw() override;
    };
}

#endif //CLUTTERENGINE_VIEWPORTPANEL_H