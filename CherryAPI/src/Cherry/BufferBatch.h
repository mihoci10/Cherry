#pragma once

#include <Cherry/Buffer.h>

namespace Cherry{

    class BufferBatch
    {
    public:
        virtual ~BufferBatch() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

        static std::unique_ptr<BufferBatch> Create(const RendererSettings& rendererSettings);
    };
}