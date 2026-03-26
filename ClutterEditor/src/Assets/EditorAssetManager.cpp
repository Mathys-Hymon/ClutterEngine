#include <Assets/EditorAssetManager.h>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "clt/Core/Debug/Log.h"

constexpr uint32_t FONT_ATLAS_WIDTH = 512;
constexpr uint32_t FONT_ATLAS_HEIGHT = 512;

editor::EditorAssetManager::EditorAssetManager(const std::unordered_map < clt::PathType, std::string>& paths)
{
    mPaths = paths;
}

editor::EditorAssetManager::~EditorAssetManager()
{
    UnloadAssets();
};

clt::Texture* editor::EditorAssetManager::LoadTexture(const clt::PathType pathtype, const std::string& path, const std::string& /*name*/,
    const clt::TextureFilter texFilter, const bool generateMipMaps, const bool flipVertically)
{
    if (mTextures.contains(path)) return GetTexture(pathtype, path);

    auto tempPath = mPaths[pathtype];
    tempPath += path;

    int width, height, channels;
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(tempPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);;

    if (!data)
    {
        CLT_CORE_WARN("[ASSET MANAGER] Failed to load texture " + tempPath);
        return nullptr;
    }

    clt::Texture* newTexture = clt::Texture::Create(texFilter, static_cast<uint32_t>(width),
    static_cast<uint32_t>(height), static_cast<uint32_t>(channels), data, generateMipMaps);

    stbi_image_free(data);

    mTextures[tempPath] = newTexture;

    CLUTTER_TRACE("[ASSET MANAGER] Successfully loaded texture: {}", tempPath);

    return newTexture;
}

clt::Texture* editor::EditorAssetManager::GetTexture(clt::PathType pathtype, const std::string& name)
{
    auto tempPath = mPaths[pathtype];
    tempPath += name;

    const auto it = mTextures.find(tempPath);
    if (it == mTextures.end())
    {
        CLUTTER_WARN("[ASSET MANAGER] Unable to find Texture: " + tempPath);

        const auto defaultTexture = mTextures.find("default");

        if (defaultTexture == mTextures.end()) return nullptr;

        return defaultTexture->second;
    }

    return it->second;
}

clt::Mesh* editor::EditorAssetManager::LoadMesh(const std::string& /*path*/, const std::string& /*name*/)
{
    return nullptr;
}

clt::Mesh* editor::EditorAssetManager::GetMesh(const std::string& /*name*/)
{
    return nullptr;
}

clt::Font* editor::EditorAssetManager::LoadFont(const std::string& path, const std::string& name)
{
    std::ifstream inputStream(path.c_str(), std::ios::binary);

    if (!inputStream.is_open())
    {
        CLUTTER_WARN("[ASSET MANAGER] Failed to open font file: {}", path);
        return nullptr;
    }

    inputStream.seekg(0, std::ios::beg);
    auto fontFileSize = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    auto dataBuffer = new uint8_t[fontFileSize];

    inputStream.read(reinterpret_cast<char*>(dataBuffer), fontFileSize);
    inputStream.close();

    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, dataBuffer, 0))
    {
        CLUTTER_WARN("[ASSET MANAGER] Failed to init font: {}", name);
        delete [] dataBuffer;
        return nullptr;
    }

    auto fontAtlasTextureData = new uint8_t[FONT_ATLAS_WIDTH * FONT_ATLAS_HEIGHT];
    stbtt_pack_context ctx;

    stbtt_PackBegin(&ctx, fontAtlasTextureData, FONT_ATLAS_WIDTH, FONT_ATLAS_HEIGHT, 0, 1, nullptr);

    float fontSize = 64.f;
    int firstChar = 32;
    int charCount = 96;

    stbtt_packedchar packedChars[96];

    stbtt_PackFontRange(&ctx, dataBuffer, 0, fontSize, firstChar, charCount, packedChars);
    stbtt_PackEnd(&ctx);

    clt::Texture* atlasTexture = clt::Texture::Create
    (
        clt::TextureFilter::LINEAR,
        FONT_ATLAS_WIDTH,
        FONT_ATLAS_HEIGHT,
        1,
        fontAtlasTextureData,
        false
    );

    auto* newFont = new clt::Font();
    newFont->mName = name;
    newFont->mPath = path;
    newFont->mAtlasTexture = std::make_unique<clt::Texture>(*atlasTexture);

    for (int i = 0; i < charCount; i++)
    {
        clt::Character character;

        character.UVMin.x = static_cast<float>(packedChars[i].x0) / FONT_ATLAS_WIDTH;
        character.UVMin.y = static_cast<float>(packedChars[i].y0) / FONT_ATLAS_HEIGHT;
        character.UVMax.x = static_cast<float>(packedChars[i].x1) / FONT_ATLAS_WIDTH;
        character.UVMax.y = static_cast<float>(packedChars[i].y1) / FONT_ATLAS_HEIGHT;

        character.Size.x = static_cast<float>(packedChars[i].x1) - packedChars[i].x0;
        character.Size.y = static_cast<float>(packedChars[i].y1) - packedChars[i].y0;

        character.Bearing.x = packedChars[i].xoff;
        character.Bearing.y = packedChars[i].yoff;

        character.Advance = static_cast<uint32_t>(packedChars[i].xadvance);

        newFont->mCharacters[static_cast<unsigned char>(firstChar + i)] = character;
    }

    delete[] dataBuffer;
    delete[] fontAtlasTextureData;

    CLUTTER_TRACE("[ASSET MANAGER] Successfully loaded font: {}", name);

    return newFont;
}

clt::Font* editor::EditorAssetManager::GetFont(const std::string& /*name*/)
{
    return nullptr;
}

void editor::EditorAssetManager::UnloadAssets()
{
    for (const auto& tex : mTextures)
    {
        delete tex.second;
    }

    mTextures.clear();
}
