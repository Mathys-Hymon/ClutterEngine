#include <EditorUI/EditorPanel.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "EditorUI/Managers/ThemeManager.h"

bool editor::EditorPanel::Begin()
{
    if (!mIsOpen) return false;

    bool* pCloseButton = mIsDocked ? nullptr : &mIsOpen;
    ctx->themes->BindFont(TextType::title);

    const bool visible = ImGui::Begin(GetName(), pCloseButton, GetFlags());
    ctx->themes->BindFont(TextType::classic);

    const ImGuiWindow* window = ImGui::GetCurrentWindow();
    mIsDocked = (window->DockNode != nullptr && window->DockNode->HostWindow != nullptr);

    if (mIsOpen) mWasOpen = mIsOpen;

    return visible;
}

void editor::EditorPanel::End()
{
    if (!mWasOpen) return;
    mWasOpen = mIsOpen;
    ImGui::End();
}
