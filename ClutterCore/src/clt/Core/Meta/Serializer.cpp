#include "clt/Core/Meta/Serializer.h"

#include <fstream>
#include <json.hpp>

#include "clt/Core/Debug/Log.h"
#include "clt/Core/Meta/Reflection.h"
#include "clt/Core/ActorComponent/Actor.h"


clt::meta::Serializer::Serializer(Level* level) : mLevel(level)
{
}

nlohmann::json clt::meta::Serializer::SerializeAny(const entt::meta_any& meta) const
{
    nlohmann::json returnValue;

    const auto metaType = meta.type();

    if (metaType == entt::resolve<float>()) returnValue = meta.cast<float>();  // FLOAT
    else if (metaType == entt::resolve<int>()) returnValue = meta.cast<int>(); // INT
    else if (metaType == entt::resolve<uint32_t>()) returnValue = meta.cast<uint32_t>(); // UINT32_T
    else if (metaType == entt::resolve<bool>()) returnValue = meta.cast<bool>(); // BOOL

    else
    {
        for (auto [ID, data] : metaType.data())
        {
            returnValue[GetName(ID)] = SerializeAny(data.get(meta));
        }
    }

    return returnValue;
}

bool clt::meta::Serializer::Serialize(const std::string& filePath) const
{
    CLT_CORE_ASSERT(mLevel, "Serializer has no Level attached");

    nlohmann::json rootData;

    rootData["LevelName"] = "test";
    rootData["EngineVersion"] = "0.0.1";

    auto& registry = mLevel->Registry();

    for (const auto entity : registry.storage<entt::entity>())
    {
        const std::string entityStr = std::to_string(static_cast<uint32_t>(entity));

        for (auto [id, storage] : registry.storage())
        {
            if (storage.contains(entity))
            {
                if (auto metaType = entt::resolve(storage.info()))
                {
                    const void* componentPtr = storage.value(entity);
                    entt::meta_any instance = metaType.from_void(componentPtr);

                    rootData["Actors"]["actor - " + entityStr]["Components"][GetName(metaType.id())] = SerializeAny(instance);
                }
            }
        }
    }

    std::ofstream file(filePath);

    if (!file.is_open()) return false;

    file << rootData.dump(4);
    file.close();

    return true;
}

void clt::meta::Serializer::DeserializeAny(const nlohmann::json& json, entt::meta_any& instance) const
{
    for (const auto& [key, value] : json.items())
    {
        entt::meta_data data = instance.type().data(entt::hashed_string(key.data()));

        if (!data) continue;

        if (data.type() == entt::resolve<float>()) data.set(instance, value.get<float>()); // FLOAT
        else if (data.type() == entt::resolve<int>())  data.set(instance, value.get<int>()); // INT
        else if (data.type() == entt::resolve<uint32_t>()) data.set(instance, value.get<uint32_t>()); // UINT32_T
        else if (data.type() == entt::resolve<bool>()) data.set(instance, value.get<bool>()); // BOOL

        else
        {
            entt::meta_any subInstance = data.get(instance);

            DeserializeAny(value, subInstance);

            data.set(instance, subInstance);
        }
    }
}

bool clt::meta::Serializer::Deserialize(const std::string& filePath) const
{
    CLT_CORE_ASSERT(mLevel, "Serializer has no Level attached");

    std::ifstream file(filePath);

    if (!file.is_open()) return false;

    nlohmann::json rootData;

    file >> rootData;

    for (const auto& [actorID, actorValue] : rootData["Actors"].items())
    {
        nlohmann::json components = actorValue;

        Actor actor = mLevel->CreateActor();

        for ( const auto& [componentID, componentValue] : components["Components"].items())
        {

            if(const entt::meta_type& compType = entt::resolve(entt::hashed_string(componentID.data())))
            {
                auto instance = compType.construct();

                if (!instance) continue;

                DeserializeAny(componentValue, instance);

                auto func = compType.func(entt::hashed_string{"AttachComponent"});

                if (!func) continue;

                entt::entity id = actor.GetID();

                func.invoke({}, &mLevel->Registry(), id, instance);
            }
        }
    }

    return true;
}
