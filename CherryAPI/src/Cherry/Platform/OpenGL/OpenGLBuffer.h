#pragma once

#include <Cherry/Buffer.h>

namespace Cherry{

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(void* data, const BufferDescriptor& descriptor, size_t count);
        ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t m_BufferID = 0;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(void* data, const BufferDescriptor& descriptor, size_t count);
        ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t m_BufferID = 0;
    };

}