#include <clt/Core/Assets/AssetManager.h>


clt::AssetManager::AssetManager()
{
}

clt::AssetManager::~AssetManager()
{
}

clt::Texture* clt::AssetManager::LoadTexture(PathType pathtype, const std::string& path, const std::string& name, const TextureFilter texFilter, const bool generateMipMaps, const bool flipVertically)
{
    return nullptr;
}

clt::Texture* clt::AssetManager::GetTexture(PathType pathtype, const std::string& name)
{
    return nullptr;
}

clt::Mesh* clt::AssetManager::LoadMesh(PathType pathtype, const std::string& path, const std::string& name)
{
    return nullptr;
}

clt::Mesh* clt::AssetManager::GetMesh(PathType pathtype, const std::string& name)
{
    return nullptr;
}

clt::Font* clt::AssetManager::LoadFont(PathType pathtype, const std::string& path, const std::string& name)
{
    return nullptr;
}

clt::Font* clt::AssetManager::GetFont(PathType pathtype, const std::string& name)
{
    return nullptr;
}

void clt::AssetManager::UnloadAssets()
{
}
