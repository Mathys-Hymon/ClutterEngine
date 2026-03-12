#include "clt/Core/Meta/Serializer.h"

#include <fstream>
#include <json.hpp>

#include "clt/Core/Debug/Log.h"
#include "clt/Core/Meta/Reflection.h"

clt::meta::Serializer::Serializer(Level* level) : mLevel(level)
{
}

bool clt::meta::Serializer::Serialize(const std::string& filePath) const
{
    CLT_CORE_ASSERT(mLevel, "Serializer has no Level attached");

    nlohmann::json data;

    data["LevelName"] = "test";
    data["EngineVersion"] = "0.0.1";

    auto& registry = mLevel->Registry();

    for (auto entity : registry.storage<entt::entity>())
    {
        CLUTTER_INFO("ENTITY ID : {}", static_cast<uint32_t>(entity));

        for (auto [id, storage] : registry.storage())
        {
            if (storage.contains(entity))
            {
                auto metaType = entt::resolve(storage.info());

                if (metaType)
                {
                    CLUTTER_INFO("Component Found");

                    for (auto [mId, mData] : metaType.data())
                    {
                        CLUTTER_INFO("id ! {}", GetName(mId));

                        const void* componentPtr = storage.value(entity);

                        entt::meta_any instance = metaType.from_void(componentPtr);

                        entt::meta_any value = mData.get(instance);

                        if (value && value.type() == entt::resolve<float>())
                        {
                            CLUTTER_INFO("Valeur : {}", value.cast<float>());
                        }
                    }
                }
                else
                {
                    CLUTTER_INFO("Component Not Found");
                }
            }
        }
    }

    std::ofstream file(filePath);

    if (!file.is_open()) return false;

    file << data.dump(4);
    file.close();

    return true;
}

bool clt::meta::Serializer::Deserialize(const std::string& /*filePath*/) const
{
    CLT_CORE_ASSERT(mLevel, "Serializer has no Level attached");
    return true;
}
