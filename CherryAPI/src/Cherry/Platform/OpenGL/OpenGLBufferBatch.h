#pragma once

#include <Cherry/BufferBatch.h>

namespace Cherry{

    class OpenGLBufferBatch: public BufferBatch
    {
    public:
        OpenGLBufferBatch();
        ~OpenGLBufferBatch();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {
            return m_VertexBuffers;
        };
        std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_BufferID = 0;
        size_t m_VertexAttribCount = 0;

        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}