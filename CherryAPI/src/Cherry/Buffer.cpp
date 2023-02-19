#include "Buffer.h"

#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/OpenGLBuffer.h>
#include <Cherry/Utils/Log.hpp>

namespace Cherry{

    uint8_t BufferDescriptor::BufferSegment::GetSize() const
    {
        switch (dataType)
        {
        case Cherry::BufferDataType::INT_8:
        case Cherry::BufferDataType::UINT_8:
        case Cherry::BufferDataType::BOOL:
            return count * 1;
        case Cherry::BufferDataType::INT_16:
        case Cherry::BufferDataType::UINT_16:
            return count * 2;
        case Cherry::BufferDataType::INT_32:
        case Cherry::BufferDataType::UINT_32:
        case Cherry::BufferDataType::FLOAT:
            return count * 4;
        case Cherry::BufferDataType::INT_64:
        case Cherry::BufferDataType::UINT_64:
        case Cherry::BufferDataType::DOUBLE:
            return count * 8;
        }
    }

    void BufferDescriptor::AddSegment(BufferDataType dataType, uint8_t count, bool normalized)
    {
        m_Segments.push_back(BufferSegment(dataType, count, m_Offset, normalized));
        m_Offset += m_Segments.back().GetSize();
    }

    std::shared_ptr<VertexBuffer> const VertexBuffer::Create(void* data, std::shared_ptr<BufferDescriptor> descriptor, size_t count) {

        switch (RendererAPI::GetSettings()->platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Vertex Buffer is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(data, descriptor, count);
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Vertex Buffer is not supported in for Vulkan!");
        }
    };

}