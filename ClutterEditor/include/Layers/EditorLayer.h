#ifndef CLUTTERENGINE_EDITORLAYER_H
#define CLUTTERENGINE_EDITORLAYER_H

#include "clt/Core/Application/Application.h"
#include "clt/Core/Layers/Layer.h"

namespace editor
{
    class EditorLayer : public clt::Layer
    {

    public:
        explicit EditorLayer([[maybe_unused]] const clt::ApplicationCommandLineArgs& args);

        void OnAttach(const clt::engine::Context& context) override;
        void OnUpdate([[maybe_unused]] double dt) override;
        void OnEvent(clt::Event& ) override;
    };
}

#endif //CLUTTERENGINE_EDITORLAYER_H