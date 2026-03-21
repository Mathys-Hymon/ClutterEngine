#ifndef CLUTTERENGINE_IMGUICONTEXTSERVICE_H
#define CLUTTERENGINE_IMGUICONTEXTSERVICE_H
#include <functional>

#include "EditorContext.h"
#include "clt/Core/EngineContext.h"

namespace editor
{
    class ImGuiContextService
    {
        const char* mGLSL{nullptr};
        const EditorContext* mContext;

        public:
        ImGuiContextService(const EditorContext* context, const char* glsl_version = "#version 460");
        ~ImGuiContextService();

        void NewFrame();
        void Render() const;

        void ApplyStyle(const std::function<void()>& applyTheme);
    };
}

#endif //CLUTTERENGINE_IMGUICONTEXTSERVICE_H