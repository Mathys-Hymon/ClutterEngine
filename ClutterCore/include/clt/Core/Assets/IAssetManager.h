#ifndef CLUTTERENGINE_IASSET_H
#define CLUTTERENGINE_IASSET_H
#include "AssetType/Font.h"
#include "AssetType/Mesh.h"
#include "AssetType/Texture.h"

namespace clt
{
    class IAssetManager
    {
    public:
        virtual ~IAssetManager() = default;

        virtual Texture* LoadTexture(const std::string& path, const std::string& name, TextureFilter texFilter = TextureFilter::LINEAR, bool generateMipMaps = true, bool flipVertically = true) = 0;
        virtual Texture* GetTexture(const std::string& name) = 0;

        virtual Mesh* LoadMesh(const std::string& path, const std::string& name) = 0;
        virtual Mesh* GetMesh(const std::string& name) = 0;

        virtual Font* LoadFont(const std::string& path, const std::string& name) = 0;
        virtual Font* GetFont(const std::string& name) = 0;

        virtual void UnloadAssets() = 0;
    };
    
}
#endif //CLUTTERENGINE_IASSET_H