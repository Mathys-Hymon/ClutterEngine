#include <clt/Core/Assets/AssetType/Texture.h>
#include "clt/Renderer/Renderer.h"

#ifdef CLUTTER_PLATFORM_WINDOWS
#include <../src/Plateform/PC/OpenGL/Assets/TextureGL.h>
#endif

namespace clt
{
    Texture* Texture::Create(const TextureFilter pTexFilter, const uint32_t width, const uint32_t height, const uint32_t channels, const unsigned char* data, const bool generateMipMaps)
    {
            #ifdef CLUTTER_PLATFORM_WINDOWS
            return new TextureGL(pTexFilter, width, height, channels, data, generateMipMaps);
            #elif define(CLUTTER_PLATFORM_3DS)
            return nullptr;
            #endif
    }
}
