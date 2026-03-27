#ifndef CLUTTERENGINE_IASSET_H
#define CLUTTERENGINE_IASSET_H
#include "AssetType/Font.h"
#include "AssetType/Mesh.h"
#include "AssetType/Texture.h"

namespace clt
{
    enum class PathType
    {
        none,
        engine,
        game
    };

    class IAssetManager
    {
    public:
        virtual ~IAssetManager() = default;

        virtual Texture* LoadTexture(PathType pathtype, const std::string& path, const std::string& name, TextureFilter texFilter, bool generateMipMaps, bool flipVertically) = 0;
        virtual Texture* GetTexture(PathType pathtype, const std::string& name) = 0;

        virtual Mesh* LoadMesh(PathType, const std::string& path, const std::string& name) = 0;
        virtual Mesh* GetMesh(PathType, const std::string& name) = 0;

        virtual Font* LoadFont(PathType, const std::string& path, const std::string& name) = 0;
        virtual Font* GetFont(PathType, const std::string& name) = 0;

        virtual void UnloadAssets() = 0;
    };
    
}
#endif //CLUTTERENGINE_IASSET_H