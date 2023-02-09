#include "Buffer.h"

#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/OpenGLBuffer.h>

namespace Cherry{

    std::shared_ptr<VertexBuffer> const VertexBuffer::Create(void* data, uint8_t stride, size_t size) {

        switch (RendererAPI::GetSettings()->platform)
        {
        case RendererPlatform::None:
            break;
        case RendererPlatform::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(data, stride, size);
        case RendererPlatform::Vulkan:
            break;
        }

        return nullptr;

    };
    
}