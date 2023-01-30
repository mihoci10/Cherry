#include "RendererAPI.h"

#include <Cherry/Platform/OpenGL/OpenGLRendererAPI.h>

namespace Cherry {

    std::unique_ptr<RendererAPI> RendererAPI::Create(std::shared_ptr<RendererSettings> rendererSettings)
    {
        switch (rendererSettings->platform)
        {
        case Cherry::RendererPlatform::None:
            return nullptr;
        case Cherry::RendererPlatform::OpenGL:
            return std::make_unique<OpenGLRendererAPI>(rendererSettings);
        case Cherry::RendererPlatform::Vulkan:
            return nullptr;
        }

        return nullptr;
    }
}