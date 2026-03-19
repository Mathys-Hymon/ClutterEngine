//
// Created by marty on 18/03/2026.
//

#ifndef CLUTTERENGINE_PROJECTSPANEL_H
#define CLUTTERENGINE_PROJECTSPANEL_H
#include "EditorUI/EditorPanel.h"

namespace editor
{
    class ProjectPanel : public EditorPanel
    {
        enum class BrowserState { RecentProjects, Templates };

        BrowserState mCurrentState = BrowserState::RecentProjects;
        int mSelectedIndex = -1;
        char mProjectPathBuffer[256] = "";

        void LeftPanel(const float bottomBarHeight);
        void RigthPanel(const float bottomBarHeight);
        void BottomPanel(const float bottomBarHeight);

        void RenderRecentProjects();
        void RenderTemplateDetails();

    public:

        ProjectPanel(EditorContext* context);
        const char* GetName() const override;
        DockPosition GetDockingPosition() const override;

        int GetFlags() const override;

        bool Begin() override;

        void Draw() override;
    };
}
#endif //CLUTTERENGINE_PROJECTSPANEL_H

