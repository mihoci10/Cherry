#pragma once

#include <Cherry/Buffer.h>
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

}