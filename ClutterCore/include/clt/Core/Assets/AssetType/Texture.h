#ifndef CLUTTERENGINE_TEXTURE_H
#define CLUTTERENGINE_TEXTURE_H
#include <cstdint>
#include <vector>

#include "clt/Core/Math/Math.h"

namespace clt
{

    class Texture
    {
        uint32_t mID{0};
        uint32_t mWidth{0};
        uint32_t mHeight{0};
        uint32_t mChannels{0};

        Texture(const uint32_t id, const uint32_t width, const uint32_t height, const uint32_t channels, [[maybe_unused]] const std::vector<unsigned char>& mPixels)
        : mID(id), mWidth(width), mHeight(height), mChannels(channels)
        {};

        friend class AssetManager;

        public:

        ~Texture() = default;

        void UpdateInfo(uint32_t& width, uint32_t& height);

        uint32_t GetID() const { return mID; }
        uint32_t GetWidth() const { return mWidth; }
        uint32_t GetHeight() const { return mHeight; }
        uint32_t GetChannels() const { return mChannels; }
        Vector2 GetSize() const { return {GetWidth(), GetHeight()}; }
    };
}

#endif //CLUTTERENGINE_TEXTURE_H