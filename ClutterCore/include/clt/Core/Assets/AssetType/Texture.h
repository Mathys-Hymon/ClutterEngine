#ifndef CLUTTERENGINE_TEXTURE_H
#define CLUTTERENGINE_TEXTURE_H
#include <cstdint>
#include <vector>

#include "clt/Core/Math/Math.h"

namespace clt
{
    enum class TextureFilter
    {
        NEAREST,
        LINEAR
    };

    class Texture
    {
        protected:

        uint32_t mID{0};
        uint32_t mWidth{0};
        uint32_t mHeight{0};
        uint32_t mChannels{0};

        float UMin{0.f}, VMin{0.f};
        float UMax{1.f}, VMax{1.f};

        Texture(const uint32_t width, const uint32_t height, const uint32_t channels)
        : mWidth(width), mHeight(height), mChannels(channels)
        {};

        public:
        ~Texture() = default;
        static Texture* Create(TextureFilter pTexFilter, uint32_t width, uint32_t height, uint32_t channels, const unsigned char* data, bool generateMipMaps = true);

        void UpdateInfo(uint32_t& width, uint32_t& height) const
        {
            width = mWidth;
            height = mHeight;
        }

        uint32_t GetID() const { return mID; }
        uint32_t GetWidth() const { return mWidth; }
        uint32_t GetHeight() const { return mHeight; }
        uint32_t GetChannels() const { return mChannels; }
        Vector2 GetSize() const { return {GetWidth(), GetHeight()}; }

        float GetUMin() const { return UMin; }
        float GetUMax() const { return UMax; }

        float GetVMin() const { return VMin; }
        float GetVMax() const { return VMax; }

        Vector2 GetUVMin() const { return {GetUMin(), GetVMin()}; }
        Vector2 GetUVMax() const { return {GetUMax(), GetVMax()}; }
    };
}

#endif //CLUTTERENGINE_TEXTURE_H