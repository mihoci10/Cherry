#include "RendererAPI.h"

#include <Cherry/Platform/OpenGL/OpenGLRendererAPI.h>

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

        if (s_Initialized) {
            // fatal error
        }

        s_Initialized = true;
        s_WndHnd = windowHandle;
        s_Settings = rendererSettings;

        switch (s_Settings->platform)
        {
        case Cherry::RendererPlatform::None:
            break;
        case Cherry::RendererPlatform::OpenGL:
            return std::make_unique<OpenGLRendererAPI>();
        case Cherry::RendererPlatform::Vulkan:
            break;
        }

        s_Settings = nullptr;
        s_WndHnd = nullptr;
        s_Initialized = false;
        return nullptr;
    }
}