#include <Services/ImGuiContextService.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "clt/Core/IWindow.h"
#include "clt/Core/Debug/Log.h"
#include "Debug/ImGuiConsoleSink.h"
#include "GLFW/glfw3.h"

editor::ImGuiContextService::ImGuiContextService(const EditorContext* context, const char* glsl_version) : mGLSL(glsl_version), mContext(context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    if (const auto window = static_cast<GLFWwindow*>(context->engineContext->window->GetNativeWindow()))
    {
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    mSink = std::make_shared<log::ImGuiConsoleSink>();
    clt::core::Log::AddSink(mSink);

    CLUTTER_INFO("Sink connected successfully");
}

editor::ImGuiContextService::~ImGuiContextService()
{
    clt::core::Log::RemoveSink(mSink);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void editor::ImGuiContextService::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void editor::ImGuiContextService::Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (const ImGuiIO& io = ImGui::GetIO(); io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        if (const auto window = static_cast<GLFWwindow*>(mContext->engineContext->window->GetNativeWindow()))
        {
            glfwMakeContextCurrent(window);
        }
    }
}

void editor::ImGuiContextService::ApplyStyle(const std::function<void()>& applyTheme)
{
    if (applyTheme) applyTheme();
}
