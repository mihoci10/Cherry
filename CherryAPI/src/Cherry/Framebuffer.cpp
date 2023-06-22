#include "Framebuffer.h"

#include <Cherry/Utils/Log.hpp>
#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/OpenGLFramebuffer.h>

namespace Cherry{    

    std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& framebufferSpecification)
    {
        switch (RendererAPI::GetSettings()->platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Framebuffer is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(framebufferSpecification);
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Framebuffer is not supported for Vulkan!");
        }
        CHERRY_THROW("Unsupported render platform encountered!");
    }

}