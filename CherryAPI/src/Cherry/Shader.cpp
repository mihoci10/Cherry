#include "Shader.h"

#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/OpenGLShader.h>
#include <Cherry/Utils/Log.hpp>

namespace Cherry{

    std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (RendererAPI::GetSettings()->platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Shader is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Shader is not supported for Vulkan!");
        }
    }

}