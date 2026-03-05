#ifndef CLUTTERENGINE_IMGUILAYER_H
#define CLUTTERENGINE_IMGUILAYER_H

#include <clt/Core/EntryPoint.h>
#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>


class ImGuiLayer : public clt::Layer
{
public:
    ImGuiLayer() : Layer("ImGuiLayer") {}

    void OnAttach(const clt::engine::Context& context) override;

    void OnUpdate(const float& dt) override
    {
        // std::cout << "Update..." << std::endl;
    }
};


#endif //CLUTTERENGINE_IMGUILAYER_H