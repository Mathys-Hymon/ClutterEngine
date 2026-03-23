#include <Assets/EditorAssetManager.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "clt/Core/Debug/Log.h"

editor::EditorAssetManager::EditorAssetManager()
{
}

editor::EditorAssetManager::~EditorAssetManager()
{
}

clt::Texture* editor::EditorAssetManager::LoadTexture(const std::string& path, const std::string& name,
    const clt::TextureFilter texFilter, const bool generateMipMaps, const bool flipVertically)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);;

    if (!data)
    {
        CLT_CORE_ERROR("Failed to load texture " + path);
        return nullptr;
    }

    stbi_image_free(data);

    clt::Texture* newTexture = clt::Texture::Create(texFilter, static_cast<uint32_t>(width),
    static_cast<uint32_t>(height), static_cast<uint32_t>(channels), data, generateMipMaps);

    mTextures[name] = newTexture;

    return newTexture;
}

clt::Texture* editor::EditorAssetManager::GetTexture(const std::string& name)
{
    const auto it = mTextures.find(name);
    if (it == mTextures.end())
    {
        CLUTTER_WARN("Unable to find Texture: " + name);

        auto dflt = mTextures.find("default");
        return dflt->second;
    }
    return it->second;
}

clt::Mesh* editor::EditorAssetManager::LoadMesh(const std::string& path, const std::string& name)
{
}

clt::Mesh* editor::EditorAssetManager::GetMesh(const std::string& name)
{
}

clt::Font* editor::EditorAssetManager::LoadFont(const std::string& path, const std::string& name)
{
}

clt::Font* editor::EditorAssetManager::GetFont(const std::string& name)
{
}
