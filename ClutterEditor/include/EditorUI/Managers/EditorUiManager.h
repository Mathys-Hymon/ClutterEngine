#ifndef CLUTTERENGINE_EDITORUIMANAGER_H
#define CLUTTERENGINE_EDITORUIMANAGER_H

#include <memory>

#include "Services/EditorContext.h"
#include "Services/ImGuiContextService.h"
#include <EditorUI/Managers/ThemeManager.h>

namespace editor
{
    class EditorUiManager
    {
        ImGuiContextService* mImGui{nullptr};
        EditorContext* mEditorContext{nullptr};

        bool mDockInitialized{false};
        std::unique_ptr<ThemeManager> mTheme{nullptr};

    public:
        EditorUiManager(ImGuiContextService* imgui, EditorContext* ctx);
        ~EditorUiManager() = default;

        void BeginFrame();
        void Draw();
        void EndFrame();
    };
}
#endif //CLUTTERENGINE_EDITORUIMANAGER_H