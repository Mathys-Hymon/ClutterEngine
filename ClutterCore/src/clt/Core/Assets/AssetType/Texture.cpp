#include <clt/Core/Assets/AssetType/Texture.h>
#include <../src/Plateform/PC/OpenGL/Assets/TextureGL.h>
#include "clt/Renderer/Renderer.h"

namespace clt
{
    Texture* Texture::Create(const TextureFilter pTexFilter, const uint32_t width, const uint32_t height, const uint32_t channels, const unsigned char* data, const bool generateMipMaps)
    {
        switch (graphic::Renderer::GetRendererAPI())
        {
        case graphic::RendererAPIType::OpenGL:
            return new TextureGL(pTexFilter, width, height, channels, data, generateMipMaps);

        case graphic::RendererAPIType::Vulkan:
            return nullptr;

        case graphic::RendererAPIType::Pica200:
            return nullptr;

        case graphic::RendererAPIType::None:
            return nullptr;
        }

        return nullptr;
    }
}
