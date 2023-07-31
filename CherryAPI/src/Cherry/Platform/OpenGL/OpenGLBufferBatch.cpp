#include "OpenGLBufferBatch.h"

#include <Cherry/Platform/OpenGL/OpenGLUtils.hpp>
#include <GL/glew.h>

namespace Cherry{

    OpenGLBufferBatch::OpenGLBufferBatch()
    {
        glCreateVertexArrays(1, &m_BufferID);
    }

    OpenGLBufferBatch::~OpenGLBufferBatch()
    {
        glDeleteVertexArrays(1, &m_BufferID);
    }

    void OpenGLBufferBatch::Bind() const
    {
        glBindVertexArray(m_BufferID);
    }

    void OpenGLBufferBatch::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLBufferBatch::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_BufferID);
        vertexBuffer->Bind();

        const auto segments = vertexBuffer->GetDescriptor().GetSegments();
        for (auto& segment : segments) {
            switch (segment.dataType)
            {
                case Cherry::BufferDataType::BOOL:
                case Cherry::BufferDataType::INT_8:
                case Cherry::BufferDataType::UINT_8:
                case Cherry::BufferDataType::INT_16:
                case Cherry::BufferDataType::UINT_16:
                case Cherry::BufferDataType::INT_32:
                case Cherry::BufferDataType::UINT_32:
                case Cherry::BufferDataType::INT_64:
                case Cherry::BufferDataType::UINT_64:
                    glEnableVertexAttribArray(static_cast<GLuint>(m_VertexAttribCount));
                    glVertexAttribIPointer(static_cast<GLuint>(m_VertexAttribCount),
                        segment.count,
                        BufferTypeConvert(segment.dataType),
                        vertexBuffer->GetDescriptor().GetSize(),
                        (const void*)segment.offset);
                    break;
                case Cherry::BufferDataType::FLOAT:
                case Cherry::BufferDataType::DOUBLE:
                    glEnableVertexAttribArray(static_cast<GLuint>(m_VertexAttribCount));
                    glVertexAttribPointer(static_cast<GLuint>(m_VertexAttribCount),
                        segment.count,
                        BufferTypeConvert(segment.dataType),
                        segment.normalized ? GL_TRUE : GL_FALSE,
                        vertexBuffer->GetDescriptor().GetSize(),
                        (const void*)segment.offset);
                    break;
            }

            m_VertexAttribCount++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLBufferBatch::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_BufferID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}