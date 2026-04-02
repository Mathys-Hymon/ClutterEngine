#include <clt/Renderer/Renderer.h>

#include "clt/Renderer/Renderer2D.h"
#include "clt/Renderer/Renderer3D.h"

#ifdef CLUTTER_PLATFORM_WINDOWS
    #include "../../ClutterCore/src/Plateform/PC/OpenGL/OpenGLRendererAPI.h"
#elif defined(CLUTTER_PLATFORM_3DS)
    // #include "../../ClutterCore/src/Plateform/3DS/Citro3DRendererAPI.h"
#endif

namespace clt::graphic
{
    void Renderer::Init()
    {
#ifdef CLUTTER_PLATFORM_WINDOWS
        RendererAPI::SetAPI(RendererAPIType::OpenGL);
        mRendererAPI = std::make_unique<OpenGLRendererAPI>();
#elif defined(CLUTTER_PLATFORM_3DS)
        RendererAPI::SetAPI(RendererAPIType::Pica200);
        // mRendererAPI = std::make_unique<Citro3DRendererAPI>();
#else
        CLT_CORE_ASSERT(false, "Unknown platform!");
#endif

        if(mRendererAPI)
        {
            mRendererAPI->Init();

            mRenderer2D = std::make_unique<Renderer2D>(mRendererAPI.get());
            mRenderer3D = std::make_unique<Renderer3D>(mRendererAPI.get());
        }
    }
}
