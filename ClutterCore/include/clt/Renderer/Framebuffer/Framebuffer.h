#ifndef CLUTTERENGINE_FRAMEBUFFER_H
#define CLUTTERENGINE_FRAMEBUFFER_H
#include <cstdint>

#include "clt/Core/Assets/AssetType/Texture.h"

namespace clt::graphic
{
    struct FrameBufferSpecification
    {
        uint32_t Width = 1280;
        uint32_t Height = 720;
        bool HasDepth = true;
        bool HasColor = true;
        uint32_t ColorAttachments = 1;
    };

    class Framebuffer
    {
        public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetWidth() = 0;
        virtual uint32_t GetHeight() = 0;

        virtual uint32_t GetColorAttachment(uint32_t index = 0) = 0;
        virtual const FrameBufferSpecification& GetSpecification() = 0;
    };
}

#endif //CLUTTERENGINE_FRAMEBUFFER_H