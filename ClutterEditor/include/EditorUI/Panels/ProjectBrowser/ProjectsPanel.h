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
        int mSelectedIndex{-1};
        char mProjectPathBuffer[256]{""};
        char mProjectName[256]{""};

        void LeftPanel();
        void RightPanel();
        void BottomPanel();

        void RenderRecentProjects();
        void RenderTemplateDetails();

        void CreateNewProject();

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

