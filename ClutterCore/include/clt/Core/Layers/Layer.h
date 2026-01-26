#pragma once
#include <string>
#include <clt/Core/EngineContext.h>

namespace clt
{
    class Layer
    {
    protected:
        std::string mDebugName;

    public:
        explicit Layer(const std::string& name = "Layer") : mDebugName(name) {};
        virtual ~Layer() = default;

        virtual void OnAttach(const EngineContext& context) {}
        virtual void OnDetach() {};

        virtual void OnUpdate(const float& dt) {}
        virtual void OnRender() {}

        const std::string& GetName() const { return mDebugName; }
    };
}