#ifndef CLUTTERENGINE_TEXTUREGL_H
#define CLUTTERENGINE_TEXTUREGL_H
#include "clt/Core/Assets/AssetType/Texture.h"

namespace clt
{
    class TextureGL : public Texture
    {
        public:
        TextureGL(const TextureFilter pTexFilter, const uint32_t width, const uint32_t height, const uint32_t channels, const unsigned char* data, const bool generateMipMaps);
    };
}

#endif //CLUTTERENGINE_TEXTUREGL_H
