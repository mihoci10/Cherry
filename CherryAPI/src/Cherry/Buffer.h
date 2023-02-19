#pragma once

namespace Cherry{

    enum class BufferDataType {
        INT_8, UINT_8, INT_16, UINT_16, INT_32, UINT_32, INT_64, UINT_64, FLOAT, DOUBLE, BOOL
    };

    class BufferDescriptor {
    private: 
        class BufferSegment {
        public:
            BufferSegment() = delete;
            BufferSegment(BufferDataType dataType, uint8_t count, uint8_t offset, bool normalized)
                : dataType(dataType), count(count), offset(offset), normalized(normalized) {};

            uint8_t GetSize() const;

            BufferDataType dataType;
            uint8_t count = 0;
            uint8_t offset = 0;
            bool normalized = false;
        };

    public:
        BufferDescriptor() = default;

        void AddSegment(BufferDataType dataType, uint8_t count, bool normalized);
        const std::vector<BufferSegment>& GetSegments() const { return m_Segments; };
        uint8_t GetSize() const { return m_Offset; };

    private:
        uint8_t m_Offset = 0;
        std::vector<BufferSegment> m_Segments = {};
    };

    class Buffer {
    public:
        Buffer() = delete;
        virtual ~Buffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        std::shared_ptr<BufferDescriptor> GetDescriptor() const { return m_Descriptor; };
        size_t GetCount() const { return m_Count; }

    protected:
        Buffer(std::shared_ptr<BufferDescriptor> descriptor, size_t count) 
            : m_Descriptor(descriptor), m_Count(count) {};
        std::shared_ptr<BufferDescriptor> m_Descriptor;
        size_t m_Count = 0;
    };

    class VertexBuffer : public Buffer {
    public:
        VertexBuffer() = delete;
        virtual ~VertexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static std::shared_ptr<VertexBuffer> const Create(void* data, std::shared_ptr<BufferDescriptor> descriptor, size_t count);

    protected:
        VertexBuffer(void* data, std::shared_ptr<BufferDescriptor> descriptor, size_t count) 
            : m_Data(data), Buffer(descriptor, count) {};
        void* m_Data;
    };

}