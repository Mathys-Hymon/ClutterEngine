#ifndef CLUTTERENGINE_IMGUICONTEXTSERVICE_H
#define CLUTTERENGINE_IMGUICONTEXTSERVICE_H
#include <functional>
#include "clt/Core/EngineContext.h"

namespace editor
{
    class ImGuiContextService
    {
        const char* mGLSL{nullptr};
        const clt::engine::Context& mContext;

        public:
        ImGuiContextService(const clt::engine::Context& context, const char* glsl_version = "#version 460");
        ~ImGuiContextService();

        void NewFrame();
        void Render() const;

        void ApplyStyle(const std::function<void()>& applyTheme);
    };
}

#endif //CLUTTERENGINE_IMGUICONTEXTSERVICE_H