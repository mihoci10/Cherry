#pragma once

#include <Cherry/Buffer.h>

namespace Cherry{

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(void* data, std::shared_ptr<BufferDescriptor> descriptor, size_t count);
        ~OpenGLVertexBuffer();

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t m_BufferID = 0;
        uint32_t m_DescID = 0;
    };

}