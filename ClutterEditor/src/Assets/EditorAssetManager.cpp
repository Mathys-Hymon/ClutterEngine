#include <Assets/EditorAssetManager.h>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "clt/Core/Debug/Log.h"
#include <ranges>

constexpr uint32_t FONT_ATLAS_WIDTH = 512;
constexpr uint32_t FONT_ATLAS_HEIGHT = 512;

editor::EditorAssetManager::EditorAssetManager(const std::unordered_map < clt::PathType, std::string>& paths)
{
    mPaths = paths;
}

editor::EditorAssetManager::~EditorAssetManager()
{
    EditorAssetManager::UnloadAssets();
};

clt::Texture* editor::EditorAssetManager::LoadTexture(const clt::PathType pathtype, const std::string& path, const std::string& /*name*/,
    const clt::TextureFilter texFilter, const bool generateMipMaps, const bool flipVertically)
{
    auto tempPath = mPaths[pathtype];
    tempPath += path;

    if (mTextures.contains(path)) return GetTexture(pathtype, path);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(tempPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);;

    if (!data)
    {
        CLT_CORE_WARN("Failed to load texture " + tempPath);
        return nullptr;
    }

    clt::Texture* newTexture = clt::Texture::Create(texFilter, static_cast<uint32_t>(width),
    static_cast<uint32_t>(height), static_cast<uint32_t>(channels), data, generateMipMaps);

    stbi_image_free(data);

    mTextures[path] = newTexture;

    CLUTTER_TRACE("Successfully loaded texture: {}", tempPath);

    return newTexture;
}

clt::Texture* editor::EditorAssetManager::GetTexture(const clt::PathType pathtype, const std::string& path)
{
    auto tempPath = mPaths[pathtype];
    tempPath += path;

    const auto it = mTextures.find(path);
    if (it == mTextures.end())
    {
        CLUTTER_WARN("Unable to find Texture: " + tempPath);

        return nullptr;
    }

    return it->second;
}

const std::unordered_map<std::string, clt::Texture*>& editor::EditorAssetManager::GetAllTextures()
{
    return mTextures;
}

clt::Mesh* editor::EditorAssetManager::LoadMesh(clt::PathType pathtype, const std::string& /*path*/, const std::string& /*name*/)
{
    return nullptr;
}

clt::Mesh* editor::EditorAssetManager::GetMesh(clt::PathType pathtype, const std::string& /*name*/)
{
    return nullptr;
}

clt::Font* editor::EditorAssetManager::LoadFont(clt::PathType pathtype, const std::string& path, const std::string& name)
{
    if (mFonts.contains(path)) return GetFont(pathtype, path);

    std::ifstream inputStream(path.c_str(), std::ios::binary);

    if (!inputStream.is_open())
    {
        CLUTTER_WARN("Failed to open font file: {}", path);
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
        CLUTTER_WARN("Failed to init font: {}", name);
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

        character.Size.x = static_cast<float>(packedChars[i].x1 - packedChars[i].x0);
        character.Size.y = static_cast<float>(packedChars[i].y1 - packedChars[i].y0);

        character.Bearing.x = packedChars[i].xoff;
        character.Bearing.y = packedChars[i].yoff;

        character.Advance = static_cast<uint32_t>(packedChars[i].xadvance);

        newFont->mCharacters[static_cast<unsigned char>(firstChar + i)] = character;
    }

    delete[] dataBuffer;
    delete[] fontAtlasTextureData;

    CLUTTER_TRACE("Successfully loaded font: {}", name);

    mFonts[path] = newFont;

    return newFont;
}

clt::Font* editor::EditorAssetManager::GetFont(const clt::PathType pathtype, const std::string& path)
{
    auto tempPath = mPaths[pathtype];
    tempPath += path;

    const auto it = mFonts.find(path);
    if (it == mFonts.end())
    {
        CLUTTER_WARN("Unable to find Font: " + tempPath);

        return nullptr;
    }

    return it->second;
}

void editor::EditorAssetManager::UnloadAssets()
{
    for (const auto& snd : mTextures | std::views::values) delete snd;

    mTextures.clear();

    for (const auto& val : mFonts | std::views::values) delete val;

    mFonts.clear();

    for (const auto& val : mMeshes | std::views::values) delete val;

    mMeshes.clear();

}
