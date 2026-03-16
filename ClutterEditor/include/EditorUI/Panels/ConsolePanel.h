#ifndef CLUTTERENGINE_CONSOLEPANEL_H
#define CLUTTERENGINE_CONSOLEPANEL_H

#include "EditorUI/EditorPanel.h"

namespace editor
{
    class ConsolePanel : public EditorPanel
    {
        bool mShowInfo{false};
        bool mShowTrace{false};
        bool mShowWarning{false};
        bool mShowError{false};
        bool mShowCritical{false};

    public:
        ConsolePanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;

        void Draw() override;
    };
}


#endif //CLUTTERENGINE_CONSOLEPANEL_H