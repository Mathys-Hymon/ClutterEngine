#include "RenderCommand.h"

#include "Renderer.h"
#include "../../ClutterCore/src/Plateform/OpenGL/OpenGLRendererAPI.h"
//#include "../../ClutterCore/src/Plateform/Vulkan/VulkanRendererAPI.h"

namespace clt
{
    namespace graphic
    {
        RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();

        void RenderCommand::Init()
        {
            switch(RendererAPI::GetAPI())
            {
            case RendererAPIType::OpenGL:
                s_RendererAPI = new OpenGLRendererAPI();
                break;

            case RendererAPIType::Vulkan:
                break;

            default:
                break;
            }

            if(s_rendererAPI) s_rendererAPI->Init();
        }
    }
}