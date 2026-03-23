#include "TextureGL.h"

#include "glad/glad.h"

clt::TextureGL::TextureGL(const TextureFilter pTexFilter, const uint32_t width, const uint32_t height, const uint32_t channels,
    const unsigned char* data, const bool generateMipMaps)
    : Texture(width, height, channels)
{
    glGenTextures(1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

    if (pTexFilter == TextureFilter::NEAREST)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, generateMipMaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, generateMipMaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    const GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}
