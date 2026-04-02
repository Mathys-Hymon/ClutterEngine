#include "OpenGLFramebuffer.h"
#include "../Assets/TextureGL.h"
#include "clt/Core/Debug/Log.h"

void clt::graphic::OpenGLFramebuffer::Invalidate()
{
    if (mRendererID)
    {
        glDeleteFramebuffers(1, &mRendererID);
        glDeleteTextures(static_cast<GLsizei>(mColorAttachments.size()), mColorAttachments.data());
        if (mDepthAttachment)
            glDeleteRenderbuffers(1, &mDepthAttachment);

        mColorAttachments.clear();
        mDepthAttachment = 0;
    }

    glGenFramebuffers(1, &mRendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);

    mColorAttachments.resize(mSpec.ColorAttachments);
    glGenTextures(mSpec.ColorAttachments, mColorAttachments.data());

    for (uint32_t i = 0; i < mSpec.ColorAttachments; i++)
    {
        glBindTexture(GL_TEXTURE_2D, mColorAttachments[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSpec.Width, mSpec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mColorAttachments[i], 0);
    }

    if (mSpec.HasDepth)
    {
        glGenRenderbuffers(1, &mDepthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mSpec.Width, mSpec.Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthAttachment);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) CLT_CORE_ERROR("Framebuffer is incomplete");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

clt::graphic::OpenGLFramebuffer::OpenGLFramebuffer(const FrameBufferSpecification& spec) : mSpec(spec)
{
    Invalidate();
}

clt::graphic::OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &mRendererID);
    glDeleteTextures(static_cast<GLsizei>(mColorAttachments.size()), mColorAttachments.data());

    if (mDepthAttachment) glDeleteRenderbuffers(1, &mDepthAttachment);
}

void clt::graphic::OpenGLFramebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);
    glViewport(0, 0, mSpec.Width, mSpec.Height);
}

void clt::graphic::OpenGLFramebuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t clt::graphic::OpenGLFramebuffer::GetHeight()
{
    return mSpec.Height;
}

uint32_t clt::graphic::OpenGLFramebuffer::GetWidth()
{
    return mSpec.Width;
}

uint32_t clt::graphic::OpenGLFramebuffer::GetColorAttachment(const uint32_t index)
{
    if (index < mColorAttachments.size()) return mColorAttachments[index];

    return 0;
}

const clt::graphic::FrameBufferSpecification& clt::graphic::OpenGLFramebuffer::GetSpecification()
{
    return mSpec;
}

void clt::graphic::OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
{
    if ((width == mSpec.Width && height == mSpec.Height) || (width == 0 && height == 0)) return;

    mSpec.Width = width;
    mSpec.Height = height;

    Invalidate();
}
