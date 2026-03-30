#ifndef CLUTTERENGINE_ASSETMANAGER_H
#define CLUTTERENGINE_ASSETMANAGER_H
#include "IAssetManager.h"

namespace clt
{
    class AssetManager : public IAssetManager
    {
        public:
        AssetManager();
        ~AssetManager();

        Texture* LoadTexture(PathType pathtype, const std::string& path, const std::string& name, TextureFilter pTexFilter = TextureFilter::LINEAR, bool generateMipMaps = true, bool flipVertically = true) override;
        Texture* GetTexture(PathType pathtype, const std::string& name) override;

        const std::unordered_map<std::string, Texture*>& GetAllTextures() override;

        Mesh* LoadMesh(PathType pathtype, const std::string& path, const std::string& name) override;
        Mesh* GetMesh(PathType pathtype, const std::string& name) override;

        Font* LoadFont(PathType pathtype, const std::string& path, const std::string& name) override;
        Font* GetFont(PathType pathtype, const std::string& name) override;

        void UnloadAssets() override;
    };
}

#endif //CLUTTERENGINE_ASSETMANAGER_H