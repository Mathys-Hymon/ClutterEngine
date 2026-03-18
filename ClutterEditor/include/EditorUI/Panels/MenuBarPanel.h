#ifndef CLUTTERENGINE_MENUBARPANEL_H
#define CLUTTERENGINE_MENUBARPANEL_H
#include "EditorUI/EditorPanel.h"

namespace editor
{
    class MenuBarPanel : public EditorPanel
    {
        public:
        MenuBarPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;
        void Draw() override;

        bool Begin() override;
        void End() override;
    };
}
#endif //CLUTTERENGINE_MENUBARPANEL_H
