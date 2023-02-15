#include "RendererAPI.h"

#include <Cherry/Platform/OpenGL/OpenGLRendererAPI.h>
#include <Cherry/Utils/Log.hpp>

namespace Cherry {

    bool RendererAPI::s_Initialized = false;
    std::shared_ptr<SDL_Window> RendererAPI::s_WndHnd = nullptr;
    std::shared_ptr<RendererSettings> RendererAPI::s_Settings = nullptr;

    RendererAPI::RendererAPI()
    {
    }

    void RendererAPI::Deinit()
    {
        s_Settings = nullptr;
        s_WndHnd = nullptr;
        s_Initialized = false;
    }

    std::unique_ptr<RendererAPI> RendererAPI::Create(std::shared_ptr<SDL_Window> windowHandle, std::shared_ptr<RendererSettings> rendererSettings)
    {
        if (s_Initialized)
            CHERRY_THROW("Cannot initialize RendererAPI twice!");

        std::unique_ptr<RendererAPI> result = nullptr;

        switch (rendererSettings->platform)
        {
        case Cherry::RendererPlatform::None:
            CHERRY_THROW("Headless mode is not supported by Renderer API!");
            break;
        case Cherry::RendererPlatform::OpenGL:
            result = std::make_unique<OpenGLRendererAPI>();
            break;
        case Cherry::RendererPlatform::Vulkan:
            CHERRY_THROW("Vulcan platform is not supported by Renderer API!");
            break;
        }

        s_Initialized = true;
        s_WndHnd = windowHandle;
        s_Settings = rendererSettings;

        return result;
    }
}