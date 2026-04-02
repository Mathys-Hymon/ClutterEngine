#ifndef CLUTTERENGINE_OPENGLFRAMEBUFFER_H
#define CLUTTERENGINE_OPENGLFRAMEBUFFER_H

#include "clt/Renderer/Framebuffer/Framebuffer.h"

#ifdef CLUTTER_PLATFORM_WINDOWS
#include "glad/glad.h"

namespace clt::graphic
{
    class OpenGLFramebuffer : public Framebuffer
    {
    protected:
		GLuint mRendererID = 0;
        FrameBufferSpecification mSpec;

        std::vector<GLuint> mColorAttachments;
        GLuint mDepthAttachment{0};

        void Invalidate();

        public:
        OpenGLFramebuffer(const FrameBufferSpecification& spec);
        ~OpenGLFramebuffer() override;

        void Bind() override;
        void UnBind() override;

        uint32_t GetHeight() override;
        uint32_t GetWidth() override;

        void Resize(uint32_t width, uint32_t height) override;

        uint32_t GetColorAttachment(uint32_t index) override;
        const FrameBufferSpecification& GetSpecification() override;
    };
}

#endif
#endif //CLUTTERENGINE_OPENGLFRAMEBUFFER_H