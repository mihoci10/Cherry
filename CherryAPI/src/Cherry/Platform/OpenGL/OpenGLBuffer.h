#pragma once

#include <Cherry/Buffer.h>

namespace Cherry{

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(void* data, uint8_t stride, size_t size); 
        ~OpenGLVertexBuffer();

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t m_BufferID;
    };

}