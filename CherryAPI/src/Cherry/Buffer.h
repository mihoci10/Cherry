#pragma once

namespace Cherry{

    class Buffer {
    public:
        Buffer() = delete;
        virtual ~Buffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        uint8_t GetStride() const { return m_Stride; }
        size_t GetCount() const { return m_Count; }
        size_t GetSize() const { return m_Size; }

    protected:
        Buffer(uint8_t stride, size_t size) : m_Stride(stride), m_Count(size / stride), m_Size(size) {};
        uint8_t m_Stride = 0;
        size_t m_Count = 0, m_Size = 0;
    };

    class VertexBuffer : public Buffer {
    public:
        VertexBuffer() = delete;
        virtual ~VertexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static std::shared_ptr<VertexBuffer> const Create(void* data, uint8_t stride, size_t size);

    protected:
        VertexBuffer(void* data, uint8_t stride, size_t size) : m_Data(data), Buffer(stride, size) {};
        void* m_Data;
    };

}