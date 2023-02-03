#include "RendererAPI.h"

#include <Cherry/Platform/OpenGL/OpenGLRendererAPI.h>

namespace Cherry {

    bool RendererAPI::s_Initialized = false;
    std::shared_ptr<RendererSettings> RendererAPI::s_Settings = nullptr;


    RendererAPI::RendererAPI()
    {
    }

    void RendererAPI::Deinit()
    {
        s_Initialized = false;
        s_Settings = nullptr;
    }

    std::unique_ptr<RendererAPI> RendererAPI::Create(std::shared_ptr<RendererSettings> rendererSettings)
    {
        if (s_Initialized) {
            // fatal error
        }

        s_Initialized = true;
        s_Settings = rendererSettings;

        switch (s_Settings->platform)
        {
        case Cherry::RendererPlatform::None:
            return nullptr;
        case Cherry::RendererPlatform::OpenGL:
            return std::make_unique<OpenGLRendererAPI>();
        case Cherry::RendererPlatform::Vulkan:
            break;
        }

        s_Settings = nullptr;
        s_Initialized = false;
        return nullptr;
    }
}