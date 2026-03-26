#ifndef CLUTTERENGINE_EDITORASSETMANAGER_H
#define CLUTTERENGINE_EDITORASSETMANAGER_H
#include <memory>

#include "clt/Core/Assets/IAssetManager.h"

namespace editor
{
    class EditorAssetManager : public clt::IAssetManager
    {
        std::unordered_map < std::string, clt::Texture*> mTextures;
        std::unordered_map < clt::PathType, std::string> mPaths;

        public:
        explicit EditorAssetManager(const std::unordered_map < clt::PathType, std::string>& paths);
        virtual ~EditorAssetManager();

        clt::Texture* LoadTexture(clt::PathType pathtype, const std::string& path, const std::string& name, clt::TextureFilter texFilter = clt::TextureFilter::LINEAR, bool generateMipMaps = true, bool flipVertically = true) override;
        clt::Texture* GetTexture(clt::PathType pathtype, const std::string& name) override;

        clt::Mesh* LoadMesh(const std::string& path, const std::string& name) override;
        clt::Mesh* GetMesh(const std::string& name) override;

        clt::Font* LoadFont(const std::string& path, const std::string& name) override;
        clt::Font* GetFont(const std::string& name) override;

        void UnloadAssets() override;
    };
}
#endif //CLUTTERENGINE_EDITORASSETMANAGER_H
