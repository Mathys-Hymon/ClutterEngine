#include <EditorUI/Panels/ViewportPanel.h>

#include "imgui.h"
#include "clt/Core/Assets/IAssetManager.h"

editor::ViewportPanel::ViewportPanel(EditorContext* context) : EditorPanel(context)
{
    // --- MOVE ---

    moveIconActiveID = context->engineContext->assets->LoadTexture(
        clt::PathType::engine,
        "Resources/Textures/moveGizmoIconActive.png",
        "folder Opened Icon",
        clt::TextureFilter::LINEAR, true, false)->GetID();

    moveIconID = context->engineContext->assets->LoadTexture(
        clt::PathType::engine,
        "Resources/Textures/moveGizmoIcon.png",
        "folder Opened Icon",
     clt::TextureFilter::LINEAR, true, false)->GetID();

    // --- ROTATE ---

    rotateIconID = context->engineContext->assets->LoadTexture(
        clt::PathType::engine,
        "Resources/Textures/RotateGizmoIcon.png",
        "folder Opened Icon",
    clt::TextureFilter::LINEAR, true, false)->GetID();

    rotateIconActiveID = context->engineContext->assets->LoadTexture(
    clt::PathType::engine,
    "Resources/Textures/RotateGizmoIconActive.png",
    "folder Opened Icon",
    clt::TextureFilter::LINEAR, true, false)->GetID();

    // --- SCALE ---

    scaleIconID = context->engineContext->assets->LoadTexture(
    clt::PathType::engine,
    "Resources/Textures/ScaleGizmoIcon.png",
    "folder Opened Icon",
    clt::TextureFilter::LINEAR, true, false)->GetID();

    scaleIconActiveID = context->engineContext->assets->LoadTexture(
    clt::PathType::engine,
    "Resources/Textures/ScaleGizmoIconActive.png",
    "folder Opened Icon",
    clt::TextureFilter::LINEAR, true, false)->GetID();
}

const char* editor::ViewportPanel::GetName() const
{
    return "Viewport";
}

editor::DockPosition editor::ViewportPanel::GetDockingPosition() const
{
    return DockPosition::center;
}

void editor::ViewportPanel::Draw()
{
    if (ImGui::BeginTabBar("ViewportTabs"))
    {
        if (ImGui::BeginTabItem("Scene"))
        {
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game"))
        {
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    const ImVec2 availSize = ImGui::GetContentRegionAvail();
    constexpr float targetRatio = 16.0f / 9.0f;

    ImVec2 renderSize = availSize;

    if (const float availRatio = (availSize.y == 0.0f) ? targetRatio : (availSize.x / availSize.y); availRatio > targetRatio)
    {
        renderSize.x = availSize.y * targetRatio;
        renderSize.y = availSize.y;
    }
    else
    {
        renderSize.x = availSize.x;
        renderSize.y = (targetRatio == 0.0f) ? availSize.y : (availSize.x / targetRatio);
    }

    ImVec2 cursorPos = ImGui::GetCursorPos();
    cursorPos.x += (availSize.x - renderSize.x) * 0.5f;
    ImGui::SetCursorPosX(cursorPos.x);

    // if (!ctx->sceneFrameBuffer) return;
    //uint32_t texID = ctx->sceneFrameBuffer->GetColorAttachment();
    //ImGui::Image((void*)(intptr_t)texID, renderSize, ImVec2(0, 1), ImVec2(1, 0));

    const ImVec2 viewportStart = ImGui::GetItemRectMin();
    const ImVec2 viewportEnd = ImGui::GetItemRectMax();
    (void)viewportEnd;

    const auto buttonPos = ImVec2(viewportStart.x + 10, viewportStart.y + 10);
    ImGui::SetCursorScreenPos(buttonPos);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 0.8f));

    static bool is2D = false;
    const bool was2D = is2D;

    constexpr auto activeColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f);
    constexpr auto activeOverColor = activeColor;
    constexpr auto activeActivationColor = activeColor;

    if (is2D)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, activeColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, activeOverColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeActivationColor);
    }

    if (ImGui::Button("2D"))  is2D = !is2D;

    if (was2D) ImGui::PopStyleColor(3);

    static bool moveActive = true;
    static bool rotateActive = false;
    static bool scaleActive = false;

    ImGui::SameLine();

    if (ImGui::ImageButton("Translate", moveActive ? moveIconActiveID : moveIconID, { 16,16 }))
    {
        //mActorGizmo->SetMode(GizmoMode::Translate);
        moveActive = true;
        rotateActive = false;
        scaleActive = false;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Rotate", rotateActive ? rotateIconActiveID : rotateIconID, { 16,16 }))
    {
        //mActorGizmo->SetMode(GizmoMode::Rotate);
        moveActive = false;
        rotateActive = true;
        scaleActive = false;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Scale", scaleActive ? scaleIconActiveID : scaleIconID, { 16,16 }))
    {
        //mActorGizmo->SetMode(GizmoMode::Scale);
        moveActive = false;
        rotateActive = false;
        scaleActive = true;
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
}
