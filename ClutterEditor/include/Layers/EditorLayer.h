#ifndef CLUTTERENGINE_EDITORLAYER_H
#define CLUTTERENGINE_EDITORLAYER_H

#include "clt/Core/Layers/Layer.h"

namespace editor
{
    class EditorLayer : public clt::Layer
    {

    public:
        EditorLayer() : Layer("Editor Layer") {};

        void OnAttach(const clt::engine::Context& context) override;
        void OnUpdate(double /*dt*/) override;
        void OnEvent(clt::Event& ) override;
    };
}

#endif //CLUTTERENGINE_EDITORLAYER_H