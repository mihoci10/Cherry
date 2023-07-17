#include "RendererAPI.h"

#include <Cherry/Platform/OpenGL/OpenGLRendererAPI.h>
#include <Cherry/Utils/Log.hpp>

namespace Cherry {

    RendererAPI::RendererAPI(std::shared_ptr<SDL_Window> windowHandle,
        RendererSettings rendererSettings)
        : m_WindowHandle(windowHandle), m_RendererSettings(rendererSettings)
    {
    }

    std::unique_ptr<RendererAPI> RendererAPI::Create(std::shared_ptr<SDL_Window> windowHandle,
        RendererSettings rendererSettings)
    {
        switch (rendererSettings.platform)
        {
        case Cherry::RendererPlatform::None:
            CHERRY_THROW("Headless mode is not supported by Renderer API!");
        case Cherry::RendererPlatform::OpenGL:
            return std::make_unique<OpenGLRendererAPI>(windowHandle, rendererSettings);
        case Cherry::RendererPlatform::Vulkan:
            CHERRY_THROW("Vulcan platform is not supported by Renderer API!");
        }
    }
}