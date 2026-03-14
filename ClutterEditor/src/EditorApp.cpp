#include <clt/Core/Application/Application.h>
#include <clt/Core/EntryPoint.h>
#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Level/Level.h"
#include "clt/Core/Meta/Serializer.h"

class EditorLayer : public clt::Layer
{
public:
    EditorLayer() : Layer("EditorLayer") {}

    void OnAttach(const clt::engine::Context& context) override
    {
        if (context.Window)
        {
            clt::Level level;

            // auto actor = level.CreateActor();
            //
            // auto& transform = actor.AddComponent<clt::Transform>();
            //
            // transform.position = {2, 25, 3};
            //
            // const auto temp = actor.GetComponent<clt::Transform>();


            clt::meta::Serializer s(&level);

            // if (s.Serialize("test.cltLevel"))
            // {
            //     CLUTTER_INFO("Level saved successfully");
            // }
            // else
            // {
            //     CLUTTER_INFO("Level could not be saved");
            // }

            if (s.Deserialize("test.cltLevel"))
            {
                CLUTTER_INFO("Level loaded successfully");

                for (auto e : level.Registry().storage<entt::entity>())
                {
                    CLUTTER_INFO("ACTOR ID : {}", static_cast<int>(e));
                    if (auto comp = level.Registry().try_get<clt::Transform>(e))
                    {
                        CLUTTER_INFO("Transform loaded successfully");

                        CLUTTER_INFO("actor location :  -> X: {}, Y: {}, Z: {}",
                            comp->position.x,
                            comp->position.y,
                            comp->position.z);
                    }
                }
            }
            else
            {
                CLUTTER_INFO("Level could not be loaded");
            }

        }
        else
        {
            CLT_CORE_WARN("Window not initialized yet");
        }
    }

    void OnUpdate(const float /*dt*/) override
    {
    }

    void OnEvent(clt::Event& /*e*/) override
    {

    }
};







class ClutterEditor : public clt::Application
{
public:
    ClutterEditor(const clt::ApplicationCommandLineArgs& args)
        : Application(args)
    {
        PushLayer(new EditorLayer());
    }

    ~ClutterEditor() override {}
};


clt::Application* clt::CreateApplication(clt::ApplicationCommandLineArgs args)
{
    return new ClutterEditor(args);
}