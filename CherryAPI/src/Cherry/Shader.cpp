#include "Shader.h"

#include <Cherry/Platform/OpenGL/OpenGLShader.h>
#include <Cherry/Utils/Log.hpp>

namespace Cherry{

    Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name), m_Sources{ { ShaderSourceType::Vertex, vertexSrc }, { ShaderSourceType::Fragment, fragmentSrc } }
    {}

    std::unique_ptr<Shader> Shader::Create(const RendererSettings& rendererSettings,
        const std::string& name, 
        const std::string& vertexSrc, 
        const std::string& fragmentSrc)
    {
        switch (rendererSettings.platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Shader is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_unique<OpenGLShader>(name, vertexSrc, fragmentSrc);
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Shader is not supported for Vulkan!");
        }
        CHERRY_THROW("Unsupported render platform encountered!");
    }

}