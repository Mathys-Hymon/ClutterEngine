#ifndef CLUTTERENGINE_SERIALIZER_H
#define CLUTTERENGINE_SERIALIZER_H
#include "json.hpp"
#include "clt/Core/Level/Level.h"

namespace clt::meta
{
    class Serializer
    {
        Level* mLevel;

        nlohmann::json SerializeAny(const entt::meta_any& meta) const;

        public:

        Serializer(Level* level);

        bool Serialize(const std::string& filePath) const;
        bool Deserialize(const std::string& filePath) const;
    };
}
#endif //CLUTTERENGINE_SERIALIZER_H