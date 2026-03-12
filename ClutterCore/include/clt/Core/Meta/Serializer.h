#ifndef CLUTTERENGINE_SERIALIZER_H
#define CLUTTERENGINE_SERIALIZER_H
#include "clt/Core/Level/Level.h"

namespace clt::meta
{
    class Serializer
    {
        Level* mLevel;

        public:

        Serializer(Level* level);

        bool Serialize(const std::string& filePath) const;
        bool Deserialize(const std::string& filePath) const;
    };
}
#endif //CLUTTERENGINE_SERIALIZER_H