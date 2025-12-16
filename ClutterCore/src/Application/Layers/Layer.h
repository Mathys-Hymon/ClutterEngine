#pragma once
#include <string>
#include <Core/EngineContext.h>

namespace clt
{
    class Layer
    {
    protected:
        std::string mDebugName;

    public:
        Layer(const std::string& name = "Layer") : mDebugName(name) {};
        virtual ~Layer() = default;

        virtual void OnAttach(const EngineContext& context) {}
        virtual void OnDetach() {};

        virtual void OnUpdate(const float& dt) {}
        virtual void OnImGuiRender() {}

        const std::string& GetName() const { return mDebugName; }
    };
}