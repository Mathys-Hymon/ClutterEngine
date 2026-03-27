#ifndef CLUTTERENGINE_EDITORASSETMANAGER_H
#define CLUTTERENGINE_EDITORASSETMANAGER_H
#include <memory>

#include "clt/Core/Assets/IAssetManager.h"

namespace editor
{
    class EditorAssetManager : public clt::IAssetManager
    {
        std::unordered_map < std::string, clt::Texture*> mTextures;
        std::unordered_map < std::string, clt::Font*> mFonts;
        std::unordered_map < std::string, clt::Mesh*> mMeshes;

        std::unordered_map < clt::PathType, std::string> mPaths;

        public:
        explicit EditorAssetManager(const std::unordered_map < clt::PathType, std::string>& paths);
        ~EditorAssetManager() override;

        clt::Texture* LoadTexture(clt::PathType pathtype, const std::string& path, const std::string& name, clt::TextureFilter texFilter, bool generateMipMaps, bool flipVertically) override;
        clt::Texture* GetTexture(clt::PathType pathtype, const std::string& path) override;

        clt::Mesh* LoadMesh(clt::PathType, const std::string& path, const std::string& name) override;
        clt::Mesh* GetMesh(clt::PathType, const std::string& path) override;

        clt::Font* LoadFont(clt::PathType, const std::string& path, const std::string& name) override;
        clt::Font* GetFont(clt::PathType, const std::string& path) override;

        void UnloadAssets() override;
    };
}
#endif //CLUTTERENGINE_EDITORASSETMANAGER_H
