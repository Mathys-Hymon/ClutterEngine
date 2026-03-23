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

editor::EditorAssetManager::EditorAssetManager()
{
}

editor::EditorAssetManager::~EditorAssetManager()
{
}

clt::Texture* editor::EditorAssetManager::LoadTexture(const std::string& path, const std::string& name,
    const clt::TextureFilter texFilter, const bool generateMipMaps, const bool flipVertically)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);;

    if (!data)
    {
        CLT_CORE_ERROR("Failed to load texture " + path);
        return nullptr;
    }

    stbi_image_free(data);

    clt::Texture* newTexture = clt::Texture::Create(texFilter, static_cast<uint32_t>(width),
    static_cast<uint32_t>(height), static_cast<uint32_t>(channels), data, generateMipMaps);

    mTextures[name] = newTexture;

    return newTexture;
}

clt::Texture* editor::EditorAssetManager::GetTexture(const std::string& name)
{
    const auto it = mTextures.find(name);
    if (it == mTextures.end())
    {
        CLUTTER_WARN("Unable to find Texture: " + name);

        auto dflt = mTextures.find("default");
        return dflt->second;
    }
    return it->second;
}

clt::Mesh* editor::EditorAssetManager::LoadMesh(const std::string& path, const std::string& name)
{
}

clt::Mesh* editor::EditorAssetManager::GetMesh(const std::string& name)
{
}

clt::Font* editor::EditorAssetManager::LoadFont(const std::string& path, const std::string& name)
{
    std::ifstream inputStream(path.c_str(), std::ios::binary);

    inputStream.seekg(0, std::ios::end);
    auto&& fontFileSize = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    auto dataBuffer = new uint8_t[fontFileSize];

    inputStream.read(reinterpret_cast<char*>(dataBuffer), fontFileSize);

    stbtt_fontinfo info = {};

    uint32_t fontCount = stbtt_GetNumberOfFonts(dataBuffer);

    CLT_CORE_INFO("[ASSET MANAGER] Font File: {} has {} fonts.", name, fontCount);
    try
    {
        stbtt_InitFont(&info, dataBuffer, 0);
    } catch (std::exception& e)
    {
        CLT_CORE_ERROR("[ASSET MANAGER] Failed to load font {} | Error : {}", name,  std::string(e.what()));
    }

    uint8_t* fontAtlasTextureData = new uint8_t[FONT_ATLAS_WIDTH * FONT_ATLAS_HEIGHT];
    stbtt_pack_context ctx;

    stbtt_PackBegin(
        &ctx,                                     // stbtt_pack_context (this call will initialize it)
        (unsigned char*)fontAtlasTextureData,     // Font Atlas texture data
        FONT_ATLAS_WIDTH,                           // Width of the font atlas texture
        FONT_ATLAS_HEIGHT,                          // Height of the font atlas texture
        0,                                        // Stride in bytes
        1,                                        // Padding between the glyphs
        nullptr);

    stbtt_PackFontRange(
        &ctx,                                     // stbtt_pack_context
        dataBuffer,                              // Font Atlas texture data
        0,                                        // Font Index
        fontSize,                                 // Size of font in pixels. (Use STBTT_POINT_SIZE(fontSize) to use points)
        codePointOfFirstChar,                     // Code point of the first charecter
        charsToIncludeInFontAtlas,                // No. of charecters to be included in the font atlas
        localState.packedChars                    // stbtt_packedchar array, this struct will contain the data to render a glyph
    );
    stbtt_PackEnd(&ctx);

    for (int i = 0; i < charsToIncludeInFontAtlas; i++)
    {
        float unusedX, unusedY;

        stbtt_GetPackedQuad(
            localState.packedChars,              // Array of stbtt_packedchar
            FONT_ATLAS_WIDTH,                      // Width of the font atlas texture
            FONT_ATLAS_HEIGHT,                     // Height of the font atlas texture
            i,                                   // Index of the glyph
            &unusedX, &unusedY,                  // current position of the glyph in screen pixel coordinates, (not required as we have a different corrdinate system)
            &localState.alignedQuads[i],         // stbtt_alligned_quad struct. (this struct mainly consists of the texture coordinates)
            0                                    // Allign X and Y position to a integer (doesn't matter because we are not using 'unusedX' and 'unusedY')
        );
    }

    delete[] fontDataBuf;

    // Optionally write the font atlas texture as a png file.
    stbi_write_png("fontAtlas.png", FONT_ATLAS_WIDTH, FONT_ATLAS_HEIGHT, 1, fontAtlasTextureData, FONT_ATLAS_WIDTH);

    return fontAtlasTextureData;
}

clt::Font* editor::EditorAssetManager::GetFont(const std::string& name)
{
    return nullptr;
}
