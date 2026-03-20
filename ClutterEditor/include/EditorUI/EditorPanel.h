#ifndef CLUTTERENGINE_EDITORPANEL_H
#define CLUTTERENGINE_EDITORPANEL_H

#include <cstdint>
#include <string>

#include "Services/EditorContext.h"

namespace editor
{
    enum class DockPosition { center, right, left, top, bottom, none};

    class EditorPanel
    {
        bool mIsOpen{true};
        bool mWasOpen{false};
        bool mIsDocked{false};

        protected:
        EditorContext* ctx{nullptr};

        EditorContext* GetContext() const { return ctx; }

        virtual bool Begin();
        virtual void End();

    public:
        EditorPanel(EditorContext* context) : ctx{context} {}
        virtual ~EditorPanel() = default;

        // Visible Label in editor
        virtual const char* GetName() const = 0;

        // Get the docking position in the editor
        virtual DockPosition GetDockingPosition() const { return DockPosition::none; };

        // Draw content only ( dont put any ImGui::Begin / End here)
        virtual void Draw() = 0;

        // Stable internal id ("editor.panel.console") - used for layout / collision / serialization
        virtual std::string GetID() const { return GetName(); }

        // ImGui Window flags for this panel
        virtual int GetFlags() const { return 0; }

        void Open() { mIsOpen = true; }
        void Close()
        {
            mIsOpen = false;
            mWasOpen = false;
        }

        void Toggle()
        {
            mIsOpen = !mIsOpen;
            mWasOpen = mIsOpen;
        }

        bool IsOpen() const { return mIsOpen; }

        friend class EditorUiManager;
    };
}

#endif //CLUTTERENGINE_EDITORPANEL_H