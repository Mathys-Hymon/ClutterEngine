#ifndef CLUTTERENGINE_FONT_H
#define CLUTTERENGINE_FONT_H
#include <cstdint>
#include <string>

#include "clt/Core/Math/Math.h"
#include <memory>
#include "clt/Core/Assets/AssetType/Texture.h"

namespace clt
{
    struct Character
    {
        Vector2 UVMin{0.f, 0.f};
        Vector2 UVMax{1.f, 1.f};

        Vector2 Size{0};
        Vector2 Bearing{0};
        uint32_t Advance{0};
    };

    struct Font
    {
        std::string mName;
        std::string mPath;

        std::unique_ptr<clt::Texture> mAtlasTexture{nullptr};

        std::unordered_map<unsigned char, Character> mCharacters;
    };
}

#endif //CLUTTERENGINE_FONT_H