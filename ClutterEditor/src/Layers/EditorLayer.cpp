#include "../../include/Layers/EditorLayer.h"

#include <clt/Core/Layers/Layer.h>
#include <clt/Core/EngineContext.h>
#include <iostream>

#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Debug/Log.h"
#include "clt/Core/Level/Level.h"
#include "clt/Core/Meta/Serializer.h"



void editor::EditorLayer::OnAttach(const clt::engine::Context& context)
{
    Layer::OnAttach(context);

    if (context.Window)
    {
        clt::Level level;

        auto actor = level.CreateActor();

        auto& transform = actor.AddComponent<clt::Transform>();

        transform.position = {2, 25, 3};


        auto& sprite = actor.AddComponent<clt::Sprite>();

        sprite.flipY = true;
        sprite.textureName = "sprite.png";
        sprite.zIndex = 12;
        sprite.tint = {2.1f, 3.0f, 1.0f, 1.0f};

        clt::meta::Serializer s(&level);

        if (s.Serialize("test.cltLevel"))
        {
            CLUTTER_INFO("Level saved successfully");
        }
        else
        {
            CLUTTER_INFO("Level could not be saved");
        }

        // if (s.Deserialize("test.cltLevel"))
        // {
        //     CLUTTER_INFO("Level loaded successfully");
        //
        //     for (auto e : level.Registry().storage<entt::entity>())
        //     {
        //         CLUTTER_INFO("ACTOR ID : {}", static_cast<int>(e));
        //         if (const auto comp = level.Registry().try_get<clt::Transform>(e))
        //         {
        //             CLUTTER_INFO("Transform loaded successfully");
        //
        //             CLUTTER_INFO("actor location :  -> X: {}, Y: {}, Z: {}",
        //                 comp->position.x,
        //                 comp->position.y,
        //                 comp->position.z);
        //         }
        //     }
        // }
        // else
        // {
        //     CLUTTER_INFO("Level could not be loaded");
        // }

    }
    else
    {
        CLT_CORE_WARN("Window not initialized yet");
    }
}

void editor::EditorLayer::OnUpdate(const float dt)
{
    Layer::OnUpdate(dt);
}

void editor::EditorLayer::OnEvent(clt::Event& event)
{
    Layer::OnEvent(event);
}
