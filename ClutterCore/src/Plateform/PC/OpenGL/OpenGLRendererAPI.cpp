#include "OpenGLRendererAPI.h"

#ifdef CLUTTER_PLATFORM_WINDOWS

#include "glad/glad.h"

void clt::graphic::OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
}

void clt::graphic::OpenGLRendererAPI::SetViewport(const uint32_t x, const uint32_t y,const uint32_t width,const uint32_t height)
{
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void clt::graphic::OpenGLRendererAPI::DrawIndexed(const uint32_t indexCount)
{
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
}

void clt::graphic::OpenGLRendererAPI::SetClearColor(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void clt::graphic::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif