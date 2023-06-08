#include "OpenGLBuffer.h"

#include <Cherry/Utils/Log.hpp>

#include <GL/glew.h>

namespace Cherry{
	GLuint BufferTypeConvert(BufferDataType dataType) {
		switch (dataType)
		{
		case Cherry::BufferDataType::INT_8:
			return GL_BYTE;
		case Cherry::BufferDataType::UINT_8:
			return GL_UNSIGNED_BYTE;
		case Cherry::BufferDataType::INT_16:
			return GL_SHORT;
		case Cherry::BufferDataType::UINT_16:
			return GL_UNSIGNED_SHORT;
		case Cherry::BufferDataType::INT_32:
			return GL_INT;
		case Cherry::BufferDataType::UINT_32:
			return GL_UNSIGNED_INT; 
		case Cherry::BufferDataType::INT_64:
			CHERRY_THROW("Buffer data type INT64 is not supported in OpenGL!");
		case Cherry::BufferDataType::UINT_64:
			CHERRY_THROW("Buffer data type UINT64 is not supported in OpenGL!");
		case Cherry::BufferDataType::FLOAT:
			return GL_FLOAT;
		case Cherry::BufferDataType::DOUBLE:
			return GL_DOUBLE;
		case Cherry::BufferDataType::BOOL:
			return GL_BOOL;
		}
		CHERRY_THROW("Unsupported buffer data type encountered!");
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, std::shared_ptr<BufferDescriptor> descriptor, size_t count) 
		: VertexBuffer(data, descriptor, count)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, m_Count * m_Descriptor->GetSize(), m_Data, GL_STATIC_DRAW);

		const auto segments = m_Descriptor->GetSegments();
		glGenVertexArrays(1, &m_DescID);
		glBindVertexArray(m_DescID);
		glEnableVertexAttribArray(0);
		for (auto& segment : segments) {
			glVertexAttribPointer(0, 
				segment.count, 
				BufferTypeConvert(segment.dataType),
				segment.normalized ? GL_TRUE : GL_FALSE, 
				m_Descriptor->GetSize() - segment.GetSize(), 
				NULL);
		}
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindVertexArray(m_DescID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}