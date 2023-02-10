#pragma once

#include <Cherry/Shader.h>

namespace Cherry{
    
    class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform(const std::string_view& name, int value) override;
		virtual void SetUniform(const std::string_view& name, float value) override;
		virtual void SetUniform(const std::string_view& name, const glm::vec2& value) override;
		virtual void SetUniform(const std::string_view& name, const glm::vec3& value) override;
		virtual void SetUniform(const std::string_view& name, const glm::vec4& value) override;
		virtual void SetUniform(const std::string_view& name, const glm::mat4& value) override;

		virtual void SetUniformArray(const std::string_view& name, int* values, uint32_t count) override;

	private:
		void CreateProgram();
		uint32_t GetOpenGLShaderType(ShaderSourceType sourceType);

		uint32_t m_ProgramID;
		std::unordered_map<ShaderSourceType, uint32_t> m_ShaderIds = {};
    };

}