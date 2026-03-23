#ifndef CLUTTERENGINE_EDITORASSETMANAGER_H
#define CLUTTERENGINE_EDITORASSETMANAGER_H
#include <memory>

#include "clt/Core/Assets/IAssetManager.h"

namespace editor
{
    class EditorAssetManager : public clt::IAssetManager
    {
        std::unordered_map < std::string, clt::Texture*> mTextures;
        public:

        EditorAssetManager();
        virtual ~EditorAssetManager();

        clt::Texture* LoadTexture(const std::string& path, const std::string& name, clt::TextureFilter texFilter, bool generateMipMaps, bool flipVertically) override;
        clt::Texture* GetTexture(const std::string& name) override;

        clt::Mesh* LoadMesh(const std::string& path, const std::string& name) override;
        clt::Mesh* GetMesh(const std::string& name) override;

        clt::Font* LoadFont(const std::string& path, const std::string& name) override;
        clt::Font* GetFont(const std::string& name) override;
    };
}
#endif //CLUTTERENGINE_EDITORASSETMANAGER_H
