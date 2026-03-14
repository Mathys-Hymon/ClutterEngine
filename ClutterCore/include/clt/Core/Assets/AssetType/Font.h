#ifndef CLUTTERENGINE_FONT_H
#define CLUTTERENGINE_FONT_H
#include <cstdint>
#include <string>

#include "clt/Core/Math/Math.h"

namespace clt
{
    struct Character
    {
        uint32_t TextureID{0};
        Vector2 Size{0};
        Vector2 Bearing{0};
        uint32_t Advance{0};
    };

    struct Font
    {
        std::string mName;
        std::string mPath;
        std::unordered_map<unsigned char, Character> mCharacters;
    };
}

#endif //CLUTTERENGINE_FONT_H