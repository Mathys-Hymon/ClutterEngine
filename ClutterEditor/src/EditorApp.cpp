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

            auto actor = level.CreateActor();

            auto& transform = actor.AddComponent<clt::Transform>();

            transform.position = {2, 25, 3};

            const auto temp = actor.GetComponent<clt::Transform>();

            CLUTTER_INFO("actor location :  -> X: {}, Y: {}, Z: {}",
              temp->position.x,
              temp->position.y,
              temp->position.z);


            clt::meta::Serializer s(&level);

            if (s.Serialize("test.cltLevel"))
            {
                CLUTTER_INFO("Level saved successfully");
            }
            else
            {
                CLUTTER_INFO("Level could not be saved");
            }

        }
        else
        {
            CLT_CORE_WARN("Window not initialized yet (Normal pour le test)");
        }
    }

    void OnUpdate(const float /*dt*/) override
    {
        // std::cout << "Update..." << std::endl;
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