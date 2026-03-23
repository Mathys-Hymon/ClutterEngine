#include <clt/Core/Assets/AssetType/Texture.h>
#include <../src/Plateform/OpenGL/Assets/TextureGL.h>
#include "clt/Renderer/Renderer.h"

namespace clt
{
    Texture* Texture::Create(TextureFilter pTexFilter, uint32_t width, uint32_t height, uint32_t channels, const unsigned char* data, bool generateMipMaps)
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
