#include "clt/Core/Meta/Serializer.h"

#include <fstream>
#include <json.hpp>

#include "clt/Core/Debug/Log.h"
#include "clt/Core/Meta/Reflection.h"


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

                    rootData["Actors"]["actor - " + entityStr]["components"][GetName(metaType.id())] = SerializeAny(instance);
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

bool clt::meta::Serializer::Deserialize(const std::string& /*filePath*/) const
{
    CLT_CORE_ASSERT(mLevel, "Serializer has no Level attached");

    return true;
}
