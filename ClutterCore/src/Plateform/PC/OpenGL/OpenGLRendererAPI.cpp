#include "OpenGLRendererAPI.h"

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
    glViewport(x, y, width, height);
}

void clt::graphic::OpenGLRendererAPI::SetClearColor(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void clt::graphic::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
