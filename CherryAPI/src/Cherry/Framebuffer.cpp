#include "Framebuffer.h"

#include <Cherry/Utils/Log.hpp>
#include <Cherry/Platform/OpenGL/OpenGLFramebuffer.h>

namespace Cherry{

    Framebuffer::Framebuffer()
    {
    }

    std::unique_ptr<Framebuffer> Framebuffer::Create(const RendererSettings& rendererSettings,
        const FramebufferSpecification& framebufferSpecification)
    {
        switch (rendererSettings.platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Framebuffer is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_unique<OpenGLFramebuffer>(framebufferSpecification);
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Framebuffer is not supported for Vulkan!");
        }
        CHERRY_THROW("Unsupported render platform encountered!");
    }

}