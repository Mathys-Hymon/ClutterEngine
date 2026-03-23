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

        Texture* LoadTexture(const std::string& path, const std::string& name, TextureFilter pTexFilter = TextureFilter::LINEAR, bool generateMipMaps = true, bool flipVertically = true) override;
        Texture* GetTexture(const std::string& name) override;

        Mesh* LoadMesh(const std::string& path, const std::string& name) override;
        Mesh* GetMesh(const std::string& name) override;

        Font* LoadFont(const std::string& path, const std::string& name) override;
        Font* GetFont(const std::string& name) override;
    };
}

#endif //CLUTTERENGINE_ASSETMANAGER_H