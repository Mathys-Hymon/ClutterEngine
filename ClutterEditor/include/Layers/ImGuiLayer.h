#ifndef CLUTTERENGINE_IMGUILAYER_H
#define CLUTTERENGINE_IMGUILAYER_H

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

namespace editor
{
    class ImGuiLayer : public clt::Layer
    {
    public:
        ImGuiLayer() : Layer("ImGui Layer") {}

        void OnAttach(const clt::engine::Context& context) override;

        void OnUpdate(float dt) override;
    };
}

#endif //CLUTTERENGINE_IMGUILAYER_H