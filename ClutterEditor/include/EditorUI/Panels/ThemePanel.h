#ifndef CLUTTERENGINE_THEMEPANEL_H
#define CLUTTERENGINE_THEMEPANEL_H
#include "EditorUI/EditorPanel.h"

namespace editor
{
    class ThemePanel : public EditorPanel
    {
        public:
        ThemePanel(EditorContext* context);
        const char* GetName() const override;
        void Draw() override;
    };
}
#endif //CLUTTERENGINE_THEMEPANEL_H
