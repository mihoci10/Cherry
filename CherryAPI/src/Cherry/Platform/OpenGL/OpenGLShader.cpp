#include "OpenGLShader.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cherry
{
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: Shader(name, vertexSrc, fragmentSrc)
	{
		CreateProgram();
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, int value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, float value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniform(const std::string_view& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniformArray(const std::string_view& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_ProgramID, name.data());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		for (auto& [shaderType, shaderSource] : m_Sources)
		{
			auto shader = glCreateShader(GetOpenGLShaderType(shaderType));
			m_ShaderIds.emplace(shaderType, shader);

			const GLchar* src = (const GLchar*) shaderSource.c_str();
			const GLint len = (const GLint) shaderSource.size();

			glShaderSource(shader, 1, &src, &len);
			glCompileShader(shader);
			glAttachShader(program, shader);
		}

		glLinkProgram(program);

		for (auto& [shadertype, shader] : m_ShaderIds) {
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}

		m_ProgramID = program;
	}

	uint32_t OpenGLShader::GetOpenGLShaderType(ShaderSourceType sourceType)
	{
		switch (sourceType)
		{
		case ShaderSourceType::None:
			break;
		case ShaderSourceType::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderSourceType::Fragment:
			return GL_FRAGMENT_SHADER;
		}
		return 0;
	}
}
